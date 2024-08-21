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

struct pipeInfo{
    pipeInfo(int line_, int coll_):
    line(line_),
    coll(coll_)
    {};
    pipeInfo(int line_, int coll_, direction from_):
    line(line_),
    coll(coll_),
    from(from_)
    {};
    int getLine(){return line;};
    int getColl(){return coll;};
    direction getFrom(){return from;};
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

pipeInfo findStartingPoint(const vector<string>& inputLines, const char& startingLetter){
    int line = 0;
    int coll = 0;
    for(const string& inputLine : inputLines){
        coll = inputLine.find_first_of(startingLetter);
        if(coll != string::npos) return pipeInfo(line, coll);
        line++;
    }
    return pipeInfo(-1, -1);
}

vector<pipeInfo> findFirstStep(const vector<string> inputLines, pipeInfo startingPoint){
    vector<pipeInfo> result;
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

vector<pipeInfo> findNextStep(const vector<string>& inputLines, vector<pipeInfo> stepPipeInfos){
    vector<pipeInfo> result;
    for(pipeInfo& stepPipeInfo : stepPipeInfos){
        switch(inputLines[stepPipeInfo.getLine()][stepPipeInfo.getColl()]){
            case 'F':
                if(stepPipeInfo.getFrom() == south){ 
                    result.emplace_back(stepPipeInfo.getLine(), stepPipeInfo.getColl() + 1, west);
                } else{ 
                    result.emplace_back(stepPipeInfo.getLine() + 1, stepPipeInfo.getColl(), north);
                };
                break;
            case '7':
                if(stepPipeInfo.getFrom() == south){ 
                    result.emplace_back(stepPipeInfo.getLine(), stepPipeInfo.getColl() - 1, east);
                } else{ 
                    result.emplace_back(stepPipeInfo.getLine() + 1, stepPipeInfo.getColl(), north);
                };
                break;
            case 'J':
                if(stepPipeInfo.getFrom() == north){ 
                    result.emplace_back(stepPipeInfo.getLine(), stepPipeInfo.getColl() - 1, east);
                } else{ 
                    result.emplace_back(stepPipeInfo.getLine() - 1, stepPipeInfo.getColl(), south);
                };
                break;
            case 'L':
                if(stepPipeInfo.getFrom() == north){ 
                    result.emplace_back(stepPipeInfo.getLine(), stepPipeInfo.getColl() + 1, west);
                } else{ 
                    result.emplace_back(stepPipeInfo.getLine() - 1, stepPipeInfo.getColl(), south);
                };
                break;
            case '|':
                if(stepPipeInfo.getFrom() == south){ 
                    result.emplace_back(stepPipeInfo.getLine() - 1, stepPipeInfo.getColl(), south);
                } else{ 
                    result.emplace_back(stepPipeInfo.getLine() + 1, stepPipeInfo.getColl(), north);
                };
                break;
            case '-':
                if(stepPipeInfo.getFrom() == west ){
                    result.emplace_back(stepPipeInfo.getLine(), stepPipeInfo.getColl() + 1, west);
                } else{ 
                    result.emplace_back(stepPipeInfo.getLine(), stepPipeInfo.getColl() - 1, east);
                };
                break;
        }
    }
    return result;
}

vector<pipeInfo> findAllPipeInfos(const vector<string>& inputLines, const pipeInfo& startingPoint, vector<pipeInfo> stepPipeInfos){
    vector<pipeInfo> allSteps;
    allSteps.push_back(startingPoint);
    allSteps.push_back(stepPipeInfos[0]);
    allSteps.push_back(stepPipeInfos[1]);
    while(stepPipeInfos[0].getColl() != stepPipeInfos[1].getColl() || stepPipeInfos[0].getLine() != stepPipeInfos[1].getLine()){
        stepPipeInfos = findNextStep(inputLines, stepPipeInfos);
        allSteps.push_back(stepPipeInfos[0]);
        allSteps.push_back(stepPipeInfos[1]);
    }
    allSteps.pop_back();
    return allSteps;
}

/// @brief 
/// @param inputLines 
/// @param allLoopPipeInfos 
/// @return 
vector<string> makeCleanLoop(const vector<string>& inputLines, vector<pipeInfo>& allLoopPipeInfos){
    vector<string> cleanLoop (inputLines.size(), string(inputLines[0].size(), '.'));
    for(pipeInfo& loopPipeInfo : allLoopPipeInfos){
        int line = loopPipeInfo.getLine();
        int coll = loopPipeInfo.getColl();
        cleanLoop[line][coll] = inputLines[line][coll];
    }
    return cleanLoop;
}

/// @brief uses a set of data with only the selected loop to find the area inside the loop
/// @param cleanLoop a vector of strings that represent the set of data where the selected loop has pipe segments
/// @return the number of open area units that are contained by the loop
int findLoopArea(const vector<string>& cleanLoop){
    int area = 0;
    bool inside = false;
    char lastTransistion = ' ';
    for(int line = 0; line < cleanLoop.size(); line++){
        for(int coll = 0; coll < cleanLoop[0].size(); coll++){
            bool partOfLoop = cleanLoop[line][coll] != '.';
            if(!partOfLoop && inside) area++;
            switch (cleanLoop[line][coll]){
                case 'F':
                    if(partOfLoop) inside = !inside;
                    lastTransistion = 'F';
                    break;
                case 'L':
                    if(partOfLoop) inside = !inside;
                    lastTransistion = 'L';
                    break;
                case 'J':
                    if(partOfLoop && lastTransistion != 'F') inside = !inside;
                    lastTransistion = 'J';
                    break;
                case '7':
                    if(partOfLoop && lastTransistion != 'L') inside = !inside;
                    lastTransistion = '7';
                    break;
                case 'S':
                case '|':
                    if(partOfLoop) inside = !inside;
                    lastTransistion = '|';
                    break;
            }            
        }
    }
    return area;
}
/// @brief Main function that calls other functions to generate data sets or takes a data set to get the answer to a problem.
/// @return returns 0 if the program runs without errors.
int main(){
    int steps = 1;
    const string filePath = "input.txt";
    const vector<string> inputLines = getInputLines(filePath);
    pipeInfo startingPoint = findStartingPoint(inputLines, 'S');
    vector<pipeInfo> stepPipeInfos = findFirstStep(inputLines, startingPoint);
    vector<pipeInfo> allPipeInfos = findAllPipeInfos(inputLines, startingPoint, stepPipeInfos);
    vector<string> cleanLoop = makeCleanLoop(inputLines, allPipeInfos);
    int loopArea = findLoopArea(cleanLoop);
    cout << "Answer to problem 1: " << allPipeInfos.size()/2 << endl;
    cout << "Answer to problem 2: " << loopArea << endl;
    return 0;
}