#include <cinttypes>
#include <iostream>
#include <vector>

const uint32_t kBitmapFileHeader = 14; // 14 bytes
const uint32_t kBitmapV5Header = 40; // the 3 version, 40 bytes
const uint32_t kByte = 8;
const uint32_t kColorChannels = 3;
const uint32_t kMaxPadding = 4;
const uint32_t kCast32To8 = 4;

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b){}
    Color() : r(255), g(255), b(255){}
};

const uint8_t kCntColors = 5;
const Color kAllColors[kCntColors] = {
        {255, 255, 255}, // white
        {0, 255, 0}, // green
        {255, 0, 255}, // magenta
        {255, 255, 0}, // yellow
        {0, 0, 0} // black
};

struct Picture {
    uint64_t length;
    uint64_t width;
    std::vector<Color> colors;
    
    Picture(uint16_t width, uint16_t height);
    void setColor(uint64_t i, uint64_t j, uint64_t color);
    void makeBmp(std::string& path);
};
