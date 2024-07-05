#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cstdint>
#include <numeric>
using namespace std;

enum leftRight{
    lft,
    rit
};

vector<string> split (const string &str, const char& delim) {
    vector<string> result;
    stringstream ss (str);
    string item;
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}

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

vector<leftRight> parseDirections(const string& directions){
    vector<leftRight> result;
    for(const char& direction : directions){
        if(direction == 'L'){
            result.emplace_back(lft);
            continue;
        }
        if(direction == 'R'){
            result.emplace_back(rit);
            continue;
        }
        cout << "Letter: " << int(direction) << " not accounted for." << endl;
    }
    return result;
}

const map<string, pair<string, string>> parseDirectionMaps(vector<string> directionLines){
    map<string, pair<string, string>> result;
    directionLines.erase(directionLines.begin(), directionLines.begin()+2);
    for(const string& directionLine : directionLines){
        result.emplace(directionLine.substr(0,3), pair<string, string>(directionLine.substr(7,3), directionLine.substr(12,3)));
    }
    return result;
}

int followDirectionsSteps(const vector<leftRight>& directions, const map<string, pair<string,string>>& directionMaps){
    int steps = 0;
    string position = "AAA";
    while(position.compare("ZZZ") != 0){
        position = directions[steps % directions.size()] == lft ? directionMaps.find(position)->second.first : directionMaps.find(position)->second.second;
        steps++;
        if(steps == 2147483647) return -1;
    }
    return steps;
}

vector<string> findDirectionMapEndingIn (const char& letter, const map<string, pair<string,string>>& directionMaps){
    vector<string> positions;
    for(const pair<string, pair<string, string>>& directionMap : directionMaps){
        if(directionMap.first[2] == letter){
            positions.emplace_back(directionMap.first);
        }
    }
    return positions;
}

vector<int> findDirectionLoop(const vector<string>& startingNodes, const vector<leftRight>& directions, const map<string, pair<string,string>>& directionMaps){
    vector<int> result;
    for(const string& startingNode : startingNodes){
        int steps = 0;
        string position = startingNode;
        int loopLength = 1;
        while(true){
            position = directions[steps % directions.size()] == lft ? directionMaps.find(position)->second.first : directionMaps.find(position)->second.second;
            if(position[2] == 'Z'){
                result.emplace_back(loopLength);
                break;
            }
            loopLength++;
            steps++;
            if(steps == 2147483647) break;
        }
    }
    return result;
}

int main(){
    const string filePath = "input.txt";
    const vector<string> directionLines = getInputLines(filePath);
    const vector<leftRight> directions = parseDirections(directionLines[0]);
    const map<string, pair<string, string>> directionMaps = parseDirectionMaps(directionLines);
    const int solution1 = followDirectionsSteps(directions, directionMaps);
    const vector<string> startingNodes = findDirectionMapEndingIn('A', directionMaps);
    const vector<int> directionLoopLengths = findDirectionLoop(startingNodes, directions, directionMaps);
    int64_t solution2 = 1;
    for(const int& directionLoopLength : directionLoopLengths){
        solution2 = lcm(directionLoopLength, solution2);
    }
    cout << "Answer to problem 1: " << solution1 << endl;
    cout << "Answer to problem 2: " << solution2 << endl;
    return 0;
}