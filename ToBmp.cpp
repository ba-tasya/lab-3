#include "ToBmp.h"

#include <fstream>
#include <iostream>

Picture::Picture(uint16_t length, uint16_t width) {
    this->length = length;
    this->width = width;
    this->colors.resize(length * width);
}

void Picture::setColor(uint64_t i, uint64_t j, uint64_t color) {
    if (color >= kCntColors) {
        color = kCntColors - 1;
    }
    colors[i + j * length] = kAllColors[color];
}

void Picture::makeBmp(std::string& path) {
    std::ofstream output(path, std::ios::binary);
    
    uint64_t file_size = kBitmapFileHeader + kBitmapV5Header + kColorChannels * length * width;
    uint64_t extra_to_str = (kMaxPadding + (length * kColorChannels) - 1) % kMaxPadding;

    uint8_t bitmap_file_header[kBitmapFileHeader];
    for (uint32_t i = 0; i < kBitmapFileHeader; i++) {
        bitmap_file_header[i] = 0;
    }
    bitmap_file_header[0] = static_cast<uint8_t>('B');
    bitmap_file_header[1] = static_cast<uint8_t>('M');
    bitmap_file_header[10] = kBitmapFileHeader + kBitmapV5Header;

    uint8_t bitmap_info_header[kBitmapV5Header];
    for (uint32_t i = 0; i < kBitmapV5Header; i++) {
        bitmap_info_header[i] = 0;
    }
    bitmap_info_header[0] = kBitmapV5Header;
    bitmap_info_header[12] = 1;
    bitmap_info_header[14] = 24;
    
    for (int i = 0; i < kCast32To8; i++) {
        bitmap_file_header[2 + i] = file_size >> kByte * i;
        bitmap_info_header[4 + i] = length >> kByte * i;
        bitmap_info_header[8 + i] = width >> kByte * i;
    }

    output.write(reinterpret_cast<const char*>(bitmap_file_header), kBitmapFileHeader);
    output.write(reinterpret_cast<const char*>(bitmap_info_header), kBitmapV5Header);

    uint64_t cnt = 1;
    for (auto color : colors) {
        output << color.b << color.g << color.r;

        if (cnt == length) {
            cnt = 0;
            for (uint64_t i = 0; i < extra_to_str; i++) {
                output << 0;
            }
        }
        cnt++;
    }

    for (int i = 0; i < extra_to_str; i++) {
        output << 0;
    }
}
