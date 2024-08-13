# ifndef _RGB_IMAGE_H_
# define _RGB_IMAGE_H_

# include "image.h"

class RGBImage : public Image
{
    private:
        int*** pixel;

    public:
        // Constructor
        RGBImage();
        RGBImage(int w, int h, int*** p);

        // Destructor
        ~RGBImage();

        // Display Function
        bool LoadImage(string filename);
        void DumpImage(string filename);
        void Display_X_Server();
        void Display_ASCII();
        void Display_CMD();

        // Color Space Transformation
        void RGB2YCrCb(int*** Y, int*** Cr, int*** Cb);
        //void RGB2HSI(double*** H, double*** S, double*** I);
        void YCrCb2RGB(int** Y, int** Cr, int** Cb);
        //void HSI2RGB(double** H, double** S, double** I);

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

        // Denoise
        void BoxFilter(int kerSize);
        void GaussianFilter(int kerSize);
        void MedianFilter(int kerSize);

        // Brightness Adjustment
        void StaticEnhance(double alpha, double beta);
        void GammaCorrection(double gamma);
        void HistogramEqualization();

        // Chromatic Adaptation
        void MaxRGB();
        void GrayWorld();
};

#endif