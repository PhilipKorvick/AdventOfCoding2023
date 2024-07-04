#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

enum handType {
    nullHand,
    highCard,
    onePair,
    twoPair,
    threeOfKind,
    fullHouse,
    fourOfKind,
    fiveOfKind
};
map<char, char> cardMapAlpha {{'2', 'a'},{'3','b'},{'4','c'},{'5','d'},{'6','e'},{'7','f'},{'8','g'},{'9','h'},{'T','i'},{'J','j'},{'Q','k'},{'K','l'},{'A','m'}};
map<char, char> cardMapJoker {{'2', 'b'},{'3','c'},{'4','d'},{'5','e'},{'6','f'},{'7','g'},{'8','h'},{'9','i'},{'T','j'},{'J','a'},{'Q','k'},{'K','l'},{'A','m'}};

string parseHandData(const string& handString){
    string result;
        for(const char& card : handString){
            result += cardMapAlpha[card];
        }
    return result;
}

string parseJokerHandData(const string& handString){
    string result;
        for(const char& card : handString){
            result += cardMapJoker[card];
        }
    return result;
}

vector<string> split (const string &str, const char& delim) {
    vector<string> result;
    stringstream ss (str);
    string item;
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}

handType parseJokerType(const string& handData){
    vector<string> handGroups;
    for(char card : handData){
        if(handGroups.size() == 0){
            handGroups.emplace_back(1, card);
            continue;
        }
        bool newCard = true;
        for(string& handGroup: handGroups){
            if(handGroup[0] == card){
                handGroup += card;
                newCard = false;
                break;
            }
        }
        if(newCard)handGroups.emplace_back(1, card);
    }
    if(handGroups[0].size() == 5) return fiveOfKind;
    sort(handGroups.begin(), handGroups.end(), [](const string & a, const string & b){ 
        if(a.size() > b.size())return true; 
        if(a.size() == b.size())return a[0] > b[0]; 
        return false; 
    });
    int jokerSet = 0;
    for(const string& handGroup: handGroups){
        if(handGroup[0] == 'a'){
            break;
        }
        jokerSet++;
    }
    if(jokerSet < handGroups.size()){
        if(handGroups[0][0] != 'a'){
            handGroups[0] += handGroups[jokerSet];
        } else {
            handGroups[1] += handGroups[jokerSet];
        }
        handGroups.erase(handGroups.begin() + jokerSet);
    }
    if(handGroups[0].size() == 5) return fiveOfKind;
    if (handGroups[0].size() == 4) return fourOfKind;
    if (handGroups[0].size() == 3){
        if(handGroups[1].size() == 2)return fullHouse;
        return threeOfKind;
    }
    if (handGroups[0].size() == 2){
        if(handGroups[1].size() == 2)return twoPair;
        return onePair;
    }
    return highCard;
}

handType parseType(const string& handData){
    vector<string> handGroups;
    for(int card : handData){
        if(handGroups.size() == 0){
            handGroups.emplace_back(1, card);
            continue;
        }
        bool newCard = true;
        for(string& handGroup: handGroups){
            if(handGroup[0] == card){
                handGroup += card;
                newCard = false;
                break;
            }
        }
        if(newCard)handGroups.emplace_back(1, card);
    }
    if(handGroups[0].size() == 5) return fiveOfKind;
    sort(handGroups.begin(), handGroups.end(), [](const string& a, const string& b){ return a.size() > b.size(); });
    
    if (handGroups[0].size() == 4) return fourOfKind;
    if (handGroups[0].size() == 3){
        if(handGroups[1].size() == 2)return fullHouse;
        return threeOfKind;
    }
    if (handGroups[0].size() == 2){
        if(handGroups[1].size() == 2)return twoPair;
        return onePair;
    }
    return highCard;
}

class hand {
    int bet = 0;
    string handData;
    string jokerHandData;
    handType type;
    handType jokerType;
public:
    hand(const string& handLine){
        vector<string> handParts = split(handLine, ' ');
        bet = stoi(handParts[1]);
        handData = parseHandData(handParts[0]);
        jokerHandData = parseJokerHandData(handParts[0]);
        type = parseType(handData);
        jokerType = parseJokerType(jokerHandData);
    }
    int getBet(){return bet;};
    string getHand(){return handData;};
    string getJokerHand(){return jokerHandData;};
    int getType(){return type;};
    int getJokerType(){return jokerType;};
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

int main (){
    const string filePath = "input.txt";
    const vector<string> handsLines = getInputLines(filePath);
    vector<hand> hands;
    for(const string& handLine : handsLines){
        hands.emplace_back(handLine);
    }
    sort(hands.begin(), hands.end(), [](hand& a, hand& b){
        if(a.getType() < b.getType())return true;
        if(a.getType() == b.getType()) return a.getHand().compare(b.getHand()) < 1;
        return false;
    });
    long long problem1Answer = 0;
    int handMultiplier = 1;
    for(hand& handInfo : hands){
        problem1Answer += handInfo.getBet() * handMultiplier;
        handMultiplier++;
    }
    sort(hands.begin(), hands.end(), [](hand& a, hand& b){
        if(a.getJokerType() < b.getJokerType())return true;
        if(a.getJokerType() == b.getJokerType()) return a.getJokerHand().compare(b.getJokerHand()) < 1;
        return false;
    });
    long long problem2Answer = 0;
    handMultiplier = 1;
    for(hand& handInfo : hands){
        problem2Answer += handInfo.getBet() * handMultiplier;
        handMultiplier++;
    }
    cout << "Answer to problem 1: " << problem1Answer << endl;
    cout << "Answer to problem 2: " << problem2Answer << endl;
    return 1;
}