#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "../Common/common.h"
#include "problem01.h"

/// @brief setting up map between spelling of numbers and their numeric representation
std::map<std::string, std::string> numbers = {{"one","1"},{"two","2"},{"three","3"},{"four","4"},{"five","5"},{"six","6"},{"seven","7"},{"eight","8"},{"nine", "9"}};

void convertNumber(std::string& line)noexcept{
    try{
        // look for each of the numbers' spellings
        for(auto number : numbers){
            bool foundString = false;
            // check for multiple of the same spelled number
            do{
                foundString = false;
                size_t linePosition = line.find(number.first);
                // if a spelled number is found do loop again and put the numeric value in the second letter of the number so that it does not disturb overlapping letters from other number spellings
                if(linePosition!=std::string::npos){
                    foundString = true;
                    line.replace(linePosition+1, 1, number.second);
                }
            }while (foundString);
        }
    } catch(std::exception& e){
    std::cout << "Exception" << e.what() << std::endl;
    }
}

int findNumber(const std::string& line)noexcept{
    try{
    char firstNumber = line[line.find_first_of("123456789")];
    char lastNumber = line[line.find_last_of("123456789")];
    return stoi(std::string{firstNumber, lastNumber});
    } catch(std::exception& e){
        std::cout << "Exception" << e.what() << std::endl;
    }
    return 0;
}

void problem01(const std::string& filePath){
    int solution1 = 0;
    int solution2 = 0;
    // Get the input data
    const std::vector<std::string> lines = getInputLines(filePath);
    for(std::string line : lines){
        solution1 += findNumber(line);
        // converts a spelled out number into the respective numeric digit
        convertNumber(line);
        // find the numbers in the data and add them to the running total
        solution2 += findNumber(line);
    }
    // display final total
    std::cout << "Solution problem 1.1: " << solution1 << std::endl;
    std::cout << "Solution problem 1.2: " << solution2 << std::endl;
}