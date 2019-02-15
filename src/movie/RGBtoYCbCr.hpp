//
//  RGBtoYCbCr.hpp
//  firstSketch
//
//  Created by Egon Firman on 15/02/19.
//

#ifndef RGBtoYCbCr_hpp
#define RGBtoYCbCr_hpp

#include <stdio.h>

class RGBtoYCbCr {
    
public:
    RGBtoYCbCr(int width, int height, int channel);
    ~RGBtoYCbCr();
    void setRGB(unsigned char *rgbImage);
    unsigned char *yuvImage;
    
    int size;
    int y_size;
    int cb_size;
    int cr_size;
    
private:
    int width;
    int height;
    int channel;
    
    int rgb_to_y(int r, int g, int b);
    int rgb_to_u(int r, int g, int b);
    int rgb_to_v(int r, int g, int b);

};

#endif /* RGBtoYCbCr_hpp */
