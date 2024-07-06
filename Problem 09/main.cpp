#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cstdint>
#include <numeric>
using namespace std;

vector<string> split (const string& str, const char& delim) {
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

vector<vector<int>> parseReadings(const vector<string>& inputlines){
    vector<vector<int>> result;
    for(const string& inputLine : inputlines){
        vector<string> inputDataStrings = split(inputLine, ' ');
        vector<int> inputData;
        for(const string& inputString : inputDataStrings){
            inputData.push_back(stoi(inputString));
        }
        result.push_back(inputData);
    }
    return result; 
}

bool allNotZeros(const vector<int>& datas){
    for(const int& data : datas){
        if(data != 0)return true;
    }
    return false;
}

vector<int> calculateDifferenceArray(const vector<int>& inputReadings){
    vector<int> result;
    for(int reading = 1; reading < inputReadings.size(); reading++){
        result.push_back(inputReadings[reading] - inputReadings[reading -1]);
    }
    return result;
}

vector<vector<int>> calculateInterpolation(const vector<int>& inputReadings){
    vector<vector<int>> result;
    result.push_back(inputReadings);
    while(allNotZeros(result.back())){
        result.push_back(calculateDifferenceArray(result.back()));
    }
    return result;
}

int calculateProjection(vector<vector<int>> projectionData){
    projectionData.back().emplace_back(0);
    for(int layer = projectionData.size()-2; layer >= 0; layer--){
        projectionData[layer].push_back(projectionData[layer].back() + projectionData[layer + 1].back());
    }
    return projectionData.front().back();
}

int calculateProjectionHistory(vector<vector<int>> projectionData){
    projectionData.back().insert(projectionData.back().begin(), 0);
    for(int layer = projectionData.size()-2; layer >= 0; layer--){
        projectionData[layer].insert(projectionData[layer].begin(), projectionData[layer].front() - projectionData[layer + 1].front());
    }
    return projectionData.front().front();
}

int main(){
    int answer1 = 0;
    int answer2 = 0;
    const string filePath = "input.txt";
    const vector<string> inputLines = getInputLines(filePath);
    const vector<vector<int>> inputReadings = parseReadings(inputLines);
    for(const vector<int> inputReading : inputReadings){
        vector<vector<int>> readingInterpolation = calculateInterpolation(inputReading);
        answer1 += calculateProjection(readingInterpolation);
        answer2 += calculateProjectionHistory(readingInterpolation);
    }
    cout << "Answer to Problem 1: " << answer1 << endl;
    cout << "Answer to Problem 2: " << answer2 << endl;
    return 0;
}