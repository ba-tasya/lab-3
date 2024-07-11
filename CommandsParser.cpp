#include "CommandsParser.h"

#include <iostream>

std::unordered_map<std::string, char> to_small_command = {{"length", 'l'}, {"width", 'w'}, {"input", 'i'}, {"output", 'o'}, {"max-iter", 'm'}, {"freq", 'f'}};

CommandsParser::CommandsParser(int argc, char* argv[]) {
    for (uint64_t i = 1; i < argc; i += 2) {
        std::string command(argv[i]);
        std::string value = "";
        if (i + 1 < argc) {
            value = static_cast<std::string>(argv[i + 1]);
        }

//        std::cout << command << ' ' << value << '\n';
        
        if (command.size() != 0 && command[0] != '-') {
            continue;
        }
        
        if (command.size() > 1 && command[1] == '-') {
            if (command.size() > 2) {
                std::string act_command = command.substr(2, command.size() - 2);
                auto is_found = to_small_command.find(act_command); 
                if (is_found != to_small_command.end()) {
                    commands[is_found->second] = value;
                }
            }
        } else if (command.size() == 2) {
            char act_command = command[1];
            if (act_command == 'l' || act_command == 'w' || act_command == 'i' || act_command == 'o' || act_command == 'm' || act_command == 'f') {
                commands[act_command] = value;
            }
        }
    }
}

unsigned long long CommandsParser::getLength() {
    return std::stoull((commands['l'] == "" ? "0" : commands['l']), nullptr, 10);
}

unsigned long long CommandsParser::getWidth() {
    return std::stoull((commands['w'] == "" ? "0" : commands['w']), nullptr, 10);
}

std::string CommandsParser::getInput() {
    return commands['i'];
}

std::string CommandsParser::getOutput() {
    return commands['o'];
}

unsigned long long CommandsParser::getMaxIter() {
    return std::stoull((commands['m'] == "" ? "0" : commands['m']), nullptr, 10);
}

unsigned long long CommandsParser::getFreq() {
    return std::stoull((commands['f'] == "" ? "0" : commands['f']), nullptr, 10);
}
