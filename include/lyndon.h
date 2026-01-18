#include <boost/multiprecision/cpp_int.hpp>

boost::multiprecision::cpp_int necklace_count(int length, int alphabet_size);

void generate_necklaces_wrapper(const int LEN, 
const std::vector<int>& alphabet, 
const int PROC_ID,
const int PROC_NUM, 
const std::function<void(const std::vector<int>&)>& callback);