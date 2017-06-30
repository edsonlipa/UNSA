#include "CImg.h"
using namespace cimg_library;
int main () {
    CImg<unsigned char> img("jaffejpg/KA.AN1.39.jpg");
    img.display("Hello, CImg!");
    
    return 0;
}
