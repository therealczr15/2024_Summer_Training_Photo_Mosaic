# include "bit_field_filter.h"

using namespace std;

// ===== FLip =====
void Flip(Image* img)
{
    img -> Flip();
}

// ===== Quantization =====
void Quantization(Image* img, int quan)
{
    img -> Quantization(quan);
}

// ===== Sharpness Enhancement =====
void LaplacianFilter_A(Image* img)
{
    img -> LaplacianFilter_A();
}

void LaplacianFilter_B(Image* img)
{
    img -> LaplacianFilter_B();
}

void PrewittFilter_H(Image* img)
{
    img -> PrewittFilter_H();
}

void PrewittFilter_V(Image* img)
{
    img -> PrewittFilter_V();
}

void SobelFilter_H(Image* img)
{
    img -> SobelFilter_H();
}

void SobelFilter_V(Image* img)
{
    img -> SobelFilter_V();
}

// ===== Denoise =====
void BoxFilter(Image* img, int kernelSize)
{
    img -> BoxFilter(kernelSize);
}

void GaussianFilter(Image* img, int kernelSize)
{
    img -> GaussianFilter(kernelSize);
}

void MedianFilter(Image* img, int kernelSize)
{
    img -> MedianFilter(kernelSize);
}

// ===== Brightness Adjustment =====
void StaticEnhance(Image* img, double alpha, double beta)
{
    img -> StaticEnhance(alpha, beta);
}

void GammaCorrection(Image* img, double gamma)
{
    img -> GammaCorrection(gamma);
}

void HistogramEqualization(Image* img)
{
    img -> HistogramEqualization();
}

// ===== Chromatic Adaptation =====
void MaxRGB(Image* img)
{
    img -> MaxRGB();
}

void GrayWorld(Image* img)
{
    img -> GrayWorld();
}