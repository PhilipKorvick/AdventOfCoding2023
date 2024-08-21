#ifndef PROBLEM01
#define PROBLEM01
#include <string>

/// @brief converts a spelled out number into the respective numeric digit
/// @param line a string in which spelled out numbers should be converted to numeric characters
void convertNumber(std::string&)noexcept;

/// @brief finds the first and last number in a string and returns them as an int in the respective order
/// @param line a string in which numbers are placed
/// @return a number where the first number in the string is the tens digit and the second string is the ones digit
int findNumber(const std::string&)noexcept;

/// @brief Main function for problem 01
/// @param string path to input file for the problem
void problem01(const std::string&);
#endif