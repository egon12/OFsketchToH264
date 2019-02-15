//
//  MovieSaver.hpp
//  firstSketch
//
//  Created by Egon Firman on 14/02/19.
//

#ifndef MovieSaver_hpp
#define MovieSaver_hpp


#include <iostream>
#include <x264.h>
#include "RGBtoYCbCr.hpp"

class MovieSaver {
    
public:
    MovieSaver(const char * filename, int width, int height);
    ~MovieSaver();
    void addFrame(unsigned char *rgbaImage);
    void end();
    
private:
    x264_t *h;
    x264_picture_t pic, pic_out;
    RGBtoYCbCr *converter;
    FILE *file;
    
    x264_nal_t *nal;
    int i_nal;

    int initFileOutput(const char *filename);
    int initEncoder(int width, int height);
    int initPic(int width, int height);
    int writeHeaders();
    int encode();
    int encodeReminder();

    
    
};


#endif /* MovieSaver_hpp */
