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

int** Image::conv(int** pixel, vector<vector<double>> kernel, int kerSize)
{
    int halfKerSize = kerSize / 2;
    int** ansPixel = new int* [_h];
    for(int i = 0; i < _h; i++)
        ansPixel[i] = new int [_w];
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            double convSum = 0;
            int row, col;
            for(int k = -halfKerSize; k <= halfKerSize; k++)
            {
                for(int l = -halfKerSize; l <= halfKerSize; l++)
                {
                    row = i + k;
                    col = j + l;
                    if(row < 0)
                        row = 0;
                    if(col < 0)
                        col = 0;
                    if(row >= _h)
                        row = _h - 1;
                    if(col >= _w)
                        col = _w - 1;
                    convSum += pixel[row][col] * kernel[k + halfKerSize][l + halfKerSize];
                }
            }
            if(convSum >= 255.0)
                ansPixel[i][j] = 255;
            else if(convSum <= 0)
                ansPixel[i][j] = 0;
            else
                ansPixel[i][j] = convSum;
        }
    }
    for(int i = 0; i < _h; i++)
        delete[] pixel[i];    
    delete[] pixel;
    return ansPixel;
}