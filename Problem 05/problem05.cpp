#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ranges>
#include <cstdint>
#include "../Common/common.h"
#include "problem05.h"

std::vector<int64_t> calculateSeedLocation(const std::vector<int64_t>& almanacSeeds, std::vector<std::vector<almanacMap>>& almanacMapGroups){
    std::vector<int64_t> seedLocations;
    int64_t intermediateValue;
    for (const int64_t& almanacSeed : almanacSeeds){
        intermediateValue = almanacSeed;
        for (std::vector<almanacMap>& almanacMaps : almanacMapGroups){
            for (almanacMap& almanacMapData : almanacMaps){
                if(intermediateValue >= almanacMapData.getSourceStart() && intermediateValue <= almanacMapData.getSourceEnd()){
                     intermediateValue = almanacMapData.getDestinationStart() + (intermediateValue - almanacMapData.getSourceStart());
                     break;
                }
            }
        }
        seedLocations.push_back(intermediateValue);
    }
    return seedLocations;
}

int findFirstAlmanacMap(almanacAspectRange& aspectRange, std::vector<almanacMap>& almanacMaps){
    for(size_t mapData = 0; mapData < almanacMaps.size(); mapData++){
        if(almanacMaps[mapData].getSourceStart() < aspectRange.getStart()){
            return mapData;
        }
    }
    return 0;
}
int findLastAlmanacMap(almanacAspectRange& aspectRange, std::vector<almanacMap>& almanacMaps){
    for(size_t mapData = 0; mapData < almanacMaps.size(); mapData++){
        if(almanacMaps[mapData].getSourceEnd() > aspectRange.getEnd()){
            return mapData;
        }
    }
    return 0;
}

std::vector<almanacAspectRange> calculateRanges(std::vector<almanacAspectRange>& aspectRanges, std::vector<almanacMap>& almanacMaps){
    std::vector<almanacAspectRange> resultRanges;
    for(almanacAspectRange& aspectRange : aspectRanges){
        int firstMap = findFirstAlmanacMap(aspectRange, almanacMaps);
        int lastMap = findLastAlmanacMap(aspectRange, almanacMaps);
        for (int mapData = firstMap; mapData == 0 || mapData > lastMap; mapData--){
            if(aspectRange.getEnd() < almanacMaps[mapData].getSourceStart()) break;
            if(aspectRange.getStart() < almanacMaps[mapData].getSourceEnd()){
                //source range contained within destination range
                if(aspectRange.getEnd() <= almanacMaps[mapData].getSourceEnd()){
                    resultRanges.emplace_back(almanacMaps[mapData].getDestinationStart() + aspectRange.getStart() - almanacMaps[mapData].getSourceStart(), almanacMaps[mapData].getDestinationStart() + aspectRange.getEnd() - almanacMaps[mapData].getSourceStart());
                }
                // source range both inside and outside of destination range but stops before next map
                else if(mapData == 0 || aspectRange.getEnd() < almanacMaps[mapData -1].getSourceStart()){
                    resultRanges.emplace_back(almanacMaps[mapData].getDestinationStart() + aspectRange.getStart() - almanacMaps[mapData].getSourceStart(), almanacMaps[mapData].getDestinationEnd());
                    resultRanges.emplace_back(almanacMaps[mapData].getSourceEnd() +1, aspectRange.getEnd());
                }
                // source range both inside and outside of destination rang and continued to next map
                else {
                    resultRanges.emplace_back(almanacMaps[mapData].getDestinationStart() + aspectRange.getStart() - almanacMaps[mapData].getSourceStart(), almanacMaps[mapData].getDestinationEnd());
                    resultRanges.emplace_back(almanacMaps[mapData].getSourceEnd() +1, almanacMaps[mapData-1].getSourceStart() -1);
                    aspectRange.setStart(almanacMaps[mapData - 1].getSourceStart());
                }
            } else {
                if(mapData == 0 || aspectRange.getEnd() < almanacMaps[mapData -1].getSourceStart()){
                    resultRanges.emplace_back(aspectRange.getStart(), aspectRange.getEnd());
                } else{
                    resultRanges.emplace_back(aspectRange.getStart(), almanacMaps[mapData -1].getSourceStart() -1);
                    aspectRange.setStart(almanacMaps[mapData - 1].getSourceStart());
                }
            }
        }
    }
    return resultRanges;
}

std::vector<int64_t> calculateAllSeedLocations(const std::vector<almanacAspectRange>& almanacSeedRanges, std::vector<std::vector<almanacMap>>& almanacMapGroups){
    std::vector<int64_t> minSeedLocations;
    for (const almanacAspectRange& seedRange : almanacSeedRanges){
        std::vector<almanacAspectRange> aspectRanges;
        aspectRanges.emplace_back(seedRange);
        for(std::vector<almanacMap>& almanacMaps : almanacMapGroups){
            aspectRanges = calculateRanges(aspectRanges, almanacMaps);
        }
        sort(aspectRanges.begin(), aspectRanges.end(), [](almanacAspectRange& a, almanacAspectRange& b){return a.getStart() < b.getStart();});
        minSeedLocations.emplace_back(aspectRanges[0].getStart());
    }
    return minSeedLocations;
}

std::vector<almanacMap> parseAlmanacMap(const std::vector<std::string>& sectionLines){
    std::vector<almanacMap> almanacMaps;
    for(const std::string& sectionLine : sectionLines){
        if(isdigit(sectionLine[0])){
            std::vector<std::string> mapNumbers = split(sectionLine, ' ');
            almanacMaps.emplace_back(mapNumbers);
        }
    }
    sort(almanacMaps.begin(), almanacMaps.end(), [](almanacMap& a, almanacMap& b){return a.getSourceStart() > b.getSourceStart();});
    return almanacMaps;
}

std::vector<int64_t> parseAlmanacSeeds(const std::string& sectionLine){
    std::vector<int64_t> almanacSeeds;
    std::vector<std::string> seedStrings = split(sectionLine, ' ');
    seedStrings.erase(seedStrings.begin());
    for(const std::string& seedString : seedStrings){
        almanacSeeds.emplace_back(stoll(seedString));
    }
    return almanacSeeds;
}

std::vector<almanacAspectRange> parseAlmanacSeedRanges(const std::string& almanacLine){
    std::vector<almanacAspectRange> almanacSeedRanges;
    std::vector<std::string> seedStrings = split(almanacLine, ' ');
    seedStrings.erase(seedStrings.begin());
    for(int seedData = 0; seedData < 20; seedData+=2){
        int64_t seedRangeStart = stoll(seedStrings[seedData]);
        int64_t seedRangeEnd = seedRangeStart + stoll(seedStrings[seedData+1]);
        almanacSeedRanges.emplace_back(seedRangeStart, seedRangeEnd);
    }
    return almanacSeedRanges;
}

std::vector<std::vector<almanacMap>> parseAlmanac(const std::vector<std::string>& almanacLines){
    std::vector<std::vector<almanacMap>> almanac;
    std::vector<std::string> sectionLines;
    for(const std::string& almanacLine: almanacLines){
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

void problem05 (const std::string& filePath){
    const std::vector<std::string> almanacLines = getInputLines(filePath);
    const std::vector<int64_t> almanacSeeds = parseAlmanacSeeds(almanacLines[0]);
    const std::vector<almanacAspectRange> almanacSeedRanges = parseAlmanacSeedRanges(almanacLines[0]);
    std::vector<std::vector<almanacMap>> almanacMapGroups = parseAlmanac(almanacLines);
    const std::vector<int64_t> seedLocation = calculateSeedLocation(almanacSeeds, almanacMapGroups);
    const std::vector<int64_t> minSeedLocations = calculateAllSeedLocations(almanacSeedRanges, almanacMapGroups);
    std::cout << "Solution problem 5.1: " << *min_element(seedLocation.begin(), seedLocation.end()) << std::endl;
    std::cout << "Solution problem 5.2: " << *min_element(minSeedLocations.begin(), minSeedLocations.end()) << std::endl;
}