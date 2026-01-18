int necklace_count(int length, int alphabet_size);

void generate_necklaces_prefix(const int LEN, 
    const std::set<int>& alphabet, 
    std::function<void(const std::vector<int>&)> callback);