#include <iostream>
#include <vector>

struct SandHeap {
    uint64_t length;
    uint64_t width;
    
    std::vector<std::vector<uint64_t>> cur_heap;
    std::vector<std::vector<short>> added_to_cell;
    
    SandHeap(uint64_t length, uint64_t width, const std::string& input_file);
    
    bool tryNext();
    uint64_t getColor(uint64_t i, uint64_t j);
};
