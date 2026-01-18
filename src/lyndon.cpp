#include <cstdint>
#include <vector>
#include<cmath>
#include<iostream>
#include<numeric>
#include<set>
#include <functional>

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

int necklace_count(int length, int alphabet_size) {
    int sum = 0; 
    for(int i = 1; i <= length; i++) {
        sum += (int)std::pow(alphabet_size, std::gcd(i, length));
    }
    return sum / length;
}

void generate_necklaces_prefix(const int LEN, 
    const std::set<int>& alphabet, 
    std::function<void(const std::vector<int>&)> callback) {

        if (LEN <= 0 || alphabet.empty()) return;

        std::vector<int> seq(LEN);

        std::function<void(int, int)> generate = [&](int i, int period) {
            if(i == LEN) {
                if(LEN % period == 0) {
                    callback(seq);
                }
                return;
            }

            seq[i] = seq[i - period];
            generate(i + 1, period);

            for (auto it = alphabet.upper_bound(seq[i - period]); it != alphabet.end(); ++it) {
                seq[i] = *it;
                generate(i + 1, i + 1);
            }
        };
    
        for(const int& character : alphabet) {
            seq[0] = character;
            generate(1, 1);
        }
}