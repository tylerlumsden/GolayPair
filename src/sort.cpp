#include<format>
#include<string>
#include<iostream>

int GNU_sort(const std::string& IN_PATH, const std::string& OUT_PATH) {
    std::string cmd = std::format("sort {} | uniq > {}", IN_PATH, OUT_PATH);
    if(std::system(cmd.c_str()) != 0) {
        std::cerr << "Sort failed\n";
        return 1;
    }
    return 0;
}