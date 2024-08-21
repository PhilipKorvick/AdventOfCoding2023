#include <vector>
#include <string>
#include <cstdint>

/// @brief class to hold source to destination mappings between almanac attribues 
class almanacMap{
private:
    /// @brief The start of the primary side of the almanac map
    int64_t sourceStart;
    /// @brief The end of the primary side of the almanac map
    int64_t sourceEnd;
    /// @brief The start of the secondary side of the almanac map
    int64_t destinationStart;
    /// @brief The end of the secondary side of the almanac map
    int64_t destinationEnd;
public:
    /// @brief constructor to build an almanac map from problem input ranges
    /// @param destinationStart_ integer where the second side of the map starts
    /// @param sourceStart_ integer where the primary side of the map starts
    /// @param range_ integer indicating the range of the map
    almanacMap(const int64_t& destinationStart_, const int64_t& sourceStart_, const int64_t& range_):
    sourceStart(sourceStart_),
    sourceEnd(sourceStart_ + range_),
    destinationStart(destinationStart_),
    destinationEnd(destinationStart_ + range_)
    {};
    /// @brief constructor to build an almanac map from internal data
    /// @param mapNumbers a vector of numbers that define a almanac map in the order destinationStart, destinationEnd, sourceStart, sourceEnd
    almanacMap(const std::vector<std::string>& mapNumbers):
    destinationStart(stoll(mapNumbers[0])),
    destinationEnd(destinationStart + (stoll(mapNumbers[2]))),
    sourceStart(stoll(mapNumbers[1])),
    sourceEnd(sourceStart + (stoll(mapNumbers[2])))
    {};
    /// @brief accessor to get the source start number for the almanac map
    /// @return almanac map source start
    int64_t getSourceStart(){
        return sourceStart;
    }
    /// @brief accessor to get the source end number for the almanac map
    /// @return almanac map source end
    int64_t getSourceEnd(){
        return sourceEnd;
    }
    /// @brief accessor to get the destination start number for the almanac map
    /// @return almanac map destination start 
    int64_t getDestinationStart(){
        return destinationStart;
    }
    /// @brief accessor to get the destination end number for the almanac map
    /// @return almanac map destination end
    int64_t getDestinationEnd(){
        return destinationEnd;
    }
};

/// @brief class to hold a range that will be mapped through all of the almanac maps
class almanacAspectRange{
private:
    /// @brief start of the aspect range
    int64_t start;
    /// @brief end of the aspect range
    int64_t end;
public:
    /// @brief constructor for an almanac aspect range
    /// @param aspectStart_ start of the aspect range
    /// @param aspectEnd_ end of the aspect range
    almanacAspectRange(const int64_t& aspectStart_, const int64_t& aspectEnd_):
    start(aspectStart_),
    end(aspectEnd_)
    {};
    /// @brief access to reset the start of the aspect range
    /// @param start_ new start to the aspect range
    void setStart(int64_t start_)
    {
        start = start_;
    };
    /// @brief access the start of the aspect range
    /// @return start of the aspect range
    int64_t getStart(){
        return start;
    }
    /// @brief access the end of the aspect range
    /// @return end of the aspect range
    int64_t getEnd(){
        return end;
    }
};
/// @brief calculates the mapping through the almanac of a vector of individual seeds
/// @param almanacSeeds list of individual seed numbers
/// @param almanacMapGroups almanac data containing almanac maps
/// @return returns the planting locations for the list of seeds
std::vector<int64_t> calculateSeedLocation(const std::vector<int64_t>& almanacSeeds, std::vector<std::vector<almanacMap>>& almanacMapGroups);

/// @brief finds which almanac map contains the start of a given aspect range 
/// @param aspectRange range of numbers to find which almanac map contains the start
/// @param almanacMaps set of almanac maps to search through
/// @return the index of the almanac map that contains the start of the aspect range
int findFirstAlmanacMap(almanacAspectRange& aspectRange, std::vector<almanacMap>& almanacMaps);

/// @brief finds which almanac map contains the end of a given aspect range 
/// @param aspectRange range of numbers to find which almanac map contains the end
/// @param almanacMaps set of almanac maps to search through
/// @return the index of the almanac map that contains the end of the aspect range
int findLastAlmanacMap(almanacAspectRange& aspectRange, std::vector<almanacMap>& almanacMaps);

/// @brief maps the current set of ranges through the almanac map group that is input
/// @param aspectRanges ranges of numbers to be mapped through the given map group
/// @param almanacMaps mapping data to transfer one aspect to the next
/// @return new vector of aspect ranges after being mapped. could be a larger set if the map divided one or more of the aspect ranges
std::vector<almanacAspectRange> calculateRanges(std::vector<almanacAspectRange>& aspectRanges, std::vector<almanacMap>& almanacMaps);

/// @brief calculates the location of the seeds in the seed ranges for an almanac
/// @param almanacSeedRanges a list of seed ranges to be mapped through the almanac
/// @param almanacMapGroups data of the almanac mappings
/// @return the resultant ranges of locations of where to plant the seeds
std::vector<int64_t> calculateAllSeedLocations(const std::vector<almanacAspectRange>& almanacSeedRanges, std::vector<std::vector<almanacMap>>& almanacMapGroups);

/// @brief takes the input lines of the problem and converts them into vector of almanac mappings
/// @param sectionLines vector of strings that represent all of the almanac maps
/// @return the vector of almanac maps
std::vector<almanacMap> parseAlmanacMap(const std::vector<std::string>& sectionLines);

/// @brief reads the list of seeds and returns the vector of integers of the seeds
/// @param sectionLine string that contains seed numbers
/// @return vectors of seed numbers
std::vector<int64_t> parseAlmanacSeeds(const std::string& sectionLine);

/// @brief takes all of the seed range data from a string and converts it into usable aspect ranges
/// @param almanacLine string that contains all of the seed ranges
/// @return a vector of seed ranges
std::vector<almanacAspectRange> parseAlmanacSeedRanges(const std::string& almanacLine);

/// @brief Converts the input text data to sets of almanac map
/// @param almanacLines vector of strings that contain the input to the problem
/// @return vectors of vectors of almanac maps
std::vector<std::vector<almanacMap>> parseAlmanac(const std::vector<std::string>& almanacLines);

/// @brief This program solves the fifth problem of the Advent of Code 2023
/// @param filePath path to input file for the problem
void problem05 (const std::string& filePath);
