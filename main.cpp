#include "./CommandsParser.h"
#include "SandHeap.h"
#include "ToBmp.h"

#include <limits>
#include <iostream>

const uint64_t kMaxUint = std::numeric_limits<uint64_t>::max();

int main(int argc, char* argv[]) {
    CommandsParser parser(argc, argv);
    
    uint64_t length = parser.getLength();
    uint64_t width = parser.getWidth();

    std::cout << length << ' ' << width << std::endl;
    
    std::string input_file = parser.getInput();
    std::string output_file = parser.getOutput();
    if (output_file[output_file.size() - 1] != '/') {
        output_file += '/';
    }
    
    uint64_t max_iter = parser.getMaxIter();
    max_iter = (max_iter == 0 ? kMaxUint : max_iter);
//    std::cout << max_iter << std::endl;
    uint64_t freq = parser.getFreq();
    
    SandHeap heap(length, width, input_file);
    
    uint64_t since_last_save = 0;
    uint64_t picture_number = 0;
    bool has_next;
    std::string to_bmp_path;
    
    while (max_iter > 0) {
        since_last_save++;
        has_next = heap.tryNext();
        if (has_next) {
            if (since_last_save == freq) {
                since_last_save = 0;
                
                Picture picture(heap.length, heap.width);
                
                for (uint64_t i = 0; i < heap.width; i++) {
                    for (uint64_t j = 0; j < heap.length; j++) {
                        picture.setColor(i, j, heap.getColor(i, j));
                    }
                }
                
                to_bmp_path = output_file + std::to_string(picture_number) + ".bmp";
                picture_number++;
                picture.makeBmp(to_bmp_path);
            }
        } else {
            break;
        }
        
        max_iter--;
    }
}
