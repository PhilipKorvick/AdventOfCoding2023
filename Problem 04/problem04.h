#include <string>
#include <vector>

/// @brief finds and returns all of the scoring numbers for a game card
/// @param gameCard string that represents a game card
/// @return vector of strings containing the scoring numbers
std::vector<std::string> getScoringGameNumbers(const std::string& gameCard);

/// @brief finds the number of matching numbers between the game numbers and scoring numbers
/// @param gameCard string that represents a game card
/// @return the number of matching game and scoring numbers
int calculateGameMatches(const std::string& gameCard);

/// @brief calculates the number of points won for a number of matching numbers
/// @param matches number of matching numbers
/// @return score for the number of matches
int calculateGamePoints(const int& matches);

/// @brief calculates and saves the number of cards won for each game card and returns the number of game cards won for the given game
/// @param gameCardCounts a vector of integers that represents how many game cards have been won
/// @param matches the number of matches for the current game card
/// @param gameNumber the number of the game currently being played
/// @return the number of game cards that have been won in total for that game
int calculateNumberOfCards(std::vector<int>& gameCardCounts, const int& matches, const int& gameNumber);

/// @brief This program solves the forth problem of the Advent of Code 2023
/// @param filePath path to input file for the problem
void problem04 (const std::string& filePath);