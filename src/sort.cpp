#include<format>
#include<string>
#include<vector>
#include<iostream>
#include <numeric>

int GNU_sort(const std::vector<std::string>& IN_PATH, const std::string& OUT_PATH) {
    std::string in_files = std::accumulate(
        std::next(IN_PATH.begin()), 
        IN_PATH.end(),
        IN_PATH[0],
        [](const std::string& a, const std::string& b) { 
            return a + " " + b; 
        }
    );

    std::string cmd = std::format("sort {} | uniq > {}", in_files, OUT_PATH);
    if(std::system(cmd.c_str()) != 0) {
        std::cerr << "Sort failed\n";
        return 1;
    }
    return 0;
}