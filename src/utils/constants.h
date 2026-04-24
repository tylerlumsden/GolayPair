#pragma once
#include <string_view>
#include <string>
#include <format>

namespace Constants {
    inline std::string get_file_path_a(const int ORDER, const std::string& TEMP_PATH) {
        return std::format("{}/order-{}/{}-filtered-{}_{}", TEMP_PATH, ORDER, ORDER, "a", 1);
    }

    inline std::string get_file_path_b(const int ORDER, const std::string& TEMP_PATH) {
        return std::format("{}/order-{}/{}-filtered-{}_{}", TEMP_PATH, ORDER, ORDER, "b", 1);
    }
}