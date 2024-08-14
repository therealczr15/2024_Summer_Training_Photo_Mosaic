# ifndef BIT_FIELD_FILTER_H
# define BIT_FIELD_FILTER_H

# include "image.h"
# include "gray_image.h"
# include "rgb_image.h"

/*# define Box_Filter                  0b00000001
# define Median_Filter               0b00000010
# define Contrast_Streching          0b00000100
# define Mosiac_Filter               0b00001000
# define Alpha_Trimmed_Mean_Filter   0b00010000
# define Sobel_Gradient_Filter       0b00100000*/

// FLip
void Flip(Image* img);

// Quantization
void Quantization(Image* img, int quan);

// Sharpness Enhancement
void LaplacianFilter_A(Image* img);
void LaplacianFilter_B(Image* img);
void PrewittFilter_H(Image* img);
void PrewittFilter_V(Image* img);
void SobelFilter_H(Image* img);
void SobelFilter_V(Image* img);

// Denoise
void BoxFilter(Image* img, int kernelSize);
void GaussianFilter(Image* img, int kernelSize);
void MedianFilter(Image* img, int kernelSize);

// Brightness Adjustment
void StaticEnhance(Image* img, double alpha, double beta);
void GammaCorrection(Image* img, double gamma);
void HistogramEqualization(Image* img);

// Chromatic Adaptation
void MaxRGB(Image* img);
void GrayWorld(Image* img);

// Saturation Adjustment
//void SaturationEnhance(RGBImage* img);

// API
void Filter(Image* img);
void LoadOptions(uint16_t &options, int case_n);
void RunOptions(Image* img, uint16_t options);

# endif