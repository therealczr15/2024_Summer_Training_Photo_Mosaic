# include "bit_field_filter.h"

# define CASE_SCALING               0b00000000000000000000000000000001
# define CASE_FLIP                  0b00000000000000000000000000000010
# define CASE_QUANTIZATION          0b00000000000000000000000000000100
# define CASE_GAMMACORRECTION       0b00000000000000000000000000001000
# define CASE_STATICENHANCE         0b00000000000000000000000000010000
# define CASE_HISTOGRAMEQUALIZATION 0b00000000000000000000000000100000
# define CASE_MAXRGB                0b00000000000000000000000001000000
# define CASE_GRAYWORLD             0b00000000000000000000000010000000
# define CASE_BOXFILTER             0b00000000000000000000000100000000
# define CASE_GAUSSIANFILTER        0b00000000000000000000001000000000
# define CASE_MEDIANFILTER          0b00000000000000000000010000000000
# define CASE_MOSAICFILTER          0b00000000000000000000100000000000
# define CASE_LAPLACIANFILTER_A     0b00000000000000000001000000000000
# define CASE_LAPLACIANFILTER_B     0b00000000000000000010000000000000
# define CASE_PREWITTFILTER_H       0b00000000000000000100000000000000
# define CASE_PREWITTFILTER_V       0b00000000000000001000000000000000
# define CASE_SOBELFILTER_H         0b00000000000000010000000000000000
# define CASE_SOBELFILTER_V         0b00000000000000100000000000000000

# define CSE_NUM 18

// *** true:  Display Image On Xserver ***
// *** false: Check Memory Leak ***
# define DISPLAY_FLAG true

using namespace std;

// ===== Scaling =====
void Scaling(Image* img, int newH, int newW)
{
    img -> Scaling(newH, newW);
}

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

void MosaicFilter(Image* img, int kernelSize)
{
    img -> MosaicFilter(kernelSize);
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

// ===== Filter Interface =====
void Filter(Image* img)
{
    // Initial menu
    cout << "       ========================================================" << endl;
    cout << "       |         Welcome to use bit-field filter!!!!!         |" << endl;
    cout << "       ========================================================" << endl;
    cout << endl;

    /*cout << "     Please input a file path of the image you want to modify (WARNING: THIS IMAGE MUST BE IN Image-Folder): "
    string filename;
    cin >> filename; 
    img -> LoadImage ("Image-Folder/" + filename);*/

    cout << "       *** Here are some functions you can use on the image ***" << endl;
    cout << "       ========================================================" << endl;
    cout << "       |    1.   Scaling                                      |" << endl;
    cout << "       |    2.   Flip                                         |" << endl;
    cout << "       |    3.   Quantization Resolution                      |" << endl;
    cout << "       |    4.   Gamma Correction                             |" << endl;
    cout << "       |    5.   Brightness Enhancement                       |" << endl;
    cout << "       |    6.   Histogram Equalization                       |" << endl;
    cout << "       |    7.   Max RGB                                      |" << endl;
    cout << "       |    8.   Gray World                                   |" << endl;
    cout << "       |    9.   Box Filter                                   |" << endl;
    cout << "       |   10.   Gaussian Filter                              |" << endl;
    cout << "       |   11.   Median Filter                                |" << endl;
    cout << "       |   12.   Mosaic Filter                                |" << endl;
    cout << "       |   13.   Laplacian Filter A                           |" << endl;
    cout << "       |   14.   Laplacian Filter B                           |" << endl;
    cout << "       |   15.   Prewitt Filter Horizontal                    |" << endl;
    cout << "       |   16.   Prewitt Filter Vertical                      |" << endl;
    cout << "       |   17.   Sobel Filter Horizontal                      |" << endl;
    cout << "       |   18.   Sobel Filter Verical                         |" << endl;
    cout << "       ========================================================" << endl;

    cout << endl;

    // Input option
    string input;

    cout << "       Please input the numbers of the functions you want." << endl;
    cout << "       Notice that the execution order is ascending." << endl;
    cout << endl;

    cout << "       For example 1, input: 2 4 9, which means:" << endl;
    cout << "       Input Image -> Flip -> Gamma Correction -> Box Filter -> Output Image" << endl;
    cout << endl;

    cout << "       For example2, input: 4 9 2, which means:" << endl;
    cout << "       Input Image -> Gamma Correction -> Box Filter -> Flip -> Output Image" << endl;
    cout << endl;

    cout << "       Your Input:" << endl;
    cout << "       ";
    getline(cin, input);

    // Fetch options
    uint32_t options = 0b00000000000000000000000000000000;
    string str, tmp;
    for(char c:input)
    {
        tmp = c;
        if(c == ' ' || c == '\"')
        {
            LoadOptions(options, stoi(str));
            str.clear();
        }
        else
            str = str + tmp;
    }
    if(!str.empty())
    {
        LoadOptions(options, stoi(str));
        str.clear();
    }

    //// check options
    //bitset<16> bs(options);
    //cout << bs << endl;

    // Running options 
    RunOptions(img, options);

    // End filter
    cout << "       End filter" << endl;
}

void LoadOptions(uint32_t &options, int case_n)
{
    switch(case_n)
    {
        case 1:
            options = options | CASE_SCALING;
            break;
        case 2:
            options = options | CASE_FLIP;
            break;
        case 3:
            options = options | CASE_QUANTIZATION;
            break;
        case 4:
            options = options | CASE_GAMMACORRECTION;
            break;
        case 5:
            options = options | CASE_STATICENHANCE;
            break;
        case 6:
            options = options | CASE_HISTOGRAMEQUALIZATION;
            break;
        case 7:
            options = options | CASE_MAXRGB;
            break;
        case 8:
            options = options | CASE_GRAYWORLD;
            break;
        case 9:
            options = options | CASE_BOXFILTER;
            break;
        case 10:
            options = options | CASE_GAUSSIANFILTER;
            break;  
        case 11:
            options = options | CASE_MEDIANFILTER;
            break;
        case 12:
            options = options | CASE_MOSAICFILTER;
            break;
        case 13:
            options = options | CASE_LAPLACIANFILTER_A;
            break;
        case 14:
            options = options | CASE_LAPLACIANFILTER_B;
            break;
        case 15:
            options = options | CASE_PREWITTFILTER_H;
            break; 
        case 16:
            options = options | CASE_PREWITTFILTER_V;
            break;
        case 17:
            options = options | CASE_SOBELFILTER_H;
            break; 
        case 18:
            options = options | CASE_SOBELFILTER_V;
            break; 
        
        default:
            cout << "       Case " << case_n << "is an invalid input!" << endl;
            exit(1);  
    }
}

void RunOptions(Image* img, uint32_t options)
{
    int tmp_int, tmp_int2;
    double tmp_dbl1, tmp_dbl2;
    char tmp_c;

    // check origin image
    if(DISPLAY_FLAG)
    {
        cout << "       Do you want to see the origin image (y/n)? ";
        cin >> tmp_c;
        if(tmp_c == 'y'  || tmp_c == 'Y') img -> Display_X_Server();
    }

    cout << endl << endl;

    // ===== Scaling =====
    if(options & CASE_SCALING)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                       Scaling                        |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input the new image size you want (height, width): ";
        cin >> tmp_int >> tmp_int2;
        Scaling(img, tmp_int, tmp_int2);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Flip =====
    if(options & CASE_FLIP)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                         Flip                         |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        Flip(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Quantization =====
    if(options & CASE_QUANTIZATION)
    {
        cout << "       ========================================================" << endl;
        cout << "       |               Quantization Resolution                |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input how many bits you want to quantize (ex. input 4, then original 8 bits image will turn into 4 bits image): ";
        cin >> tmp_int;
        Quantization(img, tmp_int);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== GammaCorrection =====
    if(options & CASE_GAMMACORRECTION)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                   Gamma Correction                   |" << endl;
        cout << "       ========================================================" << endl;

        cout << endl;
        cout << "       Please input gamma (0 ~ 1 to enhance brightness, > 1 to reduce brightness): ";
        cin >> tmp_dbl1;
        GammaCorrection(img, tmp_dbl1);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== StaticEnhance =====
    if(options & CASE_STATICENHANCE)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                  Brightness Enhance                  |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input alpha, beta (new brightness = old brightness x alpha + beta): ";
        cin >> tmp_dbl1 >> tmp_dbl2;
        StaticEnhance(img, tmp_dbl1, tmp_dbl2);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== HistogramEqualization =====
    if(options & CASE_HISTOGRAMEQUALIZATION)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                Histogram Equalization                |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        HistogramEqualization(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== MaxRGB =====
    if(options & CASE_MAXRGB)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                       Max RGB                        |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        MaxRGB(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== GrayWorld =====
    if(options & CASE_GRAYWORLD)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                      Gray World                      |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        GrayWorld(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== BoxFilter =====
    if(options & CASE_BOXFILTER)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                      Box Filter                      |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input kernal size: ";
        cin >> tmp_int;
        BoxFilter(img, tmp_int);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== GaussianFilter =====
    if(options & CASE_GAUSSIANFILTER)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                   Gaussian Filter                    |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input kernal size: ";
        cin >> tmp_int;
        BoxFilter(img, tmp_int);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== MedianFilter =====
    if(options & CASE_MEDIANFILTER)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                    Median Filter                     |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input kernal size: ";
        cin >> tmp_int;
        MedianFilter(img, tmp_int);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Mosaic Filter
    if(options & CASE_MOSAICFILTER)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                    Mosaic Filter                     |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        
        cout << "       Please input kernal size: ";
        cin >> tmp_int;
        MosaicFilter(img, tmp_int);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== LaplacianFilter_A =====
    if(options & CASE_LAPLACIANFILTER_A)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                  Laplacian Filter A                  |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        LaplacianFilter_A(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== LaplacianFilter_B =====
    if(options & CASE_LAPLACIANFILTER_B)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                  Laplacian Filter B                  |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        LaplacianFilter_B(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== PrewittFilter_H =====
    if(options & CASE_PREWITTFILTER_H)
    {
        cout << "       ========================================================" << endl;
        cout << "       |              Prewitt Filter Horizontal               |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        PrewittFilter_H(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== PrewittFilter_V =====
    if(options & CASE_PREWITTFILTER_V)
    {
        cout << "       ========================================================" << endl;
        cout << "       |               Prewitt Filter Vertical                |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        PrewittFilter_V(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== SobelFilter_H =====
    if(options & CASE_SOBELFILTER_H)
    {
        cout << "       ========================================================" << endl;
        cout << "       |               Sobel Filter Horizontal                |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        SobelFilter_H(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== SobelFilter_V =====
    if(options & CASE_SOBELFILTER_V)
    {
        cout << "       ========================================================" << endl;
        cout << "       |                Sobel Filter Vertical                 |" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        SobelFilter_V(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }
}