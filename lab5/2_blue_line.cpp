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

    for (int j = 0; j < img.height(); j++){
        img(i, j, 0, 0) = 0;  // set red channel to 0
        img(i, j, 0, 1) = 0;  // set green channel to 0
        img(i, j, 0, 2) = 255;  // set blue channel to 255
    }

    img.display("Image with vertical blue line");             // Display the image in a display window

    return 0;
}