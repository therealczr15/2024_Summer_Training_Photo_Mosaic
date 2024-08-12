# include "image.h"
 
using namespace std;

// ===== Initialize Data Loader =====
Data_Loader Image::dl;

// ===== Constructor =====
Image::Image()
{
    _w = 0;
    _h = 0;
}

Image::Image(int w, int h)
{
    _w = w;
    _h = h;
}

// ===== Destructor =====
Image::~Image(){
    ;
}

// ===== Public Member Function =====
int Image::get_width()
{
    return _w;
}

int Image::get_height()
{
    return _h;
}
