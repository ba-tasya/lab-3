#include <iostream>
#include <unordered_map>

struct CommandsParser {
    std::unordered_map<char, std::string> commands;
    
    CommandsParser(int argc, char* argv[]);
    uint64_t getLength();
    uint64_t getWidth();
    std::string getInput();
    std::string getOutput();
    uint64_t getMaxIter();
    uint64_t getFreq();
};
