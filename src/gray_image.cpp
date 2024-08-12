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

// ===== Display Function =====
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

// ===== Flip =====
void GrayImage::Flip()
{
    // Allocate memory for tmpPixel
    int** tmpPixel = new int* [_h];
    for(int i = 0; i < _h; i++)
        tmpPixel[i] = new int [_w];
    
    // Copy pixel to tmpPixel
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            tmpPixel[i][j] = pixel[i][j];
    
    // Flip Horizontally
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j] = tmpPixel[i][_w - 1 - j];
}

// ===== Brightness Adjustment =====
void GrayImage::GammaCorrection(double gamma)
{
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j] = pow(pixel[i][j] /255.0, gamma) * 255;
}
