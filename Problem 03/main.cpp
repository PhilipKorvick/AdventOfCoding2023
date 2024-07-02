#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ranges>
using namespace std;

// used to keep track of where a number is and what number it is.
struct numberInfo {
    numberInfo(int line_, int start_, int end_, int value_): 
        line(line_),
        start(start_),
        end(end_),
        value(value_)
        {}
    numberInfo(){}

    int line = 0;
    int start = 0;
    int end = 0;
    int value = 0;
};

struct geerSymbolLocation{
    geerSymbolLocation(int line_, int pos_):
        line(line_),
        pos(pos_)
    {};
    geerSymbolLocation(bool exists_):
        exists(exists_)
    {};
    int line = 0;
    int pos = 0;
    bool exists = true;
};

vector<geerSymbolLocation> findGeerLocations(vector<string>& inputDataLines){
    vector<geerSymbolLocation> geerPositioins;
    int activeLine = 0;
    for (auto& inputDataLine : inputDataLines) {
        int pos = 0;
        while (pos = inputDataLine.find_first_of("*", pos) != string::npos){
            geerPositioins.emplace_back(activeLine, pos);
        }   
        activeLine++;
    }
    return geerPositioins;
}

// finds if the number is a part number by finding adjacent symbols
int checkIfPartNumber(vector<string>& inputDataLines, numberInfo& numberData){
    char const* notSymbols = "0123456789.";
    int result = 0;
    int adjacentStart = numberData.start -1;
    
    int adjacentLength = 3 + numberData.end - numberData.start;
    if(adjacentStart < 0){
        adjacentStart = 0;
        --adjacentLength;
    }
    if(numberData.end == 140)--adjacentLength;
    string topCharacters = numberData.line > 0 ? inputDataLines[numberData.line - 1].substr(adjacentStart, adjacentLength) : "";
    string bottomeCharacters = numberData.line < inputDataLines.size() -1 ? inputDataLines[numberData.line + 1].substr(adjacentStart, adjacentLength) : "";
    string leftCharacter = adjacentStart > 0 ? inputDataLines[numberData.line].substr(numberData.start-1,1) : "";
    string rightCharacter = adjacentStart + adjacentLength <= inputDataLines.size()-1 ? inputDataLines[numberData.line].substr(numberData.end+1,1) : "";
    string adjacentCharacters = topCharacters + leftCharacter + rightCharacter + bottomeCharacters;
    if(adjacentCharacters.find_first_not_of(notSymbols)!= string::npos)result = numberData.value;
    return result;
}

geerSymbolLocation findGeerNumberCombo(vector<string>& inputDataLines, numberInfo& numberData){
    int adjacentStart = numberData.start -1;
    
    int adjacentLength = 3 + numberData.end - numberData.start;
    if(adjacentStart < 0){
        adjacentStart = 0;
        --adjacentLength;
    }
    if(numberData.end == 140)--adjacentLength;
    string topCharacters = numberData.line > 0 ? inputDataLines[numberData.line - 1].substr(adjacentStart, adjacentLength) : "";
    string bottomeCharacters = numberData.line < inputDataLines.size() -1 ? inputDataLines[numberData.line + 1].substr(adjacentStart, adjacentLength) : "";
    string leftCharacter = adjacentStart > 0 ? inputDataLines[numberData.line].substr(numberData.start-1,1) : "";
    string rightCharacter = adjacentStart + adjacentLength <= inputDataLines.size()-1 ? inputDataLines[numberData.line].substr(numberData.end+1,1) : "";
    int geerPos = topCharacters.find_first_of("*");
    if(geerPos!= string::npos){
        return geerSymbolLocation(numberData.line - 1, geerPos + adjacentStart);
    }
    geerPos = bottomeCharacters.find_first_of("*");
    if(geerPos != string::npos){
        return geerSymbolLocation(numberData.line + 1, geerPos + adjacentStart);
    }
    if(leftCharacter.compare("*") == 0){
        return geerSymbolLocation(numberData.line, numberData.start- 1);
    }
    if(rightCharacter.compare("*") == 0){
        return geerSymbolLocation(numberData.line, numberData.end + 1);
    }
    return geerSymbolLocation(false);
}

// finds numbers in an array of strings and returns the list of numberInfo structs that it found
vector<numberInfo> findNumbers(vector<string>& inputDataLines){
    vector<numberInfo> numberPositioins;
    char const* digits = "0123456789";
    int activeLine = 0;
    for (auto& inputDataLine : inputDataLines) {
        int start = 0;
        int end = 0;
        while (true){
            start = inputDataLine.find_first_of(digits, end);
            end = inputDataLine.find_first_not_of(digits, start);
            if(start == string::npos){
                break;
            }
            numberPositioins.emplace_back(activeLine, start, end != string::npos ? end-1 : 140, stoi(inputDataLine.substr(start, end - start)));
        }   
        activeLine++;
    }
    return numberPositioins;
} 

// reads input file into a vector of strings
void loadInput(const string& filePath, vector<string>& inputDataLines){
    ifstream inputReader(filePath);
    if(!inputReader.is_open()){
        cout<< "did not open the file" << endl;
    }
    // Read each line of the input data
    string line;
    while(getline(inputReader,  line)){
        inputDataLines.push_back(line);
    }
    return;
}

int main(){
    int checkSum1 = 0;
    int checkSum2 = 0;
    const string filePath = "C:\\Users\\Clem\\Documents\\Development\\CPP_Projects\\AdventOfCode2023\\Problem 3\\PhilipKorvick-AdventOfCoding2023_03\\input.txt";
    vector<string> inputDataLines;
    loadInput(filePath, inputDataLines);
    vector<numberInfo> numberPositions = findNumbers(inputDataLines);
    vector<pair<geerSymbolLocation, numberInfo>> geerNumberPairs;
    for (auto& numberPosition : numberPositions){
        checkSum1 += checkIfPartNumber(inputDataLines, numberPosition);
        geerSymbolLocation geer = findGeerNumberCombo(inputDataLines, numberPosition);
        if(geer.exists){
            geerNumberPairs.emplace_back(geer, numberPosition);
        }
    }
    sort(geerNumberPairs.begin(), geerNumberPairs.end(), [](pair<geerSymbolLocation, numberInfo>& a, pair<geerSymbolLocation, numberInfo>& b){
            if(a.first.line < b.first.line) return true;
            if(a.first.line == b.first.line) return a.first.pos < b.first.pos;
            return false;
        });
    int lineEcho = 0;
    int posEcho = 0;
    int valueEcho = 0;
    for(auto& geerNumberPair : geerNumberPairs){
        if(lineEcho == geerNumberPair.first.line && posEcho == geerNumberPair.first.pos) checkSum2 += (geerNumberPair.second.value * valueEcho);
        lineEcho = geerNumberPair.first.line;
        posEcho = geerNumberPair.first.pos;
        valueEcho = geerNumberPair.second.value;
    }
    cout << "checksum 1: " << checkSum1 << endl;
    cout << "checksum 2: " << checkSum2 << endl;
    return 0;
}