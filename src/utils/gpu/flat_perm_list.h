#pragma once
#include <memory>
#include <vector>

using PermList = std::vector<std::vector<std::vector<int>>>;

struct FlatPermListData {
    int* indexes;
    int  indexes_size;
    int* data;
    int  data_size;
    int  permutation_size;
};

class FlatPermList {
public:
    explicit FlatPermList(const PermList& permutations);
    ~FlatPermList();
    FlatPermList(const FlatPermList&) = delete;
    FlatPermList& operator=(const FlatPermList&) = delete;

    FlatPermListData data();

    struct View;
    View get_view();

private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};
