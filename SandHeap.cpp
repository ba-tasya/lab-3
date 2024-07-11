#include "SandHeap.h"

#include <fstream>
#include <iostream>

const short kMaxGrains = 4;

SandHeap::SandHeap(uint64_t length, uint64_t width, const std::string& input_file) {
    this->length = length;
    this->width = width;
    
    cur_heap.resize(width, std::vector<uint64_t>(length, 0));
    added_to_cell.resize(width, std::vector<short>(length, 0));
    
    std::ifstream input;
    input.open(input_file);
    
    uint16_t i;
    uint16_t j;
    uint64_t cnt;
    while (input >> i >> j >> cnt) {
        cur_heap[width - i - 1][j] = cnt;
    }
}

bool SandHeap::tryNext() {
    bool expand_up = false;
    bool expand_down = false;
    bool expand_left = false;
    bool expand_right = false;
    
    for (uint64_t i = 0; i < this->width; i++) {
        if (this->cur_heap[i][0] >= kMaxGrains) {
            expand_left = true;
        }
        if (this->cur_heap[i][this->length - 1] >= kMaxGrains) {
            expand_right = true;
        }
    }

    for (uint64_t j = 0; j < this->length; j++) {
        if (cur_heap[0][j] >= kMaxGrains) {
            expand_up = true;
        }
        if (cur_heap[this->width - 1][j] >= kMaxGrains) {
            expand_down = true;
        }
    }
    
    if (expand_up) {
        cur_heap.insert(cur_heap.begin(), std::vector<uint64_t>(this->length, 0));
        added_to_cell.insert(added_to_cell.begin(), std::vector<short>(this->length, 0));
        
        this->width++;
    }
    if (expand_down) {
        cur_heap.emplace_back(this->length, 0);
        added_to_cell.emplace_back(this->length, 0);
        
        this->width++;
    }
    if (expand_left) {
        for (uint64_t i = 0; i < cur_heap.size(); i++) {
            cur_heap[i].insert(cur_heap[i].begin(), 0);
            added_to_cell[i].insert(added_to_cell[i].begin(), 0);
        }
        this->length++;
    }
    if (expand_right) {
        for (uint64_t i = 0; i < cur_heap.size(); i++) {
            cur_heap[i].emplace_back(0);
            added_to_cell[i].emplace_back(0);
        }
        this->length++;
    }
    
    bool not_stable = false;
    
    for (uint64_t i = 0; i < this->width - 1; i++) {
        for (uint64_t j = 0; j < this->length - 1; j++) {
//            std::cout << i << ' ' << j << std::endl;
            if (i + 1 < this->width) {
                added_to_cell[i + 1][j] = 0;
            }

            if (i != 0 && j != 0 && cur_heap[i][j] - added_to_cell[i][j] >= kMaxGrains) {
                cur_heap[i][j] -= kMaxGrains;

                cur_heap[i + 1][j]++;
                cur_heap[i - 1][j]++;
                cur_heap[i][j + 1]++;
                cur_heap[i][j - 1]++;
                if (cur_heap[i + 1][j] >= kMaxGrains || cur_heap[i - 1][j] >= kMaxGrains || cur_heap[i][j + 1] >= kMaxGrains || cur_heap[i][j - 1] >= kMaxGrains || cur_heap[i][j] >= kMaxGrains) {
                    not_stable = true;
                }

                added_to_cell[i + 1][j]++;
                added_to_cell[i][j + 1]++;
            }
        }
    }
    
    return not_stable;
}

uint64_t SandHeap::getColor(uint64_t i, uint64_t j) {
    return cur_heap[i][j];
}
