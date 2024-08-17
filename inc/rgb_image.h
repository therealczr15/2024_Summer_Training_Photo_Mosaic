# ifndef _RGB_IMAGE_H_
# define _RGB_IMAGE_H_

# include "image.h"

class RGBImage : public Image
{
    public:
        int*** pixel;

        // Constructor
        RGBImage();
        RGBImage(int w, int h);
        RGBImage(int w, int h, int*** p);

        // Destructor
        ~RGBImage();

        // Display Function
        bool LoadImage(string filename);
        void DumpImage(string filename);
        void Display_X_Server();
        void Display_ASCII();
        void Display_CMD();
        int*** GetPixel();

        // Color Space Transformation
        void RGB2YCrCb(int*** Y, int*** Cr, int*** Cb);
        void RGB2HSI(double*** H, double*** S, double*** I);
        void YCrCb2RGB(int** Y, int** Cr, int** Cb);
        void HSI2RGB(double** H, double** S, double** I);

        // Scaling
        void Scaling(int newH, int newW);
        int bilinear(int i, int j, int k, int newH, int newW);

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
        void MotionBlur(int kernelSize, double theta);

        // Brightness Adjustment
        void StaticEnhance(double alpha, double beta);
        void GammaCorrection(double gamma);
        void HistogramEqualization();

        // Chromatic Adaptation
        void MaxRGB();
        void GrayWorld();

        // Special Function
        void SaturationEnhance(double gamma);
        void EdgeDetection();
        void SwirlFilter(double strength);
        void FishEyeFilter();

        // Color Grading
        void SepiaTone();
        void CoolTone();
        void WarmTone();
        void DuoTone(int mode);
        void NegativeFilm();
};

#endif