#ifndef COMMON
#define COMMON
#include <string>
#include <vector>

/// @brief reads a text file and returns the file as a vector of strings
/// @param  string path to file
/// @return vector of strings that represent each line of the given file
std::vector<std::string> getInputLines(const std::string&)noexcept;

/// @brief Takes a string and splits the string into smaller strings based a given deliminator character
/// @param str The string that is to be broken up
/// @param delim character that indicates where the main string should be broken
/// @return vector of strings that were separated by the delimiter 
std::vector<std::string> split (const std::string &str, const char delim)noexcept;
#endif