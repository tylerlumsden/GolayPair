#include <cstdint>
#include <vector>
#include<cmath>
#include<iostream>
#include<numeric>
#include<set>
#include <functional>
#include <boost/multiprecision/cpp_int.hpp>
#include <optional>

int mobius(int n) {
    if (n == 1) return 1;
    int count = 0;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            n /= i;
            if (n % i == 0) return 0; // square factor
            count++;
        }
    }
    if (n > 1) count++; // remaining prime
    return (count % 2 == 0) ? 1 : -1;
}

int lyndon_count(int length, int alphabet_size) {
    int sum = 0;
    for (int d = 1; d <= length; ++d) {
        if (length % d == 0) {
            int mu_d = mobius(length / d);
            std::cout << "Mobius of " << length / d << " = " << mu_d << "\n";
            int power = (int)std::pow(alphabet_size, d);
            sum += mu_d * power;
        }
    }
    return sum / length;
}

boost::multiprecision::cpp_int necklace_count(int length, int alphabet_size) {
    boost::multiprecision::cpp_int sum = 0;
    for(int i = 1; i <= length; i++) {
        int exp = std::gcd(i, length);
        sum += boost::multiprecision::pow(boost::multiprecision::cpp_int(alphabet_size), exp);
    }
    return sum / length;
}

void generate_necklaces_prefix(const int LEN, 
    const std::set<int>& alphabet, 
    const std::function<void(const std::vector<int>&, const int)>& callback,
    std::optional<std::reference_wrapper<std::vector<int>>> partial_seq = std::nullopt,
    const int i = 0,
    const int p = 0) {

    if (LEN <= i || alphabet.empty()) return;
    
    std::vector<int> default_seq;
    std::vector<int>& seq = partial_seq ? partial_seq->get() : default_seq;
    seq.resize(LEN);

    std::function<void(int, int)> generate = [&](int index, int period) {
        if(index == LEN) {
            callback(seq, period);
            return;
        }

        seq[index] = seq[index - period];
        generate(index + 1, period);

        for (auto it = alphabet.upper_bound(seq[index - period]); it != alphabet.end(); ++it) {
            seq[index] = *it;
            generate(index + 1, index + 1);
        }
    };

    if(i == 0 && p == 0) {
        for(const int& character : alphabet) {
            seq[0] = character;
            generate(1, 1);
        }
    } else {
        generate(i, p);
    }
}

void generate_necklaces_wrapper(const int LEN, 
    const std::set<int>& alphabet, 
    const int PROC_ID,
    const int PROC_NUM, 
    const std::function<void(const std::vector<int>&)>& callback) {

    int i = 1;
    for(; i <= LEN; ++i) {
        if(necklace_count(i, alphabet.size()) >= PROC_NUM * 1000) break;
    }
    std::vector<std::pair<std::vector<int>, int>> work;
    if(PROC_NUM > 1 && i < LEN) {

        boost::multiprecision::cpp_int count = 0;
        generate_necklaces_prefix(i, alphabet, [&](const std::vector<int>& seq, const int period) {
            ++count;
            if(count % PROC_NUM == PROC_ID) {
                work.push_back({seq, period});
            }
        });

    } else {
        work.push_back({std::vector<int>{}, 0});
    }

    for(auto& [seq, period] : work) {
        generate_necklaces_prefix(LEN, alphabet, [&](const std::vector<int>& full_seq, const int period) {
            if(LEN % period == 0) {
                callback(full_seq);
            }
        }, std::ref(seq), seq.size(), period);
    }
}