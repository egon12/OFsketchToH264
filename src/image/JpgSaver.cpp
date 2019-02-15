//
//  JpgSaver.cpp
//  firstSketch
//
//  Created by Egon Firman on 15/02/19.
//

#include <iostream>
#include "JpgSaver.hpp"
#include "jpeglib.h"

void JpgSaver::save(char* filename, unsigned char *data, int width, int height) {
    
    FILE* fileDescriptor = fopen(filename, "wb");
    if (fileDescriptor == NULL) {
        fprintf(stderr, "Can't open file %s\n", filename);
        return;
    }
    
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;
    
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    
    jpeg_stdio_dest(&cinfo, fileDescriptor);
    
    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_YCbCr;
    
    jpeg_set_defaults(&cinfo);
    
    jpeg_set_quality(&cinfo, 80, TRUE);
    
    jpeg_start_compress(&cinfo, TRUE);
    
    int row_stride = width * cinfo.input_components;
    
    JSAMPROW row_pointer[1];
    

    int scanline = cinfo.next_scanline;
    while (scanline < cinfo.image_height) {
      std::cout << "scanline:" << scanline << "\n";
      row_pointer[0] = & data[cinfo.next_scanline * row_stride];
      (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
      scanline = cinfo.next_scanline;
    }
    
    jpeg_finish_compress(&cinfo);

    fclose(fileDescriptor);
    
    jpeg_destroy_compress(&cinfo);
}
