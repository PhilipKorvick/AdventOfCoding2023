#ifndef PROBLEM02
#define PROBLEM02
#include <string>

/// @brief collection of data that represents the important information of the gem counting game
/// @param gameNumber the ID of the game that is being played
/// @param maxRedCubes the highest number of red gems observed in the current game
/// @param maxGreenCubes the highest number of green gems observed in the current game
/// @param maxBlueCubes the highest number of blue gems observed in the current game
struct gameData {
    int gameNumber = 0, maxRedCubes = 0, maxGreenCubes = 0, maxBlueCubes = 0;
};

/// @brief determine if there are are no more than 12 red gems, 13 green gems and, 14 blue gems in a given game
/// @param game collection of data that represents the important information of the gem counting game
/// @return returns the boolean value of if the game was valid or not
bool validateRound(const gameData& game)noexcept;

/// @brief Used to determine if the number of any colored gem is greater than the current maximum and if so update the current maximum for each round 
/// @param round a string containing a list of gem colors and the count of how many gems of that color are in the round
/// @param maxRed a reference to the highest number of red gems observed in the current game
/// @param maxGreen a reference to the highest number of green gems observed in the current game
/// @param maxBlue a reference to the highest number of blue gems observed in the current game
void calculateRound(const std::string& roundsStr, int& maxRed, int& maxGreen, int& maxBlue);

/// @brief creates a record of the gem game that was played based on the string passed in that represents the game
/// @param gameStr string that represents a gem game that was played
/// @return a record of the gem game that was played with the game ID number, and highest number of red, green, and blue gems observed
gameData parseGame(const std::string& gameStr);

/// @brief This program solves the second problem of the Advent of Code 2023
/// @param filePath path to input file for the problem
void problem02 (const std::string& filePath);
#endif
