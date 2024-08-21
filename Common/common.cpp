#include "common.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::vector<std::string> getInputLines(const std::string& filePath)noexcept{
    std::vector<std::string> result;
    try{
        std::ifstream inputData(filePath);
        if(!inputData.is_open()){
            std::cout<< "did not open the file" << std::endl;
        }
        std::string line;
        while (getline(inputData, line)){
            result.emplace_back(line);
        }
        inputData.close();
    }catch(const std::exception& e){
        std::cout << "Exception" << e.what() << std::endl;
    }
    return result;
}
 
std::vector<std::string> split (const std::string &str, const char delim)noexcept {
    std::vector<std::string> result;
    std::stringstream ss (str);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}