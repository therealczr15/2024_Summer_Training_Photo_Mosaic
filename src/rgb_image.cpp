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

// ===== Display Function =====
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

// ===== Color Space Transformation
void RGBImage::RGB2YCrCb(int*** Y, int*** Cr, int*** Cb)
{
    // Allocate Y, Cr & Cb's memory
    int** _Y  = new int* [_h];
    int** _Cr = new int* [_h];
    int** _Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        _Y[i]  = new int[_w];
        _Cr[i] = new int[_w];
        _Cb[i] = new int[_w];
    }

    // Calculate Y, Cr & Cb
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            _Y [i][j] = pixel[i][j][0] * 0.299 + pixel[i][j][1] * 0.587 + pixel[i][j][2] * 0.114;
            _Cr[i][j] = (pixel[i][j][0] - _Y[i][j]) * 0.713 + 128.0;
            _Cb[i][j] = (pixel[i][j][2] - _Y[i][j]) * 0.564 + 128.0;
        }
    }

    *Y  = _Y;
    *Cr = _Cr;
    *Cb = _Cb;
}

/*void RGBImage::RGB2HSI(double*** H, double*** S, double*** I)
{

}*/

void RGBImage::YCrCb2RGB(int** Y, int** Cr, int** Cb)
{
    int R, G, B;
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            R = Y[i][j] + 1.403 * (Cr[i][j] - 128);
            G = Y[i][j] - 0.714 * (Cr[i][j] - 128) - 0.344 * (Cb[i][j] - 128);
            B = Y[i][j] + 1.773 * (Cb[i][j] - 128);

            // to avoid R going beyond the range
            if(R >= 255)
                pixel[i][j][0] = 255;
            else if(R <= 0)
                pixel[i][j][0] = 0;
            else
                pixel[i][j][0] = R;
            
            // to avoid G going beyond the range
            if(G >= 255)
                pixel[i][j][1] = 255;
            else if(G <= 0)
                pixel[i][j][1] = 0;
            else
                pixel[i][j][1] = G;
            
            // to avoid B going beyond the range
            if(B >= 255)
                pixel[i][j][2] = 255;
            else if(B <= 0)
                pixel[i][j][2] = 0;
            else
                pixel[i][j][2] = B;
        }
    }
}

/*void RGBImage::HSI2RGB(double** H, double** S, double** I)
{

}*/

// ===== Flip =====
void RGBImage::Flip()
{
    // Allocate memory for tmpPixel
    int*** tmpPixel = new int** [_h];
    for(int i = 0; i < _h; i++)
    {
        tmpPixel[i] = new int* [_w];
        for(int j = 0; j < _w; j++)
            tmpPixel[i][j] = new int[3];
    }
    
    // Copy pixel to tmpPixel
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            for(int k = 0; k < 3; k++)
                tmpPixel[i][j][k] = pixel[i][j][k];
    
    // Flip Horizontally
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            for(int k = 0; k < 3; k++)
                pixel[i][j][k] = tmpPixel[i][_w - 1 - j][k];
}

// ===== Brightness Adjustment =====
void RGBImage::GammaCorrection(double gamma)
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            Y[i][j] = pow(Y[i][j] /255.0, gamma) * 255;

    YCrCb2RGB(Y, Cr, Cb);
}