# ifndef _IMAGE_H_
# define _IMAGE_H_

# include "data_loader.h"
# include <iostream>
# include <stdint.h>
# include <bitset>
# include <string>
# include <cmath>
# include <vector>
# include <algorithm>
# include <float.h>

using namespace std;

class Image
{
    protected:
        int _w;
        int _h;
        static Data_Loader dl;

    public:
        // Constructor
        Image();
        Image(int w, int h);

        // Destructor
        virtual ~Image();

        // Pure Virtual Fucntion
        // Display Function
        virtual bool LoadImage(string filename) = 0;
        virtual void DumpImage(string filename) = 0;
        virtual void Display_X_Server() = 0;
        virtual void Display_ASCII() = 0;
        virtual void Display_CMD() = 0;

        // Scaling
        virtual void Scaling(int newH, int newW) = 0;

        // Flip
        virtual void Flip() = 0;

        // Quantization
        virtual void Quantization(int quan) = 0;

        // Sharpness Enhancement
        virtual void LaplacianFilter_A() = 0;
        virtual void LaplacianFilter_B() = 0;
        virtual void PrewittFilter_H() = 0;
        virtual void PrewittFilter_V() = 0;
        virtual void SobelFilter_H() = 0;
        virtual void SobelFilter_V() = 0;
        virtual void EmbossFilter() = 0;

        // Denoise
        virtual void BoxFilter(int kerSize) = 0;
        virtual void GaussianFilter(int kerSize) = 0;
        virtual void MedianFilter(int kerSize) = 0;
        virtual void MosaicFilter(int kerSize) = 0;
        virtual void MotionBlur(int kernelSize, double theta) = 0;

        // Brightness Adjustment
        virtual void StaticEnhance(double alpha, double beta) = 0;
        virtual void GammaCorrection(double gamma) = 0;
        virtual void HistogramEqualization() = 0;

        // Chromatic Adaptation
        virtual void MaxRGB() = 0;
        virtual void GrayWorld() = 0;

        // Saturation Adjustment
        virtual void SaturationEnhance(double gamma) = 0;
        
        // Color Grading
        virtual void SepiaTone() = 0;
        virtual void CoolTone() = 0;
        virtual void WarmTone() = 0;
        virtual void NegativeFilm() = 0;

        // Member Function
        int get_width();
        int get_height();
        int** conv(int** pixel, vector<vector<double>> kernel, int kerSize);
};

#endif