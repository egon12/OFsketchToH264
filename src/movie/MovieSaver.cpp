//
//  MovieSaver.cpp
//  firstSketch
//
//  Created by Egon Firman on 14/02/19.
//

#include "MovieSaver.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <x264.h>

MovieSaver::MovieSaver(const char* filename, int width, int height) {
    // only convert rgba;
    converter = new RGBtoYCbCr(width, height, 4);
    
    int err = 0;
    
    err = initFileOutput(filename);
    if (err < 0) throw "Cannot open output file";

    err = initPic(width, height);
    if (err < 0) throw "Cannot initialize input Picture";

    err = initEncoder(width, height);
    if (err < 0) throw "Cannot initialize EncoderPicture";
};

MovieSaver::~MovieSaver() {
    encodeReminder();
    x264_encoder_close( h );
    fclose(file);
    delete converter;
};

void MovieSaver::addFrame(unsigned char *rgbaImage) {
    converter->setRGB(rgbaImage);
    encode();
}

int MovieSaver::initEncoder(int width, int height) {
    
    int err = 0;
    x264_param_t param;
    
    err = x264_param_default_preset(&param, "medium", NULL);
    if (err < 0) {
        return err;
    }
    
    param.i_width = width;
    param.i_height = height;
    param.i_csp = X264_CSP_I420;
    param.b_vfr_input = 0;
    param.b_repeat_headers = 1;
    param.b_annexb = 1;
    
    err = x264_param_apply_profile( &param, "high");
    if (err < 0) {
        printf("Error when set profile\n");
        return err;
    }
    
    h = x264_encoder_open(&param);
    return 0;
}

int MovieSaver::initPic(int width, int height) {
    x264_picture_init(&pic);
    pic.img.i_csp = X264_CSP_I420;
    pic.img.i_plane = 3;
    pic.img.i_stride[0] = width;
    pic.img.i_stride[1] = width / 2;
    pic.img.i_stride[2] = width / 2;
    
    pic.img.plane[0] = converter->yuvImage;
    pic.img.plane[1] = converter->yuvImage + converter->y_size;
    pic.img.plane[2] = converter->yuvImage + converter->y_size + converter->cb_size;
    
    return 0;
}

int MovieSaver::initFileOutput(const char *filename) {
    file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Failed open file to wirte:");
        return errno;
    }
    return 0;
}

int MovieSaver::encode() {
    
    int result = x264_encoder_encode(h, &nal, &i_nal, &pic, &pic_out);
    if (result < 0) {
        printf("Error when encoding");
        return result;
    }
    
    if (result == 0) {
        return;
    }
    
    int byte_write = fwrite(nal->p_payload, 1, result, file);
    if (byte_write < 0) {
        printf("After encoding failed to write to file");
        return byte_write;
    }
    
    if (byte_write < result)
        printf("Must to write %d bytes, but only able to write %d", result, byte_write);
        return -1;
        
    return 0;
}

int MovieSaver::encodeReminder() {
    while( x264_encoder_delayed_frames( h ) )
    {
        int result = x264_encoder_encode( h, &nal, &i_nal, NULL, &pic_out );
        if( result < 0 ) {}
        else if (result) {
            fwrite(nal->p_payload, result, 1, file);
        }
    }
    return 0;
}

//---------------------------------------------------------------
// x264





//int prepareX264(int width, int height) {
//
//
//    int result = x264_encoder_headers(h, &nal, &i_nal);
//
//    int byte_write = fwrite(nal->p_payload, 1, result, file);
//    if (byte_write < 0) {
//        std::cout << "After encoding failed to write to file";
//        return byte_write;
//    }
//
//    if (byte_write < result) {
//        std::cout << "must to write " << result << " bytes. but ony write" << byte_write;
//    }
//    std::cout << "write " << byte_write << " bytes for " << i_nal << "nal units \n";
//
//
//    return 0;
//}
//
