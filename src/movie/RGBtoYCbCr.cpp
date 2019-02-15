//
//  RGBtoYCbCr.cpp
//  firstSketch
//
//  Created by Egon Firman on 15/02/19.
//

#include "RGBtoYCbCr.hpp"
#include <stdlib.h>

RGBtoYCbCr::RGBtoYCbCr(int width, int height, int channel) {
    this->width = width;
    this->height = height;
    this->channel = channel;
    
    y_size = width * height;
    cb_size = cr_size = y_size / 4;
    size = y_size + cb_size + cr_size;
    
    yuvImage = (unsigned char *) malloc(size);
}

RGBtoYCbCr::~RGBtoYCbCr() {
    delete yuvImage;
}

void RGBtoYCbCr::setRGB(unsigned char * rgbImage) {
    
    unsigned char r, g, b;
    for (int y=0; y < height; y++) {
        for (int x=0; x < width; x++) {
            int index = y * (width * channel) + (x * channel);
            r = *(rgbImage + index + 0);
            g = *(rgbImage + index + 1);
            b = *(rgbImage + index + 2);
            
            int yIndex = y * width + x;
            yuvImage[yIndex] = (unsigned char) rgb_to_y(r, g, b);
            
            if (x %2 == 0 && y %2== 0) {
                int pos_v = (y / 2) * (width / 2) + (x / 2) + y_size;
                int pos_u = (y / 2) * (width / 2) + (x / 2) + y_size + cb_size;
                
                yuvImage[pos_u] = (unsigned char) rgb_to_u(r,g,b);
                yuvImage[pos_v] = (unsigned char) rgb_to_v(r,g,b);
            }
        }
    }
}

int RGBtoYCbCr::rgb_to_y(int r, int g, int b) {
    int ya, yta;
    ya = 66 * r + 129 * g + 25 * b;
    yta =  (ya + 128) >> 8;
    int result =  yta + 16;
    return result;
}

int RGBtoYCbCr::rgb_to_u(int r, int g, int b) {
    int ua, uta;
    ua = -38 * r + -74 * g + 112 * b;
    uta =  (ua + 128) >> 8;
    return uta + 128;
}

int RGBtoYCbCr::rgb_to_v(int r, int g, int b) {
    int va, vta;
    va = 112 * r + -94 * g + -18 * b;
    vta =  (va + 128) >> 8;
    return vta + 128;
}
