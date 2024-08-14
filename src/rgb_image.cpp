# include "rgb_image.h"
 
using namespace std;

// ===== Constructor =====
RGBImage::RGBImage(): Image(0, 0)
{
    pixel = NULL;
}

RGBImage::RGBImage(int w, int h, int*** p) : Image(w, h)
{
    pixel = p;
}

// ===== Destructor =====
RGBImage::~RGBImage()
{
    //cout << "Delete RGBImage successfully!" << endl;
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            delete[] pixel[i][j];
    for(int i = 0; i < _h; i++)
        delete[] pixel[i];
    delete[] pixel;
}

// ===== Display Function =====
bool RGBImage::LoadImage(string filename)
{
    pixel = dl.Load_RGB(filename, &_w, &_h);
    if(!pixel)
        return false;
    return true;
}

void RGBImage::DumpImage(string filename)
{
    dl.Dump_RGB(_w, _h, pixel, filename);
}

void RGBImage::Display_X_Server()
{
    dl.Display_RGB_X_Server(_w, _h, pixel);
}

void RGBImage::Display_ASCII()
{
    dl.Display_RGB_ASCII(_w, _h, pixel);
}

void RGBImage::Display_CMD()
{
    string filename = "tmp.jpg";
    dl.Dump_RGB(_w, _h, pixel, filename);
    dl.Display_RGB_CMD(filename);
}

// ===== Color Space Transformation
void RGBImage::RGB2YCrCb(int*** Y, int*** Cr, int*** Cb)
{
    // Calculate Y, Cr & Cb
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            //cout << i << " " << j << endl;
            (*Y) [i][j] = pixel[i][j][0] * 0.299 + pixel[i][j][1] * 0.587 + pixel[i][j][2] * 0.114;
            (*Cr)[i][j] = (pixel[i][j][0] - (*Y) [i][j]) * 0.713 + 128.0;
            (*Cb)[i][j] = (pixel[i][j][2] - (*Y) [i][j]) * 0.564 + 128.0;
        }
    }
}

/*void RGBImage::RGB2HSI(double*** H, double*** S, double*** I)
{

}*/

void RGBImage::YCrCb2RGB(int** Y, int** Cr, int** Cb)
{
    int R, G, B;
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            R = Y[i][j] + 1.403 * (Cr[i][j] - 128);
            G = Y[i][j] - 0.714 * (Cr[i][j] - 128) - 0.344 * (Cb[i][j] - 128);
            B = Y[i][j] + 1.773 * (Cb[i][j] - 128);

            // to avoid R going beyond the range
            if(R >= 255)
                pixel[i][j][0] = 255;
            else if(R <= 0)
                pixel[i][j][0] = 0;
            else
                pixel[i][j][0] = R;
            
            // to avoid G going beyond the range
            if(G >= 255)
                pixel[i][j][1] = 255;
            else if(G <= 0)
                pixel[i][j][1] = 0;
            else
                pixel[i][j][1] = G;
            
            // to avoid B going beyond the range
            if(B >= 255)
                pixel[i][j][2] = 255;
            else if(B <= 0)
                pixel[i][j][2] = 0;
            else
                pixel[i][j][2] = B;
        }
    }
}

/*void RGBImage::HSI2RGB(double** H, double** S, double** I)
{

}*/

// ===== Scaling =====
int RGBImage::bilinear(int i, int j, int k, int newH, int newW)
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
    int a0 = pixel[x0][y0][k];
    int a1 = pixel[x0][y1][k];
    int a2 = pixel[x1][y0][k];
    int a3 = pixel[x1][y1][k];

    // calculate by bilinear interpolation
    // first calculate in direction of y
    double b0 = a0 * dy1 + a1 * dy0;
    double b1 = a2 * dy1 + a3 * dy0;

    int ans = b0 * dx1 + b1 * dx0;

    return ans;
}

void RGBImage::Scaling(int newH, int newW)
{

    int*** newPixel = new int** [newH];
    for(int i = 0; i < newH; i++)
    {
        newPixel[i] = new int* [newW];
        for(int j = 0; j < newW; j++)
            newPixel[i][j] = new int[3];
    }

    for(int i = 0; i < newH; i++)
        for(int j = 0; j < newW; j++)
            for(int k = 0; k < 3; k++)
                newPixel[i][j][k] = bilinear(i, j, k, newH, newW);

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            delete[] pixel[i][j];
    for(int i = 0; i < _h; i++)
        delete[] pixel[i];
    delete[] pixel;

    _h = newH;
    _w = newW;

    pixel = new int** [_h];
    for(int i = 0; i < _h; i++)
    {
        pixel[i] = new int* [_w];
        for(int j = 0; j < _w; j++)
            pixel[i][j] = new int[3];
    }

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            for(int k = 0; k < 3; k++)
                pixel[i][j][k] = newPixel[i][j][k];
    

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            delete[] newPixel[i][j];
    for(int i = 0; i < _h; i++)
        delete[] newPixel[i];
    delete[] newPixel;
}

// ===== Flip =====
void RGBImage::Flip()
{
    // Allocate memory for tmpPixel
    int*** tmpPixel = new int** [_h];
    for(int i = 0; i < _h; i++)
    {
        tmpPixel[i] = new int* [_w];
        for(int j = 0; j < _w; j++)
            tmpPixel[i][j] = new int[3];
    }
    
    // Copy pixel to tmpPixel
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            for(int k = 0; k < 3; k++)
                tmpPixel[i][j][k] = pixel[i][j][k];
    
    // Flip Horizontally
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            for(int k = 0; k < 3; k++)
                pixel[i][j][k] = tmpPixel[i][_w - 1 - j][k];

    // Free memory for tmpPixel
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            delete[] tmpPixel[i][j];
    for(int i = 0; i < _h; i++)
        delete[] tmpPixel[i];
    delete[] tmpPixel;
}

// ===== Quantization =====
void RGBImage::Quantization(int quan)
{
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            for(int k = 0; k < 3; k++)
                pixel[i][j][k] = (pixel[i][j][k] >> quan) << quan;
}

// ===== Sharpness Enhancement =====
void RGBImage::LaplacianFilter_A()
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

    vector<vector<double>> LaplacianKernel = {  { 0, -1,  0},
                                                {-1,  4, -1},
                                                { 0, -1,  0}}; 
    Y = conv(Y, LaplacianKernel, 3);

    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

void RGBImage::LaplacianFilter_B()
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

    vector<vector<double>> LaplacianKernel = {  {-1, -1, -1},
                                                {-1,  8, -1},
                                                {-1, -1, -1}}; 
    Y = conv(Y, LaplacianKernel, 3);

    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

void RGBImage::PrewittFilter_H()
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

    vector<vector<double>> PrewittKernel = {    {-1, 0, 1},
                                                {-1, 0, 1},
                                                {-1, 0, 1}}; 
    Y = conv(Y, PrewittKernel, 3);

    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

void RGBImage::PrewittFilter_V()
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

    vector<vector<double>> PrewittKernel = {    { 1,  1,  1},
                                                { 0,  0,  0},
                                                {-1, -1, -1}}; 
    Y = conv(Y, PrewittKernel, 3);

    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

void RGBImage::SobelFilter_H()
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

    vector<vector<double>> SobelKernel = {      {1, 0, -1},
                                                {2, 0, -2},
                                                {1, 0, -1}}; 
    Y = conv(Y, SobelKernel, 3);

    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

void RGBImage::SobelFilter_V()
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);
    
    vector<vector<double>> SobelKernel = {      { 1,  2,  1},
                                                { 0,  0,  0},
                                                {-1, -2, -1}}; 
    Y = conv(Y, SobelKernel, 3);

    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

// ===== Denoise =====
void RGBImage::BoxFilter(int kerSize)
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

    vector<vector<double>> BoxKernel(kerSize, vector<double> (kerSize)); 
    for(int i = 0; i < kerSize; i++)
        for(int j = 0; j < kerSize; j++)
            BoxKernel[i][j] = 1.0 / (kerSize * kerSize);
    //int** tmpY;
    Y = conv(Y, BoxKernel, kerSize);

    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

void RGBImage::GaussianFilter(int kerSize)
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

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

    for(int i = 0; i < kerSize; i++)
    {
        for(int j = 0; j < kerSize; j++)
            cout << GaussianKernel[i][j] <<" ";
        cout << endl;
    }

    //int** tmpY;
    Y = conv(Y, GaussianKernel, kerSize);

    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

void RGBImage::MedianFilter(int kerSize)
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

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
                        tmp.push_back(Y[row][col]);
                }
            }
            sort(tmp.begin(), tmp.end());
            if(tmp.size() % 2 == 1)
                Y[i][j] = tmp[tmp.size() / 2];
            else
                Y[i][j] = (tmp[tmp.size() / 2] + tmp[tmp.size() / 2 + 1]) / 2;
            tmp.clear();
        }
    }

    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

void RGBImage::MosaicFilter(int kerSize)
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

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
                        sum += Y[row][col];
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
                        Y[row][col] = ans;
                }
            }
        }
    }

    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

// ===== Brightness Adjustment =====
void RGBImage::StaticEnhance(double alpha, double beta)
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

    double tmp;
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            tmp = Y[i][j] * alpha + beta;
            if(tmp >= 255.0)
                Y[i][j] = 255;
            else if(tmp <= 0)
                Y[i][j] = 0;
            else
                Y[i][j] = tmp;
        }       
    }
    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

void RGBImage::GammaCorrection(double gamma)
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y [i] = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            Y[i][j] = pow(Y[i][j] / 255.0, gamma) * 255;

    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

void RGBImage::HistogramEqualization()
{
    // Allocate Y, Cr & Cb's memory
    int** Y  = new int* [_h];
    int** Cr = new int* [_h];
    int** Cb = new int* [_h];
    for(int i = 0; i < _h; i++)
    {
        Y[i]  = new int[_w];
        Cr[i] = new int[_w];
        Cb[i] = new int[_w];
    }

    RGB2YCrCb(&Y, &Cr, &Cb);

    // Declare histogram array
    int hist[256] = {0};

    // Count the quantity of 256 levels
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            hist[Y[i][j]]++;

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
    double result;
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            result = 255 * cdf[Y[i][j]];
            if(result >= 255)
                Y[i][j] = 255;
            else if(result <= 0)
                Y[i][j] = 0;
            else
                Y[i][j] = result;
        }
    }

    YCrCb2RGB(Y, Cr, Cb);

    // Free Y, Cr & Cb's memory
    for(int i = 0; i < _h; i++)
    {
        delete[] Y[i];
        delete[] Cr[i];
        delete[] Cb[i];
    }
    delete[] Y;
    delete[] Cr;
    delete[] Cb;
}

// ===== Chromatic Adaptation =====
void RGBImage::MaxRGB()
{
    int maxR = 0;
    int maxG = 0;
    int maxB = 0;

    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            if(pixel[i][j][0] > maxR)
                maxR = pixel[i][j][0];
            if(pixel[i][j][1] > maxG)
                maxG = pixel[i][j][1];
            if(pixel[i][j][2] > maxB)
                maxB = pixel[i][j][2];
        }
    }

    double ratioR = 255.0 / maxR;
    double ratioG = 255.0 / maxG;
    double ratioB = 255.0 / maxB;

    double resultR, resultG, resultB;
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            resultR = pixel[i][j][0] * ratioR;
            if(resultR >= 255)
                pixel[i][j][0] = 255;
            else if(resultR <= 0)
                pixel[i][j][0] = 0;
            else
                pixel[i][j][0] = resultR;

            resultG = pixel[i][j][1] * ratioG;
            if(resultG >= 255)
                pixel[i][j][1] = 255;
            else if(resultG <= 0)
                pixel[i][j][1] = 0;
            else
                pixel[i][j][1] = resultG;

            resultB = pixel[i][j][2] * ratioB;
            if(resultB >= 255)
                pixel[i][j][2] = 255;
            else if(resultB <= 0)
                pixel[i][j][2] = 0;
            else
                pixel[i][j][2] = resultB;
        }
    }
}

void RGBImage::GrayWorld()
{
    long long sumR = 0;
	long long sumG = 0;
	long long sumB = 0;

    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            sumR += pixel[i][j][0];
            sumG += pixel[i][j][1];
            sumB += pixel[i][j][2];
        }
    }

    double meanR, meanG, meanB;
    meanR = sumR * 1.0 / (_h * _w);
    meanG = sumG * 1.0 / (_h * _w);
    meanB = sumB * 1.0 / (_h * _w);

    double ratioR, ratioG, ratioB;
	ratioR = (meanR + meanG + meanB) / (3.0 * meanR);
	ratioG = (meanR + meanG + meanB) / (3.0 * meanG);
	ratioB = (meanR + meanG + meanB) / (3.0 * meanB);

    double resultR, resultG, resultB;
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            resultR = pixel[i][j][0] * ratioR;
            if(resultR >= 255)
                pixel[i][j][0] = 255;
            else if(resultR <= 0)
                pixel[i][j][0] = 0;
            else
                pixel[i][j][0] = resultR;

            resultG = pixel[i][j][1] * ratioG;
            if(resultG >= 255)
                pixel[i][j][1] = 255;
            else if(resultG <= 0)
                pixel[i][j][1] = 0;
            else
                pixel[i][j][1] = resultG;

            resultB = pixel[i][j][2] * ratioB;
            if(resultB >= 255)
                pixel[i][j][2] = 255;
            else if(resultB <= 0)
                pixel[i][j][2] = 0;
            else
                pixel[i][j][2] = resultB;
        }
    }
}
