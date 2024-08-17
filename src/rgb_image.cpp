# include "rgb_image.h"
 
using namespace std;

// ===== Constructor =====
RGBImage::RGBImage(): Image(0, 0)
{
    pixel = NULL;
}

RGBImage::RGBImage(int w, int h): Image(w, h)
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

int*** RGBImage::GetPixel()
{
    return pixel;
}

// ===== Color Space Transformation
void RGBImage::RGB2YCrCb(int*** Y, int*** Cr, int*** Cb)
{
    // Calculate Y, Cr & Cb
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            (*Y) [i][j] = pixel[i][j][0] * 0.299 + pixel[i][j][1] * 0.587 + pixel[i][j][2] * 0.114;
            (*Cr)[i][j] = (pixel[i][j][0] - (*Y) [i][j]) * 0.713 + 128.0;
            (*Cb)[i][j] = (pixel[i][j][2] - (*Y) [i][j]) * 0.564 + 128.0;
        }
    }
}

void RGBImage::RGB2HSI(double*** H, double*** S, double*** I)
{
    int r, g, b, min;
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            r = pixel[i][j][0];
            g = pixel[i][j][1];
            b = pixel[i][j][2];

            min = b;
            if(g < min)
                min = g;
            if(r < min)
                min = r;
            double theta = acos( 0.5 * (r-g+r-b) / sqrt( pow(r-g,2) + (r-b) * (g-b) ) );
            (*I) [i][j] = (r + g + b) / 3.0;
            if((*I) [i][j] == 0)
                (*S) [i][j] = 0;
            else
                (*S) [i][j] = 1.0 - 3.0 * min / (r + g + b);
            (*H) [i][j] = (b <= g) ? theta : 2 * M_PI - theta;              
        }
    }
}

void RGBImage::YCrCb2RGB(int** Y, int** Cr, int** Cb)
{
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            pixel[i][j][0] = min(255, max(0, static_cast<int>(Y[i][j] + 1.403 * (Cr[i][j] - 128))));
            pixel[i][j][1] = min(255, max(0, static_cast<int>(Y[i][j] - 0.714 * (Cr[i][j] - 128) - 0.344 * (Cb[i][j] - 128))));
            pixel[i][j][2] = min(255, max(0, static_cast<int>(Y[i][j] + 1.773 * (Cb[i][j] - 128))));
        }
    }
}

void RGBImage::HSI2RGB(double** H, double** S, double** I)
{
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            double r, g ,b;
            if(0 <= H[i][j] && H[i][j] < 2.0 * M_PI / 3.0)
            {
                b = (1.0 - S[i][j]) * I[i][j];
                r = (1.0 + S[i][j] * cos(H[i][j]) / cos(M_PI / 3.0 - H[i][j]) ) * I[i][j];
                g = 3 * I[i][j] - (r + b);
            }
            else if(2.0 * M_PI / 3.0 <= H[i][j] && H[i][j] < 4.0 * M_PI / 3.0)
            {
                r = (1.0 - S[i][j]) * I[i][j];
                g = (1.0 + S[i][j] * cos(H[i][j] - 2.0 * M_PI / 3.0) / cos(M_PI - H[i][j]) ) * I[i][j];
                b = 3 * I[i][j] - (r + g);
            }
            else if(4.0 * M_PI / 3.0 <= H[i][j] && H[i][j] < 2.0 * M_PI)
            {
                g = (1.0 - S[i][j]) * I[i][j];
                b = (1.0 + S[i][j] * cos(H[i][j] - 4.0 * M_PI / 3.0) / cos(5.0 * M_PI / 3.0 - H[i][j]) ) * I[i][j];
                r = 3 * I[i][j] - (g + b);
            }

            pixel[i][j][0] = min(255, max(0, static_cast<int>(r)));
            pixel[i][j][1] = min(255, max(0, static_cast<int>(g)));
            pixel[i][j][2] = min(255, max(0, static_cast<int>(b)));
        }
    }
}

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
    if(x0 < 0)
        x0 = 0;

	int x1 = ceil(x);
    if(x1 >= _h)
        x1 = _h - 1;

	int y0 = floor(y);
    if(y0 < 0)
        y0 = 0;

	int y1 = ceil(y);
    if(y1 >= _w)
        y1 = _w - 1;

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
                                                {-1,  5, -1},
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
                                                {-1,  9, -1},
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
                                                {-1, 1, 1},
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
                                                { 0,  1,  0},
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
                                                {2, 1, -2},
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
                                                { 0,  1,  0},
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

void RGBImage::EmbossFilter()
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

    vector<vector<double>> EmbossKernel = {     {-2, -1,  0},
                                                {-1,  1,  1},
                                                { 0,  1,  2}}; 
    
    Y = conv(Y, EmbossKernel, 3);

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

void RGBImage::MotionBlur(int kerSize, double theta)
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

    int** tmpPixel = new int* [_h];
    for(int i = 0; i < _h; i++)
        tmpPixel[i] = new int [_w];

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            tmpPixel[i][j] = pixel[i][j][0];

    tmpPixel = conv(tmpPixel, kernel, kerSize);

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j][0] = tmpPixel[i][j];

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            tmpPixel[i][j] = pixel[i][j][1];

    tmpPixel = conv(tmpPixel, kernel, kerSize);

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j][1] = tmpPixel[i][j];

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            tmpPixel[i][j] = pixel[i][j][2];

    tmpPixel = conv(tmpPixel, kernel, kerSize);

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            pixel[i][j][2] = tmpPixel[i][j];

    for(int i = 0; i < _h; i++)
        delete[] tmpPixel[i];
    delete[] tmpPixel;
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

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            Y[i][j] = min(255, max(0, static_cast<int>(Y[i][j] * alpha + beta)));
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
    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            Y[i][j] = min(255, max(0, static_cast<int>(255 * cdf[Y[i][j]])));

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

    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            pixel[i][j][0] = min(255, max(0, static_cast<int>(pixel[i][j][0] * ratioR)));
            pixel[i][j][1] = min(255, max(0, static_cast<int>(pixel[i][j][1] * ratioG)));
            pixel[i][j][2] = min(255, max(0, static_cast<int>(pixel[i][j][2] * ratioB)));
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

    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            pixel[i][j][0] = min(255, max(0, static_cast<int>(pixel[i][j][0] * ratioR)));
            pixel[i][j][1] = min(255, max(0, static_cast<int>(pixel[i][j][1] * ratioG)));
            pixel[i][j][2] = min(255, max(0, static_cast<int>(pixel[i][j][2] * ratioB)));
        }
    }
}

// ===== Special Function =====
void RGBImage::SaturationEnhance(double gamma)
{
    // Allocate H, S & I's memory
    double** H = new double* [_h];
    double** S = new double* [_h];
    double** I = new double* [_h];
    for(int i = 0; i < _h; i++)
    {
        H[i] = new double[_w];
        S[i] = new double[_w];
        I[i] = new double[_w];
    }

    RGB2HSI(&H, &S, &I);

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w ; j++)
            S[i][j] = min(1.0, pow(S[i][j] , gamma));

    HSI2RGB(H,S,I);

    for(int i = 0; i < _h; i++)
    {
        delete[] H[i];
        delete[] S[i];
        delete[] I[i];
    }
    delete[] H;
    delete[] S;
    delete[] I;
}

void RGBImage::EdgeDetection()
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
    
    int** newY = new int* [_h];
    for(int i = 0; i < _h; i++)
        newY[i] = new int[_w];

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            newY[i][j] = Y[i][j];

    vector<vector<double>> SobelKernel_H = {    {1, 0, -1},
                                                {2, 0, -2},
                                                {1, 0, -1}}; 
    newY = conv(newY, SobelKernel_H, 3);

    vector<vector<double>> SobelKernel_V = {    { 1,  2,  1},
                                                { 0,  0,  0},
                                                {-1, -2, -1}}; 
    Y = conv(Y, SobelKernel_V, 3);

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            Y[i][j] = min(255, max(0, static_cast<int>(sqrt(newY[i][j] * newY[i][j] + Y[i][j] * Y[i][j]))));

    for(int i = 0; i < _h; i++)
        delete[] newY[i];
    delete[] newY;

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

void RGBImage::SwirlFilter(double strength)
{
    int*** newPixel = new int** [_h];
    for(int i = 0; i < _h; i++)
    {
        newPixel[i] = new int* [_w];
        for(int j = 0; j < _w; j++)
            newPixel[i][j] = new int[3];
    }

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            for(int k = 0; k < 3; k++)
                newPixel[i][j][k] = pixel[i][j][k];

    int centerY = _h / 2;
    int centerX = _w / 2;
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            int dy = i - centerY;
            int dx = j - centerX;
            double radius = sqrt(dx * dx + dy * dy);
            double angle = atan2(dy, dx) + strength * (sqrt(_h * _h + _w * _w) - radius) / sqrt(_h * _h + _w * _w);
            int newI = static_cast<int>(centerY + radius * sin(angle));
            int newJ = static_cast<int>(centerX + radius * cos(angle));
            if(newI >= 0 && newI < _h && newJ >= 0 && newJ < _w)
            {
                pixel[i][j][0] = newPixel[newI][newJ][0];
                pixel[i][j][1] = newPixel[newI][newJ][1];
                pixel[i][j][2] = newPixel[newI][newJ][2];
            }
        }
    }

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            delete[] newPixel[i][j];
    for(int i = 0; i < _h; i++)
        delete[] newPixel[i];
    delete[] newPixel;
}

void RGBImage::FishEyeFilter()
{
    int*** newPixel = new int** [_h];
    for(int i = 0; i < _h; i++)
    {
        newPixel[i] = new int* [_w];
        for(int j = 0; j < _w; j++)
            newPixel[i][j] = new int[3];
    }

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            for(int k = 0; k < 3; k++)
                newPixel[i][j][k] = pixel[i][j][k];

    int centerY = _h / 2;
    int centerX = _w / 2;
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            int dy = i - centerY;
            int dx = j - centerX;
            double distance = sqrt(dx * dx + dy * dy);
            if(distance > min(centerX, centerY))
            {
                pixel[i][j][0] = 0;
                pixel[i][j][1] = 0;
                pixel[i][j][2] = 0;
                continue;
            }
            double normalizeR = distance / min(centerX, centerY);
            double angle = atan2(dy, dx);
            double radius;
            double strength = 1.0 + 3.0 * normalizeR;
            radius = pow(normalizeR, strength) * min(centerX, centerY);
            int newI = static_cast<int>(centerY + radius * sin(angle));
            int newJ = static_cast<int>(centerX + radius * cos(angle));
            if(newI >= 0 && newI < _h && newJ >= 0 && newJ < _w)
            {
                pixel[i][j][0] = newPixel[newI][newJ][0];
                pixel[i][j][1] = newPixel[newI][newJ][1];
                pixel[i][j][2] = newPixel[newI][newJ][2];
            }
            else
            {
                pixel[i][j][0] = 0;
                pixel[i][j][1] = 0;
                pixel[i][j][2] = 0;
            }
        }
    }

    for(int i = 0; i < _h; i++)
        for(int j = 0; j < _w; j++)
            delete[] newPixel[i][j];
    for(int i = 0; i < _h; i++)
        delete[] newPixel[i];
    delete[] newPixel;
}

// ===== Color Grading =====
void RGBImage::SepiaTone()
{
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            pixel[i][j][0] = min(255, max(0, static_cast<int>(pixel[i][j][0] * 0.393 + pixel[i][j][1] * 0.769 + pixel[i][j][2] * 0.189)));
            pixel[i][j][1] = min(255, max(0, static_cast<int>(pixel[i][j][0] * 0.349 + pixel[i][j][1] * 0.686 + pixel[i][j][2] * 0.168)));
            pixel[i][j][2] = min(255, max(0, static_cast<int>(pixel[i][j][0] * 0.272 + pixel[i][j][1] * 0.534 + pixel[i][j][2] * 0.131)));
        }
    }
}

void RGBImage::CoolTone()
{
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            pixel[i][j][0] = min(255, max(0, static_cast<int>(pixel[i][j][0] * 0.9)));
            pixel[i][j][1] = min(255, max(0, static_cast<int>(pixel[i][j][1] * 1.1)));
            pixel[i][j][2] = min(255, max(0, static_cast<int>(pixel[i][j][2] * 1.2)));
        }
    }
}

void RGBImage::WarmTone()
{
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            pixel[i][j][0] = min(255, max(0, static_cast<int>(pixel[i][j][0] * 1.2)));
            pixel[i][j][1] = min(255, max(0, static_cast<int>(pixel[i][j][1] * 1.1)));
            pixel[i][j][2] = min(255, max(0, static_cast<int>(pixel[i][j][2] * 0.9)));
        }
    }
}

void RGBImage::DuoTone(int mode)
{
    int r1 = 0, g1 = 34, b1 = 102;
    int r2, g2, b2;
    switch(mode)
    {
        case 1:
            // Red Tone
            r2 = 255, g2 = 0, b2 = 0;
            break;
        case 2:
            // Green Tone
            r2 = 0, g2 = 255, b2 = 0;
            break;
        case 3:
            // Blue Tone
            r2 = 0, g2 = 0, b2 = 255;
            break;
        case 4:
            // Yellow Tone
            r2 = 255, g2 = 204, b2 = 0;
            break;
        case 5:
            // Cyan Tone
            r2 = 0, g2 = 255, b2 = 255;
            break;
        case 6:
            // Pink Tone
            r2 = 255, g2 = 192, b2 = 203;
            break;
        case 7:
            // Orange Tone
            r2 = 255, g2 = 77, b2 = 64;
            break;
        case 8:
            // Purple Tone
            r2 = 106, g2 = 13, b2 = 173;
            break;
        default:
            cout << "   !!!!! ERROR MODE !!!!!\n";
            exit(1);
            break;
    }

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

    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            double y = Y[i][j] / 255.0;
            pixel[i][j][0] = min(255, max(0, static_cast<int>(r1 * (1 - y) + r2 * y)));
            pixel[i][j][1] = min(255, max(0, static_cast<int>(g1 * (1 - y) + g2 * y)));
            pixel[i][j][2] = min(255, max(0, static_cast<int>(b1 * (1 - y) + b2 * y)));           
        }
    }
}

void RGBImage::NegativeFilm()
{
    for(int i = 0; i < _h; i++)
    {
        for(int j = 0; j < _w; j++)
        {
            pixel[i][j][0] = 255 - pixel[i][j][0];
            pixel[i][j][1] = 255 - pixel[i][j][1];
            pixel[i][j][2] = 255 - pixel[i][j][2];
        }
    }
}