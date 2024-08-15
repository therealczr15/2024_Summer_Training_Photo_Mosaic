# ifndef BIT_FIELD_FILTER_H
# define BIT_FIELD_FILTER_H

# include "image.h"
# include "gray_image.h"
# include "rgb_image.h"

// Scaling
void Scaling(Image* img, int newH, int newW);

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
void EmbossFilter(Image* img);

// Denoise
void BoxFilter(Image* img, int kernelSize);
void GaussianFilter(Image* img, int kernelSize);
void MedianFilter(Image* img, int kernelSize);
void MosaicFilter(Image* img, int kernelSize);
void MotionBlur(Image* img, int kernelSize, double theta);

// Brightness Adjustment
void StaticEnhance(Image* img, double alpha, double beta);
void GammaCorrection(Image* img, double gamma);
void HistogramEqualization(Image* img);

// Chromatic Adaptation
void MaxRGB(Image* img);
void GrayWorld(Image* img);

// Saturation Adjustment
void SaturationEnhance(Image* img, double gamma);

// Color Grading
void SepiaTone(Image* img);
void CoolTone(Image* img);
void WarmTone(Image* img);
void NegativeFilm(Image* img);

// API
void Filter(Image* img);
void LoadOptions(uint32_t &options, int case_n);
void RunOptions(Image* img, uint32_t options);


# endif