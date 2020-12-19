#include <string>
#include <vector>
#include <stdexcept>

std::vector<int64_t> readIntegers(const std::string &fileName);

std::vector<std::string> readStrings(const std::string &fileName);

std::vector<std::string> split(const std::string &string, const std::string& delimiter);