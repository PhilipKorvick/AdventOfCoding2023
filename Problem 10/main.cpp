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

vector<pipeInfo> findNextStep(const vector<string>& inputLines, vector<pipeInfo> steppipeInfos){
    vector<pipeInfo> result;
    for(pipeInfo& steppipeInfo : steppipeInfos){
        switch(inputLines[steppipeInfo.getLine()][steppipeInfo.getColl()]){
            case 'F':
                if(steppipeInfo.getfrom() == south){ 
                    result.emplace_back(steppipeInfo.getLine(), steppipeInfo.getColl() + 1, west);
                } else{ 
                    result.emplace_back(steppipeInfo.getLine() + 1, steppipeInfo.getColl(), north);
                };
                break;
            case '7':
                if(steppipeInfo.getfrom() == south){ 
                    result.emplace_back(steppipeInfo.getLine(), steppipeInfo.getColl() - 1, east);
                } else{ 
                    result.emplace_back(steppipeInfo.getLine() + 1, steppipeInfo.getColl(), north);
                };
                break;
            case 'J':
                if(steppipeInfo.getfrom() == north){ 
                    result.emplace_back(steppipeInfo.getLine(), steppipeInfo.getColl() - 1, east);
                } else{ 
                    result.emplace_back(steppipeInfo.getLine() - 1, steppipeInfo.getColl(), south);
                };
                break;
            case 'L':
                if(steppipeInfo.getfrom() == north){ 
                    result.emplace_back(steppipeInfo.getLine(), steppipeInfo.getColl() + 1, west);
                } else{ 
                    result.emplace_back(steppipeInfo.getLine() - 1, steppipeInfo.getColl(), south);
                };
                break;
            case '|':
                if(steppipeInfo.getfrom() == south){ 
                    result.emplace_back(steppipeInfo.getLine() - 1, steppipeInfo.getColl(), south);
                } else{ 
                    result.emplace_back(steppipeInfo.getLine() + 1, steppipeInfo.getColl(), north);
                };
                break;
            case '-':
                if(steppipeInfo.getfrom() == west ){
                    result.emplace_back(steppipeInfo.getLine(), steppipeInfo.getColl() + 1, west);
                } else{ 
                    result.emplace_back(steppipeInfo.getLine(), steppipeInfo.getColl() - 1, east);
                };
                break;
        }
    }
    return result;
}

vector<pipeInfo> findAllPipeInfos(const vector<string>& inputLines, const pipeInfo& startingPoint, vector<pipeInfo> steppipeInfos){
    vector<pipeInfo> allSteps;
    allSteps.push_back(startingPoint);
    allSteps.push_back(steppipeInfos[0]);
    allSteps.push_back(steppipeInfos[1]);
    while(steppipeInfos[0].getColl() != steppipeInfos[1].getColl() || steppipeInfos[0].getLine() != steppipeInfos[1].getLine()){
        steppipeInfos = findNextStep(inputLines, steppipeInfos);
        allSteps.push_back(steppipeInfos[0]);
        allSteps.push_back(steppipeInfos[1]);
    }
    allSteps.pop_back();
    return allSteps;
}

vector<string> makeCleanLoop(const vector<string>& inputLines, vector<pipeInfo>& allLooppipeInfos){
    vector<string> cleanLoop (inputLines.size(), string(inputLines[0].size(), '.'));
    for(pipeInfo& looppipeInfo : allLooppipeInfos){
        int line = looppipeInfo.getLine();
        int coll = looppipeInfo.getColl();
        cleanLoop[line][coll] = inputLines[line][coll];
    }
    return cleanLoop;
}

int findLoopArea(const vector<string>& cleanLoop){
    int area = 0;
    bool inside = false;
    char lastTransisition = ' ';
    for(int line = 0; line < cleanLoop.size(); line++){
        for(int coll = 0; coll < cleanLoop[0].size(); coll++){
            bool partOfLoop = cleanLoop[line][coll] != '.';
            if(!partOfLoop && inside) area++;
            switch (cleanLoop[line][coll]){
                case 'F':
                    if(partOfLoop) inside = !inside;
                    lastTransisition = 'F';
                    break;
                case 'L':
                    if(partOfLoop) inside = !inside;
                    lastTransisition = 'L';
                    break;
                case 'J':
                    if(partOfLoop && lastTransisition != 'F') inside = !inside;
                    lastTransisition = 'J';
                    break;
                case '7':
                    if(partOfLoop && lastTransisition != 'L') inside = !inside;
                    lastTransisition = '7';
                    break;
                case 'S':
                case '|':
                    if(partOfLoop) inside = !inside;
                    lastTransisition = '|';
                    break;
            }            
        }
    }
    return area;
}

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