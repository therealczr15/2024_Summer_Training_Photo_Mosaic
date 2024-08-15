# include "gray_image.h"
 
using namespace std;

// ===== Constructor =====
GrayImage::GrayImage(): Image(0, 0)
{
    pixel = NULL;
}

GrayImage::GrayImage(int w, int h, int** p) : Image(w, h)
{
    pixel = p;
}


// ===== Destructor =====
GrayImage::~GrayImage()
{
    //cout << "Delete GrayImage successfully!" << endl;
    for(int i = 0; i < _h; i++)
        delete[] pixel[i];
    delete[] pixel;
}

// ===== Display Function =====
bool GrayImage::LoadImage(string filename)
{
    pixel = dl.Load_Gray(filename, &_w, &_h);
    if(!pixel)
        return false;
    return true;
}

void GrayImage::DumpImage(string filename)
{
    dl.Dump_Gray(_w, _h, pixel, filename);
}

void GrayImage::Display_X_Server()
{
    dl.Display_Gray_X_Server(_w, _h, pixel);
}

void GrayImage::Display_ASCII()
{
    dl.Display_Gray_ASCII(_w, _h, pixel);
}

void GrayImage::Display_CMD()
{
    string filename = "tmp.jpg";
    dl.Dump_Gray(_w, _h, pixel, filename);
    dl.Display_Gray_CMD(filename);
}

int** GrayImage::GetPixel()
{
    return pixel;
}

// ===== Scaling =====
int GrayImage::bilinear(int i, int j, int newH, int newW)
{
    double x, y, xRatio, yRatio;

    // get inverse ratio, - 1.0 to avoid x0, x1, y0 and y1 from exceeding the boundaries
    xRatio = (_h - 1.0) * 1.0 / (newH - 1.0);
    yRatio = (_w - 1.0) * 1.0 / (newW - 1.0);

    // get the original position where each new pixel point should be on the original image
	x = i * xRatio;
	y = j * yRatio;

    // get 4 nearest pixels of the original position
	int x0 = floor(x);
	int x1 = ceil(x);
	int y0 = floor(y);
	int y1 = ceil(y);

    // bilinear interpolation
	double dx0 = x - x0;
	double dx1 = 1 - dx0;
	double dy0 = y - y0;
	double dy1 = 1 - dy0;

    // get image infomation of the 4 nearest pixels
    int a0 = pixel[x0][y0];
    int a1 = pixel[x0][y1];
    int a2 = pixel[x1][y0];
    int a3 = pixel[x1][y1];

    // calculate by bilinear interpolation
    // first calculate in direction of y
    double b0 = a0 * dy1 + a1 * dy0;
    double b1 = a2 * dy1 + a3 * dy0;

    int ans = b0 * dx1 + b1 * dx0;

    return ans;

}

void GrayImage::Scaling(int newH, int newW)
{
    int** newPixel = new int* [newH];
    for(int i = 0; i < newH; i++)
        newPixel[i] = new int [newW];

    for(int i = 0; i < newH; i++)
        for(int j = 0; j < newW; j++)
            newPixel[i][j] = bilinear(i, j, newH, newW);

    for(int i = 0; i < _h; i++)
        delete[] pixel[i];    
    delete[] pixel;

    _h = newH;
    _w = newW;

    pixel = new int*[_h];
    for(int i = 0; i < _h; i++)
        pixel[i] = new int [_w];

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j] = newPixel[i][j];
    

    for(int i = 0; i < _h; i++)
        delete[] newPixel[i];    
    delete[] newPixel;
}

// ===== Flip =====
void GrayImage::Flip()
{
    // Allocate memory for tmpPixel
    int** tmpPixel = new int* [_h];
    for(int i = 0; i < _h; i++)
        tmpPixel[i] = new int [_w];
    
    // Copy pixel to tmpPixel
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            tmpPixel[i][j] = pixel[i][j];
    
    // Flip Horizontally
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j] = tmpPixel[i][_w - 1 - j];

    // Free memory for tmpPixel
    for(int i = 0; i < _h; i++)
        delete[] tmpPixel[i];
    delete[] tmpPixel;
}

// ===== Quantization =====
void GrayImage::Quantization(int quan)
{
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j] = (pixel[i][j] >> quan) << quan;
}

// ===== Sharpness Enhancement =====
void GrayImage::LaplacianFilter_A()
{
    vector<vector<double>> LaplacianKernel = {  { 0, -1,  0},
                                                {-1,  5, -1},
                                                { 0, -1,  0}}; 
    pixel = conv(pixel, LaplacianKernel, 3);
}

void GrayImage::LaplacianFilter_B()
{
    vector<vector<double>> LaplacianKernel = {  {-1, -1, -1},
                                                {-1,  9, -1},
                                                {-1, -1, -1}}; 
    pixel = conv(pixel, LaplacianKernel, 3);
}

void GrayImage::PrewittFilter_H()
{
    vector<vector<double>> PrewittKernel = {    {-1, 0, 1},
                                                {-1, 1, 1},
                                                {-1, 0, 1}}; 
    pixel = conv(pixel, PrewittKernel, 3);
}

void GrayImage::PrewittFilter_V()
{
    vector<vector<double>> PrewittKernel = {    { 1,  1,  1},
                                                { 0,  1,  0},
                                                {-1, -1, -1}}; 
    pixel = conv(pixel, PrewittKernel, 3);
}

void GrayImage::SobelFilter_H()
{
    vector<vector<double>> SobelKernel = {      {1, 0, -1},
                                                {2, 1, -2},
                                                {1, 0, -1}}; 
    pixel = conv(pixel, SobelKernel, 3);
}

void GrayImage::SobelFilter_V()
{
    vector<vector<double>> SobelKernel = {      { 1,  2,  1},
                                                { 0,  1,  0},
                                                {-1, -2, -1}}; 
    pixel = conv(pixel, SobelKernel, 3);
}

void GrayImage::EmbossFilter()
{
    vector<vector<double>> EmbossKernel = {     {-2, -1,  0},
                                                {-1,  1,  1},
                                                { 0,  1,  2}}; 
    pixel = conv(pixel, EmbossKernel, 3);
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j] = min(255, max(0, static_cast<int>(pixel[i][j] + 128)));
}

// ===== Denoise =====
void GrayImage::BoxFilter(int kerSize)
{
    vector<vector<double>> BoxKernel(kerSize, vector<double> (kerSize)); 
    for(int i = 0; i < kerSize; i++)
        for(int j = 0; j < kerSize; j++)
            BoxKernel[i][j] = 1.0 / (kerSize * kerSize);

    pixel = conv(pixel, BoxKernel, kerSize);
}

void GrayImage::GaussianFilter(int kerSize)
{
    vector<vector<double>> GaussianKernel(kerSize, vector<double> (kerSize)); 
    int halfKerSize = kerSize / 2;
    double sigma = 1.0;
    double s = 2.0 * sigma * sigma;
    double r;
    double sum = 0;

    for(int i = -halfKerSize; i <= halfKerSize; i++)
    {   
        for(int j = -halfKerSize; j <= halfKerSize; j++)
        {
            r = sqrt(i * i + j * j);
            GaussianKernel[i + halfKerSize][j + halfKerSize] = (exp(-(r * r) / s)) / (M_PI * s);
            sum += GaussianKernel[i + halfKerSize][j + halfKerSize];
        }
    }

    for(int i = 0; i < kerSize; i++)
        for(int j = 0; j < kerSize; j++)
            GaussianKernel[i][j] /= sum;

    pixel = conv(pixel, GaussianKernel, kerSize);
}

void GrayImage::MedianFilter(int kerSize)
{
    vector<int> tmp;
    int halfKerSize = kerSize / 2;
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            int row, col;
            for(int k = -halfKerSize; k <= halfKerSize; k++)
            {
                for(int l = -halfKerSize; l <= halfKerSize; l++)
                {
                    row = i + k;
                    col = j + l;
                    if(row >= 0 && col >= 0 && row < _h && col < _w)
                        tmp.push_back(pixel[row][col]);
                }
            }
            sort(tmp.begin(), tmp.end());
            if(tmp.size() % 2 == 1)
                pixel[i][j] = tmp[tmp.size() / 2];
            else
                pixel[i][j] = (tmp[tmp.size() / 2] + tmp[tmp.size() / 2 + 1]) / 2;
            tmp.clear();
        }
    }
}

void GrayImage::MosaicFilter(int kerSize)
{
    for(int i = 0; i < _h; i += kerSize)
    {
        for(int j = 0; j < _w; j += kerSize)
        {
            int row, col;
            int count = 0;
            double sum = 0;
            for(int k = 0; k < kerSize; k++)
            {
                for(int l = 0; l < kerSize; l++)
                {
                    row = i + k;
                    col = j + l;
                    if(row >= 0 && col >= 0 && row < _h && col < _w)
                    {
                        sum += pixel[row][col];
                        count++;
                    }
                }
            }
            double ans = sum * 1.0 / count;
            for(int k = 0; k < kerSize; k++)
            {
                for(int l = 0; l < kerSize; l++)
                {
                    row = i + k;
                    col = j + l;
                    if(row >= 0 && col >= 0 && row < _h && col < _w)
                        pixel[row][col] = ans;
                }
            }
        }
    }
}

void GrayImage::MotionBlur(int kerSize, double theta)
{

    vector<vector<double>> kernel(kerSize, vector<double>(kerSize));
    double rad = theta * M_PI / 180.0;
    int center = kerSize / 2;

    // Populate the kernel
    for (int i = 0; i < kerSize; i++) 
    {
        int x = i - center;
        int y = static_cast<int>(round(x * tan(rad)));
        int row = center + y;
        int col = i;
        if (row >= 0 && row < kerSize)
            kernel[row][col] = 1.0;
    }

    // Normalize the kernel so that the sum of all elements is 1
    double sum = 0;
    for (int i = 0; i < kerSize; i++)
        for (int j = 0; j < kerSize; j++)
            sum += kernel[i][j];
    
    if (sum != 0) 
        for (int i = 0; i < kerSize; i++)
            for (int j = 0; j < kerSize; j++)
                kernel[i][j] /= sum;

    pixel = conv(pixel, kernel, kerSize);
}

// ===== Brightness Adjustment =====
void GrayImage::StaticEnhance(double alpha, double beta)
{
    for(int i = 0; i < _h; i++)   
        for(int j = 0; j < _w; j++)
            pixel[i][j] = min(255, max(0, static_cast<int>(pixel[i][j] * alpha + beta)));

}


void GrayImage::GammaCorrection(double gamma)
{
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j] = pow(pixel[i][j] / 255.0, gamma) * 255;
}

void GrayImage::HistogramEqualization()
{
    // Declare histogram array
    int hist[256] = {0};

    // Count the quantity of 256 levels
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            hist[pixel[i][j]]++;

    // Declare the probability array
    double prob[256] = {0};

    // Calculate the probability of 256 levels
    for(int i = 0; i < 256; i++)
        prob[i] = hist[i] / double(_h * _w);

    // Declare CDF array
    double cdf[256] = {0};

    // Calculate the CDF of 256 levels
    for(int i = 0; i < 256; i++)
    {
        if(i == 0)
            cdf[i] = prob[i];
        else
            cdf[i] = prob[i] + cdf[i - 1];
    }

    // Get Histogram Equalization Result
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j] = min(255, max(0, static_cast<int>(255 * cdf[pixel[i][j]])));

}

// ===== Chromatic Adaptation =====
void GrayImage::MaxRGB()
{
    int maxPixel = 0;

    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            if(pixel[i][j] > maxPixel)
                maxPixel = pixel[i][j];
        }
    }

    double ratio = 255.0 / maxPixel;
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j] = min(255, max(0, static_cast<int>(pixel[i][j] * ratio)));
}

void GrayImage::GrayWorld()
{
    cout << "ERROR: Gray World can't be applied in GrayImage.";
}
 
// ====== Saturation Adjustment =====
void GrayImage::SaturationEnhance(double gamma)
{
    cout << "ERROR: Saturation Enhance can't be applied in GrayImage.";
}

// ===== Color Grading =====
void GrayImage::SepiaTone()
{
    cout << "ERROR: Sepia Tone can't be applied in GrayImage.";
}

void GrayImage::CoolTone()
{
    cout << "ERROR: Cool Tone can't be applied in GrayImage.";
}

void GrayImage::WarmTone()
{
    cout << "ERROR: Warm Tone can't be applied in GrayImage.";
}

void GrayImage::NegativeFilm()
{
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j] = 255 - pixel[i][j];
}