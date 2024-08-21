#include <iostream>
#include <string>
#include <vector>
#include "../Common/common.h"
#include "problem02.h"

bool validateRound(const gameData& game)noexcept{
    if(12 < game.maxRedCubes) return false;
    if(13 < game.maxGreenCubes) return false;
    if(14 < game.maxBlueCubes) return false;
    return true;
}

void calculateRound(const std::string& round, int& maxRed, int& maxGreen, int& maxBlue){
    const std::vector<std::string> cubeGroups = split(round, ',');
    for(auto& cubeGroup : cubeGroups){
        std::vector<std::string> data = split(cubeGroup, ' ');
        if(data.size() != 3) throw std::invalid_argument("Malformed input: " + round);
        if(data[2].compare("red") == 0 && maxRed < stoi(data[1])) maxRed = stoi(data[1]);
        if(data[2].compare("green") == 0 && maxGreen < stoi(data[1])) maxGreen = stoi(data[1]);
        if(data[2].compare("blue") == 0 && maxBlue < stoi(data[1])) maxBlue = stoi(data[1]);
    }
    return;
}

gameData parseGame(const std::string& gameStr){
    gameData game;
    const std::vector<std::string> gameStringParts = split(gameStr, ':');
    game.gameNumber = stoi(gameStringParts[0].substr(5, gameStringParts[0].size()-1));
    const std::vector<std::string> rounds = split(gameStringParts[1], ';');
    for (auto round : rounds) {
        try {
        calculateRound(round, game.maxRedCubes, game.maxGreenCubes, game.maxBlueCubes);
        }
        catch(const std::invalid_argument& e){
            std::cout << "Game Number: " << game.gameNumber << " " << e.what() << std::endl;
            throw std::invalid_argument("Invalid input file.");
        }
    }
    return game;
}

void problem02 (const std::string& filePath){
    int solution1 = 0;
    int solution2 = 0;
    std::vector<std::string> lines = getInputLines(filePath);
    for (const std::string& line : lines){
        try{
            const gameData game = parseGame(line);
            solution1 += validateRound(game) ? game.gameNumber : 0;
            solution2 += game.maxRedCubes * game.maxGreenCubes * game.maxBlueCubes;
        } catch (const std::invalid_argument& e){
            std:: cout << "Exception thrown in problem 02: " << e.what() << std::endl;
            return;
        }
    }
    std::cout << "Solution problem 2.1: " << solution1 << std::endl;
    std::cout << "Solution problem 2.2: " << solution2 << std::endl;
}