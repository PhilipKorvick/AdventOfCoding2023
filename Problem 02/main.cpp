#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> split (const string &str, const char delim) {
    vector<string> result;
    stringstream ss (str);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

bool validateRound(const string& round){
    const int maxRed = 12;
    const int maxGreen = 13;
    const int maxBlue = 14;
    const vector<string> cubeGroups = split(round, ',');
    for(auto& cubeGroup : cubeGroups){
        vector<string> data = split(cubeGroup, ' ');
        if(data[2].compare("red") == 0 && maxRed < stoi(data[1])) return false;
        if(data[2].compare("green") == 0 && maxGreen < stoi(data[1])) return false;
        if(data[2].compare("blue") == 0 && maxBlue < stoi(data[1])) return false;
    }
    return true;
}

void calculateRound(const string& round, int& maxRed, int& maxGreen, int& maxBlue){
    const vector<string> cubeGroups = split(round, ',');
    for(auto& cubeGroup : cubeGroups){
        vector<string> data = split(cubeGroup, ' ');
        if(data[2].compare("red") == 0 && maxRed < stoi(data[1])) maxRed = stoi(data[1]);
        if(data[2].compare("green") == 0 && maxGreen < stoi(data[1])) maxGreen = stoi(data[1]);
        if(data[2].compare("blue") == 0 && maxBlue < stoi(data[1])) maxBlue = stoi(data[1]);
    }
    return;
}

int parseGame(const string& gameStr){
    int redCubes = 0;
    int greenCubes = 0;
    int blueCubes = 0;
    const vector<string> gameStringParts = split(gameStr, ':');
    int gameNumber = stoi(gameStringParts[0].substr(5, gameStringParts[0].size()-1));
    const vector<string> rounds = split(gameStringParts[1], ';');
    for (auto round : rounds) {
        calculateRound(round, redCubes, greenCubes, blueCubes);
    }
    return redCubes * greenCubes * blueCubes;
}

int main (){
    string line;
    int checksum = 0;
    const string filePath = "input.txt";
    ifstream inputData(filePath);
    if(!inputData.is_open()){
        cout<< "did not open the file" << endl;
    }
    while (getline(inputData, line)){
        checksum += parseGame(line);
    }
    cout << checksum << endl;

    return 0;
}