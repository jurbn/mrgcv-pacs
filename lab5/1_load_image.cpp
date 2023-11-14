#include <iostream>
#include "CImg-3.3.2/CImg.h"

using namespace cimg_library;

int main(){
  CImg<unsigned char> img("image.jpg");  // Load image file "image.jpg" at object img
  // print the width, height, depth and spectrum of the image
  std::cout << "Image width: " << img.width() << "\nImage height: " << img.height() << "\nNumber of slices: " << img.depth() <<
    "\nNumber of channels: " << img.spectrum() << std::endl;  //dump some characteristics of the loaded image

  int i = img.width() / 2;
  int j = img.height() / 2;
  // NOTE: keep in mind that this prints the HEX value of the channel
  std::cout << std::hex << (int) img(i, j, 0, 0) << std::endl;  //print pixel value for channel 0 (red) 
  std::cout << std::hex << (int) img(i, j, 0, 1) << std::endl;  //print pixel value for channel 1 (green) 
  std::cout << std::hex << (int) img(i, j, 0, 2) << std::endl;  //print pixel value for channel 2 (blue) 
  
  img.display("My first CImg code");             // Display the image in a display window

  return 0;
}