#ifndef PROBLEM03
#define PROBLEM03
#include <vector>
#include <string>

/// @brief used to hold data regarding possible gear ration combination for a part number
struct gearSymbolLocation{
    /// @brief line number of gear symbol
    int line = 0;
    /// @brief character position in string of gear symbol
    int pos = 0;
    /// @brief if the part number is a gear number
    bool exists = false;
    /// @brief if the gear number has been paired with another gear number
    bool paired = false;
};

/// @brief used to hold information about numbers found in the diagram
struct numberInfo {
    /// @brief constructor for numberInfo to hod information about numbers found in the diagram
    /// @param line_ line number of the number
    /// @param start_ character number in the string where the number starts
    /// @param end_ character number in the string where the number ends
    /// @param value_ the integer format of the number
    numberInfo(int line_, int start_, int end_, int value_):
    line(line_),
    start(start_),
    end(end_),
    value(value_)
    {}
    /// @brief characters adjacent above the number
    std::string topCharacters;
    /// @brief characters adjacent below the number
    std::string bottomCharacters;
    /// @brief characters adjacent to the left of the number
    std::string leftCharacter;
    /// @brief characters adjacent to the right of the number
    std::string rightCharacter;
    /// @brief all characters adjacent to the number
    std::string adjacentCharacters;
    /// @brief line number of the number
    int line = 0;
    /// @brief character number in the string where the number starts
    int start = 0;
    /// @brief character number in the string where the number ends
    int end = 0;
    /// @brief the integer format of the number
    int value = 0;
    /// @brief indicator to show if there is an adjacent part symbol
    bool partNumber = false;
    /// @brief if there is an adjacent gear symbol to the number information about that number is found here
    gearSymbolLocation gear;
};

/// @brief get all of the adjacent characters for a given number
/// @param inputDataLines reference to diagram information
/// @param numberData reference to a number on the diagram to be manipulated
void getAdjacentCharacters(const std::vector<std::string>& inputDataLines, numberInfo& numberData)noexcept;

/// @brief determine if the part number could be part of a gear ration and capture the data about the gear character
/// @param inputDataLines reference to diagram information
/// @param numberData reference to a number on the diagram to be manipulated
void findIfGear(const std::vector<std::string>& inputDataLines, numberInfo& numberData)noexcept;

/// @brief determine if the number on the diagram is a part number by finding an adjacent part character
/// @param inputDataLines reference to diagram information
/// @param numberData reference to a number on the diagram to be manipulated
void checkIfPartNumber(const std::vector<std::string>& inputDataLines, numberInfo& numberData)noexcept;

/// @brief parses through the full diagram input and returns all of the part numbers in a vector
/// @param inputDataLines reference to diagram information
/// @return list of all part numbers in the diagram
std::vector<numberInfo> findPartNumbers(const std::vector<std::string>& inputDataLines)noexcept;

/// @brief finds the connection between two gear numbers and returns their gear ratio
/// @param numberPositions list of all part numbers on the diagram
/// @param numberPosition reference to a number on the diagram to be manipulated
/// @return gear ration which is the product of two gear numbers sharing the same gear icon
int calculateGearRation(std::vector<numberInfo>& numberPositions, numberInfo& numberPosition)noexcept;

/// @brief This program solves the third problem of the Advent of Code 2023
/// @param filePath path to input file for the problem
void problem03 (const std::string& filePath);

#endif