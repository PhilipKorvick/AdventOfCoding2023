#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cstdint>
#include <numeric>
using namespace std;

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

vector<int> calculateNextNumber(const vector<vector<int>>& inputreadings){
    vector<int> result;
    for (const vector<int> readings : inputreadings){
        //ToDo: recursively calculate interpalation
        //ToDO: calculate projection
        //ToDo: add final projection to result
    }
    return result;
}

int main(){
    const string filePath = "input.txt";
    const vector<string> inputLines = getInputLines(filePath);
    const vector<vector<int>> inputreadings = parseReadings(inputLines);
    const vector<int> nextNumberInReadings = calculateNextNumber(inputreadings);
    return 0;
}