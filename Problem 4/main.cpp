#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> getInputLines(const string& filePath){
    vector<string> result;
    ifstream inputData(filePath);
    if(!inputData.is_open()){
        cout<< "did not open the file" << endl;
    }
    string line;
    while (getline(inputData, line)){
        result.emplace_back(line);
    }
    return result;
}

vector<string> getScoringGameNubmers(const string& gameCard){
    int scoringNumbersStart = 9;
    vector<string> scoringNumbers;
    for(int scoringNumber = 0; scoringNumber < 10; scoringNumber++){
        scoringNumbers.push_back(gameCard.substr(scoringNumbersStart, 3));
        scoringNumbersStart += 3;
    }
    return scoringNumbers;
}

int calculateGameMatches(const string& gameCard){
    int matches = 0;
    vector<string> scoringNumbers = getScoringGameNubmers(gameCard);
    for (const string& scoringNumber : scoringNumbers){
        if(gameCard.find(scoringNumber, 40)!= string::npos){
            matches++;
        } 
    }
    return matches;
}

int calculateGamePoints(const int& matches){
    return matches > 0 ? 1 << (matches - 1) : 0;
}

int calculateNumberOfCards(vector<int>& gameCardCounts, const int& matches, const int& gameNumber){
    int currentNumberOfCards = gameCardCounts[gameNumber];
    for(int count = 1; count <= matches; count++){
        gameCardCounts[gameNumber + count] += currentNumberOfCards;
    }
    return currentNumberOfCards;
}

int main(){
    int checksum = 0;
    int numberOfCards = 0;
    const string filePath = "C:\\Users\\Clem\\Documents\\Development\\CPP_Projects\\AdventOfCode2023\\Problem 4\\AdventOfCoding2023_04\\input.txt";
    const vector<string> gameCards = getInputLines(filePath);
    vector<int> gameCardCouts (gameCards.size(), 1);
    int gameNumber = 0;
    for (const string& gameCard : gameCards){
        int matches = calculateGameMatches(gameCard);
        checksum += calculateGamePoints(matches);
        numberOfCards += calculateNumberOfCards(gameCardCouts, matches, gameNumber);
        gameNumber++;
    }
    cout << checksum << endl;
    cout << numberOfCards << endl;
    return 1; 
}