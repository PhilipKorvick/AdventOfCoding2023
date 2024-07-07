#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <cstdint>
#include <numeric>
using namespace std;

enum direction{
    east,
    north,
    west,
    south
};

struct location{
    location(int line_, int coll_):
    line(line_),
    coll(coll_)
    {};
    location(int line_, int coll_, direction from_):
    line(line_),
    coll(coll_),
    from(from_)
    {};
    int getLine(){return line;};
    int getColl(){return coll;};
    direction getfrom(){return from;};
private:
    int line;
    int coll;
    direction from;
};

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

location findStartingPoint(const vector<string>& inputLines, const char& startingLetter){
    int line = 0;
    int coll = 0;
    for(const string& inputLine : inputLines){
        coll = inputLine.find_first_of(startingLetter);
        if(coll != string::npos) return location(line, coll);
        line++;
    }
    return location(-1, -1);
}

vector<location> findFirstStep(const vector<string> inputLines, location startingPoint){
    vector<location> result;
    char northChar = inputLines[startingPoint.getLine() -1][startingPoint.getColl()];
    char eastChar = inputLines[startingPoint.getLine()][startingPoint.getColl() +1];
    char southChar = inputLines[startingPoint.getLine() +1][startingPoint.getColl()];
    char westChar = inputLines[startingPoint.getLine()][startingPoint.getColl() -1];
    if(northChar == 'F' || northChar == '|' || northChar == '7') result.emplace_back(startingPoint.getLine() -1, startingPoint.getColl(), south);
    if(eastChar == '7' || eastChar == '-' || eastChar == 'J') result.emplace_back(startingPoint.getLine(), startingPoint.getColl() +1, west);
    if(southChar == 'L' || southChar == '|' || southChar == 'J') result.emplace_back(startingPoint.getLine() +1, startingPoint.getColl(), north);
    if(westChar == 'L' || westChar == '-' || westChar == 'F') result.emplace_back(startingPoint.getLine(), startingPoint.getColl() -1, east);
    return result;
}

vector<location> findNextStep(const vector<string>& inputLines, vector<location> stepLocations){
    vector<location> result;
    for(location& stepLocation : stepLocations){
        switch(inputLines[stepLocation.getLine()][stepLocation.getColl()]){
            case 'F':
                if(stepLocation.getfrom() == south){ 
                    result.emplace_back(stepLocation.getLine(), stepLocation.getColl() + 1, west);
                } else{ 
                    result.emplace_back(stepLocation.getLine() + 1, stepLocation.getColl(), north);
                };
                break;
            case '7':
                if(stepLocation.getfrom() == south){ 
                    result.emplace_back(stepLocation.getLine(), stepLocation.getColl() - 1, east);
                } else{ 
                    result.emplace_back(stepLocation.getLine() + 1, stepLocation.getColl(), north);
                };
                break;
            case 'J':
                if(stepLocation.getfrom() == north){ 
                    result.emplace_back(stepLocation.getLine(), stepLocation.getColl() - 1, east);
                } else{ 
                    result.emplace_back(stepLocation.getLine() - 1, stepLocation.getColl(), south);
                };
                break;
            case 'L':
                if(stepLocation.getfrom() == north){ 
                    result.emplace_back(stepLocation.getLine(), stepLocation.getColl() + 1, west);
                } else{ 
                    result.emplace_back(stepLocation.getLine() - 1, stepLocation.getColl(), south);
                };
                break;
            case '|':
                if(stepLocation.getfrom() == south){ 
                    result.emplace_back(stepLocation.getLine() - 1, stepLocation.getColl(), south);
                } else{ 
                    result.emplace_back(stepLocation.getLine() + 1, stepLocation.getColl(), north);
                };
                break;
            case '-':
                if(stepLocation.getfrom() == west ){
                    result.emplace_back(stepLocation.getLine(), stepLocation.getColl() + 1, west);
                } else{ 
                    result.emplace_back(stepLocation.getLine(), stepLocation.getColl() - 1, east);
                };
                break;
        }
    }
    return result;
}

vector<location> findAllLocations(const vector<string>& inputLines, location& startingPoint, vector<location>& stepLocations){
    vector<location> allSteps;
    allSteps.push_back(startingPoint);
    allSteps.push_back(stepLocations[0]);
    allSteps.push_back(stepLocations[1]);
    while(stepLocations[0].getColl() != stepLocations[1].getColl() || stepLocations[0].getLine() != stepLocations[1].getLine()){
        stepLocations = findNextStep(inputLines, stepLocations);
        allSteps.push_back(stepLocations[0]);
        allSteps.push_back(stepLocations[1]);
    }
    allSteps.pop_back();
    return allSteps;
}

int main(){
    int steps = 1;
    const string filePath = "input.txt";
    const vector<string> inputLines = getInputLines(filePath);
    location startingPoint = findStartingPoint(inputLines, 'S');
    vector<location> stepLocations = findFirstStep(inputLines, startingPoint);
    vector<location> allLocations = findAllLocations(inputLines, startingPoint, stepLocations);
    cout << "Answer to problem 1: " << allLocations.size()/2 << endl;
    return 0;
}