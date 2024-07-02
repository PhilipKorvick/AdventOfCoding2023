#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <stdint.h>
using namespace std;

struct almanacMap{
    almanacMap(const int64_t& destinationStart_, const int64_t& sourceStart_, const int64_t& range_):
    sourceStart(sourceStart_),
    sourceEnd(sourceStart_ + range_),
    destinationStart(destinationStart_),
    destinationEnd(destinationStart_ + range_)
    {};
    almanacMap(const vector<string>& mapNumbers):
    destinationStart(stoll(mapNumbers[0])),
    destinationEnd(destinationStart + (stoll(mapNumbers[2]))),
    sourceStart(stoll(mapNumbers[1])),
    sourceEnd(sourceStart + (stoll(mapNumbers[2])))
    {};
    int64_t sourceStart;
    int64_t sourceEnd;
    int64_t destinationStart;
    int64_t destinationEnd;
};

struct almanacAspectRange{
    almanacAspectRange(const int64_t& aspectStart_, const int64_t& aspectEnd_):
    start(aspectStart_),
    end(aspectEnd_)
    {};
    int64_t start;
    int64_t end;
    void set_start(int64_t start_){
        start = start_;
    };
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

vector<int64_t> calculateSeedLocation(const vector<int64_t>& almanacSeeds, const vector<vector<almanacMap>>& almanacMapGroups){
    vector<int64_t> seedLocations;
    int64_t intermediatValue;
    for (const int64_t& almanacSeed : almanacSeeds){
        intermediatValue = almanacSeed;
        for (const vector<almanacMap>& almanacMaps : almanacMapGroups){
            for (const almanacMap& almanacMapData : almanacMaps){
                if(intermediatValue >= almanacMapData.sourceStart && intermediatValue <= almanacMapData.sourceEnd){
                     intermediatValue = almanacMapData.destinationStart + (intermediatValue - almanacMapData.sourceStart);
                     break;
                }
            }
        }
        seedLocations.push_back(intermediatValue);
    }
    return seedLocations;
}

int findFirstAlmanacMap(almanacAspectRange& aspectRange, const vector<almanacMap>& almanacMaps){
    for(size_t mapData = 0; mapData < almanacMaps.size(); mapData++){
        if(almanacMaps[mapData].sourceStart < aspectRange.start){
            return mapData;
        }
    }
    return 0;
}
int findLastAlmanacMap(almanacAspectRange& aspectRange, const vector<almanacMap>& almanacMaps){
    for(size_t mapData = 0; mapData < almanacMaps.size(); mapData++){
        if(almanacMaps[mapData].sourceEnd > aspectRange.end){
            return mapData;
        }
    }
    return 0;
}

vector<almanacAspectRange> calculateRanges(vector<almanacAspectRange>& aspectRanges, const vector<almanacMap>& almanacMaps){
    vector<almanacAspectRange> resultRanges;
    for(almanacAspectRange& aspectRange : aspectRanges){
        int firstMap = findFirstAlmanacMap(aspectRange, almanacMaps);
        int lastMap = findLastAlmanacMap(aspectRange, almanacMaps);
        for (int mapData = firstMap; mapData == 0 || mapData > lastMap; mapData--){
            if(aspectRange.end < almanacMaps[mapData].sourceStart) break;
            if(aspectRange.start < almanacMaps[mapData].sourceEnd){
                //source range contained within destination range
                if(aspectRange.end <= almanacMaps[mapData].sourceEnd){
                    resultRanges.emplace_back(almanacMaps[mapData].destinationStart + aspectRange.start - almanacMaps[mapData].sourceStart, almanacMaps[mapData].destinationStart + aspectRange.end - almanacMaps[mapData].sourceStart);
                }
                // source range both inside and outside of destination range but stops before next map
                else if(mapData == 0 || aspectRange.end < almanacMaps[mapData -1].sourceStart){
                    resultRanges.emplace_back(almanacMaps[mapData].destinationStart + aspectRange.start - almanacMaps[mapData].sourceStart, almanacMaps[mapData].destinationEnd);
                    resultRanges.emplace_back(almanacMaps[mapData].sourceEnd +1, aspectRange.end);
                }
                // source range both inside and outsid of destination rang and continued to next map
                else {
                    resultRanges.emplace_back(almanacMaps[mapData].destinationStart + aspectRange.start - almanacMaps[mapData].sourceStart, almanacMaps[mapData].destinationEnd);
                    resultRanges.emplace_back(almanacMaps[mapData].sourceEnd +1, almanacMaps[mapData-1].sourceStart -1);
                    aspectRange.set_start(almanacMaps[mapData - 1].sourceStart);
                }
            } else {
                if(mapData == 0 || aspectRange.end < almanacMaps[mapData -1].sourceStart){
                    resultRanges.emplace_back(aspectRange.start, aspectRange.end);
                } else{
                    resultRanges.emplace_back(aspectRange.start, almanacMaps[mapData -1].sourceStart -1);
                    aspectRange.set_start(almanacMaps[mapData - 1].sourceStart);
                }
            }
        }
    }
    return resultRanges;
}

vector<int64_t> calculateAllSeedLocations(const vector<almanacAspectRange>& almanacSeedRanges, const vector<vector<almanacMap>>& almanacMapGroups){
    vector<int64_t> minSeedLocations;
    for (const almanacAspectRange& seedRange : almanacSeedRanges){
        vector<almanacAspectRange> aspectRanges;
        aspectRanges.emplace_back(seedRange);
        for(const vector<almanacMap>& almanacMaps : almanacMapGroups){
            aspectRanges = calculateRanges(aspectRanges, almanacMaps);
        }
        sort(aspectRanges.begin(), aspectRanges.end(), [](almanacAspectRange& a, almanacAspectRange& b){return a.start < b.start;});
        minSeedLocations.emplace_back(aspectRanges[0].start);
    }
    return minSeedLocations;
}

vector<almanacMap> parseAlmanacMap(const vector<string>& sectionLines){
    vector<almanacMap> almanacMaps;
    for(const string& sectionLine : sectionLines){
        if(isdigit(sectionLine[0])){
            vector<string> mapNumbers = split(sectionLine, ' ');
            almanacMaps.emplace_back(mapNumbers);
        }
    }
    sort(almanacMaps.begin(), almanacMaps.end(), [](almanacMap& a, almanacMap& b){return a.sourceStart > b.sourceStart;});
    for(const almanacMap& mapData : almanacMaps){
    }
    return almanacMaps;
}

vector<int64_t> parseAlmanacSeeds(const string& sectionLine){
    vector<int64_t> almanacSeeds;
    vector<string> seedStrings = split(sectionLine, ' ');
    seedStrings.erase(seedStrings.begin());
    for(const string& seedString : seedStrings){
        almanacSeeds.emplace_back(stoll(seedString));
    }
    return almanacSeeds;
}

vector<almanacAspectRange> parseAlmanacSeedRanges(const string& almanacLine){
    vector<almanacAspectRange> almanacSeedRanges;
    vector<string> seedStrings = split(almanacLine, ' ');
    seedStrings.erase(seedStrings.begin());
    for(int seedData = 0; seedData < 20; seedData+=2){
        int64_t seedRangeStart = stoll(seedStrings[seedData]);
        int64_t seedRangeEnd = seedRangeStart + stoll(seedStrings[seedData+1]);
        almanacSeedRanges.emplace_back(seedRangeStart, seedRangeEnd);
    }
    return almanacSeedRanges;
}

vector<vector<almanacMap>> parseAlmanac(const vector<string>& almanacLines){
    vector<vector<almanacMap>> almanac;
    vector<string> sectionLines;
    for(const string& almanacLine: almanacLines){
        if(almanacLine.compare("") != 0){
            sectionLines.emplace_back(almanacLine);
        }
        else if(sectionLines.size() > 1){
            almanac.emplace_back(parseAlmanacMap(sectionLines));
            sectionLines.clear();
        } else{
            sectionLines.clear();
        }
    }
    almanac.emplace_back(parseAlmanacMap(sectionLines));
    return almanac;
}

int main(){
    const string filePath = "input.txt";
    const vector<string> almanacLines = getInputLines(filePath);
    const vector<int64_t> almanacSeeds = parseAlmanacSeeds(almanacLines[0]);
    const vector<almanacAspectRange> almanacSeedRanges = parseAlmanacSeedRanges(almanacLines[0]);
    const vector<vector<almanacMap>> almanacMapGroups = parseAlmanac(almanacLines);
    const vector<int64_t> seedLocation = calculateSeedLocation(almanacSeeds, almanacMapGroups);
    const vector<int64_t> minSeedLocations = calculateAllSeedLocations(almanacSeedRanges, almanacMapGroups);
    cout << "Problem 1: " << *min_element(seedLocation.begin(), seedLocation.end()) << endl;
    cout << "Problem 2: " << *min_element(minSeedLocations.begin(), minSeedLocations.end()) << endl;
    return 1;
}