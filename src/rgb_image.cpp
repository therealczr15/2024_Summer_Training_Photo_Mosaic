# include "rgb_image.h"
 
using namespace std;

// ===== Constructor =====
RGBImage::RGBImage(): Image(0, 0)
{
    pixel = NULL;
}

RGBImage::RGBImage(int w, int h, int*** p) : Image(w, h)
{
    pixel = p;
}

// ===== Destructor =====
RGBImage::~RGBImage()
{
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            delete[] pixel[i][j];
    for(int i = 0; i < _h; i++)
        delete[] pixel[i];
    delete[] pixel;
}

// ===== Public Member Function =====
bool RGBImage::LoadImage(string filename)
{
    pixel = dl.Load_RGB(filename, &_w, &_h);
    if(!pixel)
        return false;
    return true;
}

void RGBImage::DumpImage(string filename)
{
    dl.Dump_RGB(_w, _h, pixel, filename);
}

void RGBImage::Display_X_Server()
{
    dl.Display_RGB_X_Server(_w, _h, pixel);
}

void RGBImage::Display_ASCII()
{
    dl.Display_RGB_ASCII(_w, _h, pixel);
}

void RGBImage::Display_CMD()
{
    string filename = "tmp.jpg";
    dl.Dump_RGB(_w, _h, pixel, filename);
    dl.Display_RGB_CMD(filename);
}

