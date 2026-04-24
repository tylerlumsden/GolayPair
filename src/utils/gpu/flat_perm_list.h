#pragma once
#include <memory>
#include <vector>

using PermList = std::vector<std::vector<std::vector<int>>>;

class FlatPermList {
public:
    explicit FlatPermList(const PermList& permutations);
    ~FlatPermList();
    FlatPermList(const FlatPermList&) = delete;
    FlatPermList& operator=(const FlatPermList&) = delete;

    struct View;
    View get_view();

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
