# include "bit_field_filter.h"

using namespace std;

// FLip
void Flip(Image* img)
{
    img -> Flip();
}

// Brightness Adjustment
void GammaCorrection(Image* img, double gamma)
{
    img -> GammaCorrection(gamma);
}