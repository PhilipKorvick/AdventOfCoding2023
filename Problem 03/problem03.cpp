#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "../Common/common.h"
#include "problem03.h"

void getAdjacentCharacters(const std::vector<std::string>& inputDataLines, numberInfo& numberData)noexcept{
    int adjacentStart = numberData.start -1;
    int adjacentLength = 3 + numberData.end - numberData.start;
    if(adjacentStart < 0){
        adjacentStart = 0;
        --adjacentLength;
    }
    if(numberData.end == 140)--adjacentLength;
    numberData.topCharacters = numberData.line > 0 ? inputDataLines[numberData.line - 1].substr(adjacentStart, adjacentLength) : "";
    numberData.bottomCharacters = numberData.line < inputDataLines.size() -1 ? inputDataLines[numberData.line + 1].substr(adjacentStart, adjacentLength) : "";
    numberData.leftCharacter = adjacentStart > 0 ? inputDataLines[numberData.line].substr(numberData.start-1,1) : "";
    numberData.rightCharacter = adjacentStart + adjacentLength <= inputDataLines.size()-1 ? inputDataLines[numberData.line].substr(numberData.end+1,1) : "";
    numberData.adjacentCharacters = numberData.topCharacters + numberData.leftCharacter + numberData.rightCharacter + numberData.bottomCharacters;
}

void findIfGear(const std::vector<std::string>& inputDataLines, numberInfo& numberData)noexcept{
    int gearPos = numberData.topCharacters.find_first_of("*");
    if(gearPos!= std::string::npos){
        numberData.gear.exists=true;
        numberData.gear.line = numberData.line - 1;
        numberData.gear.pos = gearPos + numberData.start - 1;
        return;
    }
    gearPos = numberData.bottomCharacters.find_first_of("*");
    if(gearPos != std::string::npos){
        numberData.gear.exists=true;
        numberData.gear.line = numberData.line + 1;
        numberData.gear.pos = gearPos + numberData.start - 1;
        return;
    }
    if(numberData.leftCharacter.compare("*") == 0){
        numberData.gear.exists=true;
        numberData.gear.line = numberData.line;
        numberData.gear.pos = numberData.start -1;
        return;
    }
    if(numberData.rightCharacter.compare("*") == 0){
        numberData.gear.exists=true;
        numberData.gear.line = numberData.line;
        numberData.gear.pos = numberData.end + 1;
        return;
    }
}

void checkIfPartNumber(const std::vector<std::string>& inputDataLines, numberInfo& numberData)noexcept{
    char const* notSymbols = "0123456789.";
    getAdjacentCharacters(inputDataLines, numberData);
    numberData.partNumber = (numberData.adjacentCharacters.find_first_not_of(notSymbols)!= std::string::npos);
    findIfGear(inputDataLines, numberData);
}

std::vector<numberInfo> findPartNumbers(const std::vector<std::string>& inputDataLines)noexcept{
    std::vector<numberInfo> numberPositions;
    char const* digits = "0123456789";
    int activeLine = 0;
    for (auto& inputDataLine : inputDataLines) {
        int start = 0;
        int end = 0;
        while (true){
            start = inputDataLine.find_first_of(digits, end);
            end = inputDataLine.find_first_not_of(digits, start);
            if(start == std::string::npos){
                break;
            }
            numberInfo possibleNumber = {activeLine, start, end != std::string::npos ? end-1 : 140, stoi(inputDataLine.substr(start, end - start))};
            checkIfPartNumber(inputDataLines, possibleNumber);
            if(possibleNumber.partNumber)numberPositions.emplace_back(possibleNumber);
        }   
        activeLine++;
    }
    return numberPositions;
} 

int calculateGearRation(std::vector<numberInfo>& numberPositions, numberInfo& numberPosition)noexcept{
    auto gearPair = std::find_if(numberPositions.begin(), numberPositions.end(), [numberPosition](numberInfo numberPair){
        return 
        numberPair.gear.exists && 
        !numberPair.gear.paired && 
        numberPosition.gear.line == numberPair.gear.line && 
        numberPosition.gear.pos == numberPair.gear.pos && 
        numberPosition.value != numberPair.value;
    });
    if(gearPair != numberPositions.end()){
        numberPosition.gear.paired = true;
        gearPair->gear.paired = true;
        return gearPair->value * numberPosition.value;
    }
    return 0;
}

void problem03 (const std::string& filePath){
    int solution1 = 0;
    int solution2 = 0;
    std::vector<std::string> inputDataLines = getInputLines(filePath);
    std::vector<numberInfo> numberPositions = findPartNumbers(inputDataLines);
    for (auto& numberPosition : numberPositions){
        solution1 += numberPosition.value;
        if(numberPosition.gear.exists && !numberPosition.gear.paired){
            solution2 += calculateGearRation(numberPositions, numberPosition);
        }
    }

    std::cout << "Solution problem 3.1: " << solution1 << std::endl;
    std::cout << "Solution problem 3.2: " << solution2 << std::endl;
}