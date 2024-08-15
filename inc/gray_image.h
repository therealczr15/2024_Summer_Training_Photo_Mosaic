# ifndef _GRAY_IMAGE_H_
# define _GRAY_IMAGE_H_

# include "image.h"

class GrayImage : public Image
{
    public:
        int** pixel;

        // Constructor
        GrayImage();
        GrayImage(int w, int h, int** p);

        // Destructor
        ~GrayImage();

        // Display Function
        bool LoadImage(string filename);
        void DumpImage(string filename);
        void Display_X_Server();
        void Display_ASCII();
        void Display_CMD();
        int** GetPixel();

        // Scaling
        void Scaling(int newH, int newW);
        int bilinear(int i, int j, int newH, int newW);

        // Flip
        void Flip();

        // Quantization
        void Quantization(int quan);

        // Sharpness Enhancement
        void LaplacianFilter_A();
        void LaplacianFilter_B();
        void PrewittFilter_H();
        void PrewittFilter_V();
        void SobelFilter_H();
        void SobelFilter_V();
        void EmbossFilter();
        
        // Denoise
        void BoxFilter(int kerSize);
        void GaussianFilter(int kerSize);
        void MedianFilter(int kerSize);
        void MosaicFilter(int kerSize);
        void MotionBlur(int kerSize, double theta);

        // Brightness Adjustment
        void StaticEnhance(double alpha, double beta);
        void GammaCorrection(double gamma);
        void HistogramEqualization();

        // Chromatic Adaptation
        void MaxRGB();
        void GrayWorld();

        // Saturation Adjustment 
        void SaturationEnhance(double gamma);

        // Color Grading
        void SepiaTone();
        void CoolTone();
        void WarmTone();
        void NegativeFilm();
};

#endif