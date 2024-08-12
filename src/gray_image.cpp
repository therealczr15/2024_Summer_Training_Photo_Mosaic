# include "gray_image.h"
 
using namespace std;

// ===== Constructor =====
GrayImage::GrayImage(): Image(0, 0)
{
    pixel = NULL;
}

GrayImage::GrayImage(int w, int h, int** p) : Image(w, h)
{
    pixel = p;
}


// ===== Destructor =====
GrayImage::~GrayImage()
{
    for(int i = 0; i < _h; i++)
        delete[] pixel[i];
    delete[] pixel;
}

// ===== Public Member Function =====
bool GrayImage::LoadImage(string filename)
{
    pixel = dl.Load_Gray(filename, &_w, &_h);
    if(!pixel)
        return false;
    return true;
}

void GrayImage::DumpImage(string filename)
{
    dl.Dump_Gray(_w, _h, pixel, filename);
}

void GrayImage::Display_X_Server()
{
    dl.Display_Gray_X_Server(_w, _h, pixel);
}

void GrayImage::Display_ASCII()
{
    dl.Display_Gray_ASCII(_w, _h, pixel);
}

void GrayImage::Display_CMD()
{
    string filename = "tmp.jpg";
    dl.Dump_Gray(_w, _h, pixel, filename);
    dl.Display_Gray_CMD(filename);
}

