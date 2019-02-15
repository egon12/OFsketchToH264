#include <iostream>
#include "../src/movie/RGBtoYCbCr.hpp"


int main() {

  int w, h, c;
  w = h = 2;
  c = 3;
  unsigned char rgb_data[12] = {255, 255, 255,  255, 255, 255,  255, 255, 255,  255, 255, 255};


  auto converter = new RGBtoYCbCr(w, h, c);


  converter->setRGB(rgb_data);
  auto yuvImage = converter->yuvImage;
  for (int i=0; i<4; i++) {
    std::cout << (int) yuvImage[i] << ",";
  }
  std::cout << "\n";


}
