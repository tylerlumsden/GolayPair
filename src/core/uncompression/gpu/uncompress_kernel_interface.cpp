#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<map>
#include<vector>
#include<set>
#include<array>
#include<time.h>
#include"fftw3.h"
#include"array.h"
#include"fourier.h"
#include"equivalence.h"
#include<tgmath.h>
#include<algorithm>
#include<fstream>
#include<iostream>
#include<format>
#include <functional>

#include"golay.h"
#include"match_pairs.h"
#include"sort.h"
#include"constants.h"
#include"io.h"
#include <thread>
#include <filesystem>
#include "uncompression.h"
#include "uncompress_kernel.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <cuda_runtime_api.h>

int uncompress_gpu(
    std::vector<int>& orig, 
    const int COMPRESS, 
    const int NEWCOMPRESS, 
    const int PAF_CONSTANT, 
    const int PROC_ID, 
    const int PROC_NUM, 
    std::ofstream& outfile, 
    int seqflag
) {
    const int ORDER = orig.size() * COMPRESS;

    Fourier FourierManager = Fourier(ORDER / NEWCOMPRESS);

    std::set<int> alphabet = getalphabet(COMPRESS);

    std::set<int> newalphabet = getalphabet(NEWCOMPRESS);

    std::vector<std::vector<int>> parts = getCombinations(COMPRESS / NEWCOMPRESS, newalphabet);
    std::vector<std::vector<int>> partition;

    std::map<int, std::vector<std::vector<int>>> partitions;

    //generate all permutations of possible decompositions for each letter in the alphabet
    for(int letter : alphabet) {
        partition.clear();
        for(std::vector<int> part : parts) {
            int sum = 0;
            for(long unsigned int i = 0; i < part.size(); i++) {
                sum += part[i];
            }
            if(sum == letter) {
                do {
                    partition.push_back(part);
                } while(next_permutation(part.begin(), part.end()));
            }
        }
        partitions.insert(make_pair(letter, partition));
    }

    //shift original sequence such that the element with the largest number of permutations is in the front
    set<int> seta;
    for(int element : orig) {
        seta.insert(element);
    }

    size_t max = 0;
    int best = orig[0];
    for(int element : seta) {
        if(partitions.at(element).size() > max) {
            max = partitions.at(element).size();
            best = element;
        }
    }
    for(size_t i = 0; i < orig.size(); i++) {
        if(orig[i] == best) {
            rotate(orig.begin(), orig.begin() + i, orig.end());
        }
    }

    set<vector<int>> perma;
    for(vector<int> perm : partitions.at(orig[0])) {
        set<vector<int>> equiv = generateUncompress(perm);
        perma.insert(*equiv.begin());
    }

    vector<vector<int>> newfirsta;
    for(vector<int> perm : perma) {
        newfirsta.push_back(perm);
    }

    PermList permutation_list;
    permutation_list.push_back(newfirsta);
    for(size_t i = 1; i < orig.size(); ++i) {
        permutation_list.push_back(partitions.at(orig[i]));
    }
    
    std::function<void(std::span<int>, std::span<double>)> write_function; 
    if(seqflag) {
        write_function =
        [&outfile](std::span<int> seq, std::span<double> psd) {
            write_seq_psd(seq, psd, outfile);
        };
    } else {
        int bound = ORDER * 2 - PAF_CONSTANT;
        write_function = 
        [&outfile, bound](std::span<int> seq, std::span<double> psd) {
            write_seq_psd_invert(seq, psd, outfile, bound);
        };
    }

    uncompress_kernel(
        orig, 
        permutation_list,
        ORDER / NEWCOMPRESS, 
        ORDER, 
        PAF_CONSTANT,
        write_function
    );

    return 0;
}

void uncompress_kernel(
  std::vector<int> seq,
  PermList permutations,
  size_t new_length,
  int order,
  int paf_constant,
  std::function<void(std::span<int>, std::span<double>)> writer
) {
  using BigInt = boost::multiprecision::cpp_int;

  size_t seq_length = seq.size();

  std::vector<int> radices;
  for(auto list : permutations) {
    radices.push_back(list.size());
  }

  BigInt count = 1;
  for(int num : radices) {
    count *= num;
  }

  //printf("Pre-allocation VRAM:\n");
  //print_vram();

  std::size_t free_mem, total_mem;
  cudaMemGetInfo(&free_mem, &total_mem);

  // TODO: free_mem division should be designated somewhere else
  size_t items_per_iter = static_cast<size_t>(
    std::min(count, static_cast<BigInt>((free_mem / 256) / (seq_length * sizeof(float))))
  );

  UncompressKernel kernel(permutations, seq, new_length, items_per_iter);

  //printf("Post-allocation VRAM, %lu sequences allocated:\n", items_per_iter);
  //print_vram();

  size_t filtered_count = 0;
  printf("Uncompressing with a count of: %s\n", count.str().c_str());
  for(BigInt offset = 0; offset < count;) {
    printf("Current offset: %s\n", offset.str().c_str());

    BigInt remaining = count - offset;

    // TODO: refactor... ugly if else chain
    std::size_t threads_per_block, num_blocks;
    if(remaining < items_per_iter) {
      if(remaining < 256) {
        threads_per_block = static_cast<int>(remaining);
        num_blocks = 1;
      } else {
        threads_per_block = std::min(static_cast<std::size_t>(256), items_per_iter);
        num_blocks = static_cast<std::size_t>(remaining / static_cast<BigInt>(threads_per_block));
      }
    } else {
      threads_per_block = std::min(static_cast<std::size_t>(256), items_per_iter);
      num_blocks = static_cast<std::size_t>(items_per_iter / threads_per_block);
    }
    std::size_t num_threads = num_blocks * threads_per_block;
    std::cout << "num_threads: " << num_threads << "\n";

    // BigInt -> mixed-radix conversion (moved from MixedRadixPool::set_base)
    std::vector<int> mixed_radix(kernel.radices().size());
    BigInt tmp = offset;
    for(int i = (int)mixed_radix.size() - 1; i >= 0; --i) {
      mixed_radix[i] = static_cast<int>(tmp % kernel.radices()[i]);
      tmp /= kernel.radices()[i];
    }
    kernel.set_offset(mixed_radix);

    printf("Launching cartesian product\n");
    kernel.launch_cartesian_product(num_blocks, threads_per_block);

    //printf("Launching FFT batch\n");
    kernel.launch_fft();

    //printf("Filtering batch\n");
    size_t n = kernel.launch_sequence_filter(num_blocks, threads_per_block, order, paf_constant);
    filtered_count += n;

    kernel.write_filtered(n, writer);

    offset += num_threads;
  }

  printf("Done uncompressing, total output: %lu\n", filtered_count);
}