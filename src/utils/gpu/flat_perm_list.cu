#include "flat_perm_list.h"
#include "view_types.h"
#include "cuda_error.h"

struct FlatPermList::Impl {
    int* indexes;
    int  indexes_size;
    int* data;
    int  data_size;
    int  permutation_size;

    Impl(const PermList& list) {
        permutation_size = list[0][0].size();
        std::vector<int> host_indexes;
        std::vector<int> host_data;
        int running_index = 0;
        for(auto& sublist : list) {
            host_indexes.push_back(running_index);
            running_index += sublist.size() * permutation_size;
            for(auto& perm : sublist)
                for(int num : perm)
                    host_data.push_back(num);
        }
        indexes_size = host_indexes.size();
        data_size    = host_data.size();
        check_cuda_error(cudaMalloc(&indexes, indexes_size * sizeof(int)));
        check_cuda_error(cudaMalloc(&data,    data_size    * sizeof(int)));
        cudaMemcpy(indexes, host_indexes.data(), indexes_size * sizeof(int), cudaMemcpyHostToDevice);
        cudaMemcpy(data,    host_data.data(),    data_size    * sizeof(int), cudaMemcpyHostToDevice);
    }

    ~Impl() {
        cudaFree(indexes);
        cudaFree(data);
    }
};

FlatPermList::FlatPermList(const PermList& permutations)
    : impl(std::make_unique<Impl>(permutations)) {}

FlatPermList::~FlatPermList() = default;

FlatPermList::View FlatPermList::get_view() {
    return View(impl->indexes, impl->indexes_size,
                impl->data,    impl->data_size,
                impl->permutation_size);
}
