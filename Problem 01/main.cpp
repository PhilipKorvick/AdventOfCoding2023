#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

// setting up map between spelling of numbers and their numaric representation
map<string, string> numbers = {{"one","1"},{"two","2"},{"three","3"},{"four","4"},{"five","5"},{"six","6"},{"seven","7"},{"eight","8"},{"nine", "9"}};

// converts a spelled out number into the respective numaric digit
void convertNumber(string& line){
    // look for each of the numbers' spellings
    for(auto number : numbers){
        bool foundString = false;
        // check for multiple of the same spelled number
        do{
            foundString = false;
            size_t linePosition = line.find(number.first);
            // if a spelled number is found do loop again and put the numaric value in the second letter of the number so that it does not disturbe overlapping letters from other number spellings
            if(linePosition!=string::npos){
                foundString = true;
                line.replace(linePosition+1, 1, number.second);
            }

        }while (foundString);
    }
}

// finds the first and last number in a string and returns them as an int in the respective order
int findNumber(string& line){
    char firstNumber = 0;
    char lastNumber = 0;

    // iterate through entire string to find a number
    for(string::iterator it = line.begin(); it != line.end(); it++){
        // capture the first number found
        if(isdigit(*it) && firstNumber == 0){
            firstNumber = *it;
        }
        // capture any number found with it being replaced with later numbers
        if(isdigit(*it)){
            lastNumber = *it;
        }
    }
    return stoi(string{firstNumber, lastNumber});
}

int main(){
    int checkSum = 0;
    string line;
    // Get the input data
    const string filePath = "input.txt";
    ifstream inputData(filePath);
    if(!inputData.is_open()){
        cout<< "did not open the file" << endl;
    }
    // Read each line of the input data
    while(getline(inputData, line)){
        // converts a spelled out number into the respective numaric digit
        convertNumber(line);
        // find the numbers in the data and add them to the running total
        checkSum += findNumber(line);
    }
    // display final total
    cout << checkSum << endl;
    inputData.close();
    return 0;
}