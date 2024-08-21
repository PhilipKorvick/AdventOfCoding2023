#include <iostream>
#include <string>
#include <vector>
#include "../Common/common.h"
#include "problem04.h"

std::vector<std::string> getScoringGameNumbers(const std::string& gameCard){
    int scoringNumbersStart = 9;
    std::vector<std::string> scoringNumbers;
    for(int scoringNumber = 0; scoringNumber < 10; scoringNumber++){
        scoringNumbers.push_back(gameCard.substr(scoringNumbersStart, 3));
        scoringNumbersStart += 3;
    }
    return scoringNumbers;
}

int calculateGameMatches(const std::string& gameCard){
    int matches = 0;
    std::vector<std::string> scoringNumbers = getScoringGameNumbers(gameCard);
    for (const std::string& scoringNumber : scoringNumbers){
        if(gameCard.find(scoringNumber, 40)!= std::string::npos){
            matches++;
        } 
    }
    return matches;
}

int calculateGamePoints(const int& matches){
    return matches > 0 ? 1 << (matches - 1) : 0;
}

int calculateNumberOfCards(std::vector<int>& gameCardCounts, const int& matches, const int& gameNumber){
    int currentNumberOfCards = gameCardCounts[gameNumber];
    for(int count = 1; count <= matches; count++){
        gameCardCounts[gameNumber + count] += currentNumberOfCards;
    }
    return currentNumberOfCards;
}

void problem04 (const std::string& filePath){
    int solution1 = 0;
    int solution2 = 0;
    const std::vector<std::string> gameCards = getInputLines(filePath);
    std::vector<int> gameCardCounts (gameCards.size(), 1);
    int gameNumber = 0;
    for (const std::string& gameCard : gameCards){
        int matches = calculateGameMatches(gameCard);
        solution1 += calculateGamePoints(matches);
        solution2 += calculateNumberOfCards(gameCardCounts, matches, gameNumber);
        gameNumber++;
    }

    std::cout << "Solution problem 4.1: " << solution1 << std::endl;
    std::cout << "Solution problem 4.2: " << solution2 << std::endl;

}