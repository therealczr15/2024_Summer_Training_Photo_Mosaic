# include "bit_field_filter.h"

# define CASE_SCALING               0b00000000000000000000000000000001
# define CASE_FLIP                  0b00000000000000000000000000000010
# define CASE_QUANTIZATION          0b00000000000000000000000000000100
# define CASE_GAMMACORRECTION       0b00000000000000000000000000001000
# define CASE_STATICENHANCE         0b00000000000000000000000000010000
# define CASE_HISTOGRAMEQUALIZATION 0b00000000000000000000000000100000
# define CASE_SEPIATONE             0b00000000000000000000000001000000    
# define CASE_COOLTONE              0b00000000000000000000000010000000
# define CASE_WARMTONE              0b00000000000000000000000100000000
# define CASE_DUOTONE               0b00000000000000000000001000000000
# define CASE_NEGATIVEFILM          0b00000000000000000000010000000000    
# define CASE_MAXRGB                0b00000000000000000000100000000000      
# define CASE_GRAYWORLD             0b00000000000000000001000000000000     
# define CASE_BOXFILTER             0b00000000000000000010000000000000 
# define CASE_GAUSSIANFILTER        0b00000000000000000100000000000000
# define CASE_MEDIANFILTER          0b00000000000000001000000000000000
# define CASE_MOSAICFILTER          0b00000000000000010000000000000000
# define CASE_MOTIONBLUR            0b00000000000000100000000000000000
# define CASE_LAPLACIANFILTER_A     0b00000000000001000000000000000000
# define CASE_LAPLACIANFILTER_B     0b00000000000010000000000000000000
# define CASE_PREWITTFILTER_H       0b00000000000100000000000000000000
# define CASE_PREWITTFILTER_V       0b00000000001000000000000000000000
# define CASE_SOBELFILTER_H         0b00000000010000000000000000000000
# define CASE_SOBELFILTER_V         0b00000000100000000000000000000000
# define CASE_EMBOSSFILTER          0b00000001000000000000000000000000
# define CASE_SATURATIONENHANCE     0b00000010000000000000000000000000
# define CASE_EDGEDETECTION         0b00000100000000000000000000000000
# define CASE_SWIRLFILTER           0b00001000000000000000000000000000
# define CASE_FISHEYEFILTER         0b00010000000000000000000000000000

# define CSE_NUM 30

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

void EmbossFilter(Image *img)
{
    img -> EmbossFilter();
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

void MotionBlur(Image* img, int kernelSize, double theta)
{
    img -> MotionBlur(kernelSize, theta);
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

// ===== Special Function =====
void SaturationEnhance(Image* img, double gamma)
{
    img -> SaturationEnhance(gamma);
}

void EdgeDetection(Image* img)
{
    img -> EdgeDetection();
}

void SwirlFilter(Image* img, double strength)
{
    img -> SwirlFilter(strength);
}

void FishEyeFilter(Image* img)
{
    img -> FishEyeFilter();
}

// ===== Color Grading =====
void SepiaTone(Image* img)
{
    img -> SepiaTone();
}

void CoolTone(Image* img)
{
    img -> CoolTone();
}

void WarmTone(Image* img)
{
    img -> WarmTone();
}

void NegativeFilm(Image* img)
{
    img -> NegativeFilm();
}

void DuoTone(Image* img, int mode)
{
    img -> DuoTone(mode);
}

// ===== Filter Interface =====
void Filter(Image* img)
{
    // Initial menu
    cout << endl << endl;
    cout << "       ========================================================" << endl;
    cout << "       |\033[47m\033[30m       Let's start to use bit-field filter!!!!!       \033[m|" << endl;
    cout << "       ========================================================" << endl;
    cout << endl;

    cout << "       *** Here are some functions you can use on the image ***" << endl;
    cout << "       ========================================================" << endl;
    cout << "       |\033[41m                                                      \033[m|" << endl;
    cout << "       |\033[41m                    Basic Function                    \033[m|" << endl;
    cout << "       |\033[41m                                                      \033[m|" << endl;
    cout << "       |\033[31m       1.   Scaling                                   \033[m|" << endl;
    cout << "       |\033[31m       2.   Flip                                      \033[m|" << endl;
    cout << "       |\033[31m       3.   Quantization Resolution                   \033[m|" << endl;
    cout << "       |\033[42m                                                      \033[m|" << endl;
    cout << "       |\033[42m                 Contrast Enhancement                 \033[m|" << endl;
    cout << "       |\033[42m                                                      \033[m|" << endl;
    cout << "       |\033[32m       4.   Gamma Correction                          \033[m|" << endl;
    cout << "       |\033[32m       5.   Brightment Adjustment                     \033[m|" << endl;
    cout << "       |\033[32m       6.   Histogram Equalization                    \033[m|" << endl;
    cout << "       |\033[43m                                                      \033[m|" << endl;
    cout << "       |\033[43m                    Color Grading                     \033[m|" << endl;
    cout << "       |\033[43m                                                      \033[m|" << endl;
    cout << "       |\033[33m       7.   Sepia Tone                                \033[m|" << endl;
    cout << "       |\033[33m       8.   Cool Tone                                 \033[m|" << endl;
    cout << "       |\033[33m       9.   Warm Tone                                 \033[m|" << endl;
    cout << "       |\033[33m      10.   Duo Tone                                  \033[m|" << endl;
    cout << "       |\033[33m      11.   Negative Film                             \033[m|" << endl;
    cout << "       |\033[44m                                                      \033[m|" << endl;
    cout << "       |\033[44m                 Chromatic Adaptation                 \033[m|" << endl;
    cout << "       |\033[44m                                                      \033[m|" << endl;
    cout << "       |\033[34m      12.   Max RGB                                   \033[m|" << endl;
    cout << "       |\033[34m      13.   Gray World                                \033[m|" << endl;
    cout << "       |\033[45m                                                      \033[m|" << endl;
    cout << "       |\033[45m                       Denoise                        \033[m|" << endl;
    cout << "       |\033[45m                                                      \033[m|" << endl;
    cout << "       |\033[35m      14.   Box Filter                                \033[m|" << endl;
    cout << "       |\033[35m      15.   Gaussian Filter                           \033[m|" << endl;
    cout << "       |\033[35m      16.   Median Filter                             \033[m|" << endl;
    cout << "       |\033[35m      17.   Mosaic Filter                             \033[m|" << endl;
    cout << "       |\033[35m      18.   Motion Blur                               \033[m|" << endl;
    cout << "       |\033[46m                                                      \033[m|" << endl;
    cout << "       |\033[46m                Sharpness Enhancement                 \033[m|" << endl;
    cout << "       |\033[46m                                                      \033[m|" << endl;
    cout << "       |\033[36m      19.   Laplacian Filter A                        \033[m|" << endl;
    cout << "       |\033[36m      20.   Laplacian Filter B                        \033[m|" << endl;
    cout << "       |\033[36m      21.   Prewitt Filter Horizontal                 \033[m|" << endl;
    cout << "       |\033[36m      22.   Prewitt Filter Vertical                   \033[m|" << endl;
    cout << "       |\033[36m      23.   Sobel Filter Horizontal                   \033[m|" << endl;
    cout << "       |\033[36m      24.   Sobel Filter Verical                      \033[m|" << endl;
    cout << "       |\033[36m      25.   Emboss Filter                             \033[m|" << endl;
    cout << "       |\033[47m\033[30m                                                      \033[m|" << endl;
    cout << "       |\033[47m\033[30m                   Special Function                   \033[m|" << endl;
    cout << "       |\033[47m\033[30m                                                      \033[m|" << endl;
    cout << "       |\033[37m      26.   Saturation Enhance                        \033[m|" << endl;
    cout << "       |\033[37m      27.   Edge Detection                            \033[m|" << endl;
    cout << "       |\033[37m      28.   Swirl Filter                              \033[m|" << endl;
    cout << "       |\033[37m      29.   Fish Eye Filter                           \033[m|" << endl;
    cout << "       ========================================================" << endl << endl;

    cout << "       Please input a file path of the image you want to modify \033[31m(WARNING: THIS IMAGE MUST BE IN Image-Folder)\033[m: ";
    string filename;
    cin >> filename; 
    filename = "Image-Folder/" + filename;
    img -> LoadImage (filename);


    // Input option
    string input;

    cout << endl;
    cout << "       Please input the numbers of the functions you want." << endl;
    cout << "       \033[31mNotice that the execution order is ascending.\033[m" << endl;
    cout << endl;

    cout << "       \033[34mFor example 1, input: 2 4 14, which means:\033[m" << endl;
    cout << "       \033[32mInput Image -> Flip -> Gamma Correction -> Box Filter -> Output Image\033[m" << endl;
    cout << endl;

    cout << "       \033[34mFor example 2, input: 4 14 2, which means:\033[m" << endl;
    cout << "       \033[32mInput Image -> Gamma Correction -> Box Filter -> Flip -> Output Image\033[m" << endl;
    cout << endl;

    cout << "       Your Input: " << endl;
    cout << "       ";
    cin.ignore();
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
    cout << "       \033[1;33m\033[5mEnd bit-field filter  (The image you modified has been dumped in 'Result' folder)\033[m" << endl << endl;
    cout << "       Let's make a Photo Mosaic." << endl;
    cout << "       Continue [y/n]? ";
    char tmp_c;
    cin >> tmp_c;
    if(tmp_c != 'y'  && tmp_c != 'Y') exit(1);

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
            options = options | CASE_SEPIATONE;
            break;
        case 8:
            options = options | CASE_COOLTONE;
            break;
        case 9:
            options = options | CASE_WARMTONE;
            break;
        case 10:
            options = options | CASE_DUOTONE;
            break;
        case 11:
            options = options | CASE_NEGATIVEFILM;
            break;
        case 12:
            options = options | CASE_MAXRGB;
            break;
        case 13:
            options = options | CASE_GRAYWORLD;
            break;
        case 14:
            options = options | CASE_BOXFILTER;
            break;
        case 15:
            options = options | CASE_GAUSSIANFILTER;
            break;  
        case 16:
            options = options | CASE_MEDIANFILTER;
            break;
        case 17:
            options = options | CASE_MOSAICFILTER;
            break;
        case 18:
            options = options | CASE_MOTIONBLUR;
            break;
        case 19:
            options = options | CASE_LAPLACIANFILTER_A;
            break;
        case 20:
            options = options | CASE_LAPLACIANFILTER_B;
            break;
        case 21:
            options = options | CASE_PREWITTFILTER_H;
            break; 
        case 22:
            options = options | CASE_PREWITTFILTER_V;
            break;
        case 23:
            options = options | CASE_SOBELFILTER_H;
            break; 
        case 24:
            options = options | CASE_SOBELFILTER_V;
            break; 
        case 25:
            options = options | CASE_EMBOSSFILTER;
            break;         
        case 26:
            options = options | CASE_SATURATIONENHANCE;
            break;
        case 27:
            options = options | CASE_EDGEDETECTION;
            break;
        case 28:
            options = options | CASE_SWIRLFILTER;
            break;
        case 29:
            options = options | CASE_FISHEYEFILTER;
            break;
        default:
            cout << "       \033[31mCase " << case_n << " is an invalid input!\033[m" << endl;
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
        cout << "       Do you want to see the origin image [y/n]? ";
        cin >> tmp_c;
        if(tmp_c == 'y'  || tmp_c == 'Y') img -> Display_X_Server();
    }

    cout << endl << endl;

    // ===== Scaling =====
    if(options & CASE_SCALING)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                       Scaling                        \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input the new image size you want (height, width): ";
        cin >> tmp_int >> tmp_int2;
        Scaling(img, tmp_int, tmp_int2);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Flip =====
    if(options & CASE_FLIP)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                         Flip                         \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        Flip(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Quantization =====
    if(options & CASE_QUANTIZATION)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m               Quantization Resolution                \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input how many bits you want to quantize (ex. input 4, then original 8 bits image will turn into 4 bits image): ";
        cin >> tmp_int;
        Quantization(img, tmp_int);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== GammaCorrection =====
    if(options & CASE_GAMMACORRECTION)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                   Gamma Correction                   \033[m|" << endl;
        cout << "       ========================================================" << endl;

        cout << endl;
        cout << "       Please input gamma (0 ~ 1 to enhance brightness, > 1 to reduce brightness): ";
        cin >> tmp_dbl1;
        GammaCorrection(img, tmp_dbl1);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== StaticEnhance =====
    if(options & CASE_STATICENHANCE)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                  Brightness Enhance                  \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input alpha, beta (new brightness = old brightness x alpha + beta): ";
        cin >> tmp_dbl1 >> tmp_dbl2;
        StaticEnhance(img, tmp_dbl1, tmp_dbl2);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== HistogramEqualization =====
    if(options & CASE_HISTOGRAMEQUALIZATION)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                Histogram Equalization                \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        HistogramEqualization(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== SepiaTone =====
    if(options & CASE_SEPIATONE)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                      Sepia Tone                      \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        SepiaTone(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== CoolTone =====
    if(options & CASE_COOLTONE)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                      Cool Tone                       \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        CoolTone(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== WarmTone =====
    if(options & CASE_WARMTONE)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                      Warm Tone                       \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        WarmTone(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== DuoTone =====
    if(options & CASE_DUOTONE)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                       Duo Tone                       \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       \033[31m1. Red Tone\033[m\n";
        cout << "       \033[32m2. Green Tone\033[m\n";
        cout << "       \033[34m3. Blue Tone\033[m\n";
        cout << "       \033[1;33m4. Yellow Tone\033[m\n";
        cout << "       \033[36m5. Cyan Tone\033[m\n";
        cout << "       \033[1;31m6. Pink Tone\033[m\n";
        cout << "       \033[0;33m7. Orange Tone\033[m\n";
        cout << "       \033[35m8. Purple Tone\033[m\n";
        cout << endl;

        cout << "       Please input tone mode: ";
        cin >> tmp_int;

        DuoTone(img, tmp_int);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Negative Film =====
    if(options & CASE_NEGATIVEFILM)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                    Negative Film                     \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        NegativeFilm(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== MaxRGB =====
    if(options & CASE_MAXRGB)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                       Max RGB                        \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        MaxRGB(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== GrayWorld =====
    if(options & CASE_GRAYWORLD)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                      Gray World                      \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        GrayWorld(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== BoxFilter =====
    if(options & CASE_BOXFILTER)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                      Box Filter                      \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input kernal size: ";
        cin >> tmp_int;
        BoxFilter(img, tmp_int);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== GaussianFilter =====
    if(options & CASE_GAUSSIANFILTER)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                   Gaussian Filter                    \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input kernal size: ";
        cin >> tmp_int;
        GaussianFilter(img, tmp_int);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== MedianFilter =====
    if(options & CASE_MEDIANFILTER)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                    Median Filter                     \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input kernal size: ";
        cin >> tmp_int;
        MedianFilter(img, tmp_int);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Mosaic Filter
    if(options & CASE_MOSAICFILTER)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                    Mosaic Filter                     \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        
        cout << "       Please input kernal size: ";
        cin >> tmp_int;
        MosaicFilter(img, tmp_int);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Motion Blur
    if(options & CASE_MOTIONBLUR)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                     Motion Blur                      \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        
        cout << "       Please input kernal size, theta: ";
        cin >> tmp_int >> tmp_dbl1;
        MotionBlur(img, tmp_int, tmp_dbl1);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== LaplacianFilter_A =====
    if(options & CASE_LAPLACIANFILTER_A)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                  Laplacian Filter A                  \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        LaplacianFilter_A(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== LaplacianFilter_B =====
    if(options & CASE_LAPLACIANFILTER_B)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                  Laplacian Filter B                  \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        LaplacianFilter_B(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== PrewittFilter_H =====
    if(options & CASE_PREWITTFILTER_H)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m              Prewitt Filter Horizontal               \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        PrewittFilter_H(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== PrewittFilter_V =====
    if(options & CASE_PREWITTFILTER_V)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m               Prewitt Filter Vertical                \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        PrewittFilter_V(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== SobelFilter_H =====
    if(options & CASE_SOBELFILTER_H)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m               Sobel Filter Horizontal                \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        SobelFilter_H(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== SobelFilter_V =====
    if(options & CASE_SOBELFILTER_V)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                Sobel Filter Vertical                 \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        SobelFilter_V(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

     // ===== Emboss Filter =====
    if(options & CASE_EMBOSSFILTER)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                    Emboss Filter                     \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;

        EmbossFilter(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Saturation Enhance =====
    if(options & CASE_SATURATIONENHANCE)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                  Saturation Enhance                  \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input gamma (0 ~ 1 to enhance saturation, > 1 to reduce saturation): ";
        cin >> tmp_dbl1;
        SaturationEnhance(img, tmp_dbl1);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Edge Detection =====
    if(options & CASE_EDGEDETECTION)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                    Edge Detection                    \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        EdgeDetection(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Swirl Filter =====
    if(options & CASE_SWIRLFILTER)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                     Swirl Filter                     \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        cout << "       Please input strength (The larger the strength, the more pronounced the swirl effect.): ";
        cin >> tmp_dbl1;
        SwirlFilter(img, tmp_dbl1);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Fish Eye Filter =====
    if(options & CASE_FISHEYEFILTER)
    {
        cout << "       ========================================================" << endl;
        cout << "       |\033[47m\033[30m                   Fish Eye Filter                    \033[m|" << endl;
        cout << "       ========================================================" << endl;
        cout << endl;
        FishEyeFilter(img);

        if(DISPLAY_FLAG)
        {
            cout << "       Do you want to see the result [y/n]? ";
            cin >> tmp_c;
            if(tmp_c == 'y' || tmp_c == 'Y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

}

// ===== Introduction =====
void Introduction(){
    // Initial menu
    cout << endl << endl;
    cout << "       ========================================================" << endl;
    cout << "       |\033[47m\033[30m          Bit-field filter introduction!!!!!          \033[m|" << endl;
    cout << "       ========================================================" << endl;
    cout << endl;

    cout << "       *** Here are some functions you can use on the image ***" << endl;
    cout << "       ========================================================" << endl;
    cout << "       |\033[41m                                                      \033[m|" << endl;
    cout << "       |\033[41m                    Basic Function                    \033[m|" << endl;
    cout << "       |\033[41m                                                      \033[m|" << endl;
    cout << "       |\033[31m       1.   Scaling                                   \033[m|" << endl;
    cout << "       |\033[31m       2.   Flip                                      \033[m|" << endl;
    cout << "       |\033[31m       3.   Quantization Resolution                   \033[m|" << endl;
    cout << "       |\033[42m                                                      \033[m|" << endl;
    cout << "       |\033[42m                 Contrast Enhancement                 \033[m|" << endl;
    cout << "       |\033[42m                                                      \033[m|" << endl;
    cout << "       |\033[32m       4.   Gamma Correction                          \033[m|" << endl;
    cout << "       |\033[32m       5.   Brightment Adjustment                     \033[m|" << endl;
    cout << "       |\033[32m       6.   Histogram Equalization                    \033[m|" << endl;
    cout << "       |\033[43m                                                      \033[m|" << endl;
    cout << "       |\033[43m                    Color Grading                     \033[m|" << endl;
    cout << "       |\033[43m                                                      \033[m|" << endl;
    cout << "       |\033[33m       7.   Sepia Tone                                \033[m|" << endl;
    cout << "       |\033[33m       8.   Cool Tone                                 \033[m|" << endl;
    cout << "       |\033[33m       9.   Warm Tone                                 \033[m|" << endl;
    cout << "       |\033[33m      10.   Duo Tone                                  \033[m|" << endl;
    cout << "       |\033[33m      11.   Negative Film                             \033[m|" << endl;
    cout << "       |\033[44m                                                      \033[m|" << endl;
    cout << "       |\033[44m                 Chromatic Adaptation                 \033[m|" << endl;
    cout << "       |\033[44m                                                      \033[m|" << endl;
    cout << "       |\033[34m      12.   Max RGB                                   \033[m|" << endl;
    cout << "       |\033[34m      13.   Gray World                                \033[m|" << endl;
    cout << "       |\033[45m                                                      \033[m|" << endl;
    cout << "       |\033[45m                       Denoise                        \033[m|" << endl;
    cout << "       |\033[45m                                                      \033[m|" << endl;
    cout << "       |\033[35m      14.   Box Filter                                \033[m|" << endl;
    cout << "       |\033[35m      15.   Gaussian Filter                           \033[m|" << endl;
    cout << "       |\033[35m      16.   Median Filter                             \033[m|" << endl;
    cout << "       |\033[35m      17.   Mosaic Filter                             \033[m|" << endl;
    cout << "       |\033[35m      18.   Motion Blur                               \033[m|" << endl;
    cout << "       |\033[46m                                                      \033[m|" << endl;
    cout << "       |\033[46m                Sharpness Enhancement                 \033[m|" << endl;
    cout << "       |\033[46m                                                      \033[m|" << endl;
    cout << "       |\033[36m      19.   Laplacian Filter A                        \033[m|" << endl;
    cout << "       |\033[36m      20.   Laplacian Filter B                        \033[m|" << endl;
    cout << "       |\033[36m      21.   Prewitt Filter Horizontal                 \033[m|" << endl;
    cout << "       |\033[36m      22.   Prewitt Filter Vertical                   \033[m|" << endl;
    cout << "       |\033[36m      23.   Sobel Filter Horizontal                   \033[m|" << endl;
    cout << "       |\033[36m      24.   Sobel Filter Verical                      \033[m|" << endl;
    cout << "       |\033[36m      25.   Emboss Filter                             \033[m|" << endl;
    cout << "       |\033[47m\033[30m                                                      \033[m|" << endl;
    cout << "       |\033[47m\033[30m                   Special Function                   \033[m|" << endl;
    cout << "       |\033[47m\033[30m                                                      \033[m|" << endl;
    cout << "       |\033[37m      26.   Saturation Enhance                        \033[m|" << endl;
    cout << "       |\033[37m      27.   Edge Detection                            \033[m|" << endl;
    cout << "       |\033[37m      28.   Swirl Filter                              \033[m|" << endl;
    cout << "       |\033[37m      29.   Fish Eye Filter                           \033[m|" << endl;
    cout << "       ========================================================" << endl << endl;


    cout << endl;

    // Show example 1
    cout << "       \033[47m\033[30m***** 1. Scaling *****\033[m" << endl << endl;
    Image *img = new RGBImage();
    img -> LoadImage("Image-Folder/lena.jpg");

    cout << "       \033[1;34mBefore (225 x 225)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    Scaling(img, 300, 300);

    cout << "       \033[1;32mAfter (300 x 300)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/Scaling.jpg");

    cout << endl;

    // Show example 2
    cout << "       \033[47m\033[30m***** 2. Flip *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/cat.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    Flip(img);

    cout << "       \033[1;32mAfter (Flip Horizontally)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/Flip.jpg");

    cout << endl;

    // Show example 3
    int quan = 4;
    cout << "       \033[47m\033[30m***** 3. Quantization Resolution *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/cat.jpg");

    cout << "       \033[1;34mBefore (8bits)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    Quantization(img, quan);

    cout << "       \033[1;32mAfter (" << 8 - quan << "bits)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/Quantization.jpg");

    cout << endl;

    // Show example 4
    cout << "       \033[47m\033[30m***** 4. Gamma Correction *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/dark.jpg");

    cout << "       \033[1;34mBefore (Darker)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    GammaCorrection(img, 0.6);

    cout << "       \033[1;32mAfter (Brighter, Gamma = 0.6)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/GammaCorrection.jpg");

    cout << endl;

    // Show example 5
    cout << "       \033[47m\033[30m***** 5. Brightness Enhancement *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/dark.jpg");

    cout << "       \033[1;34mBefore (Darker)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    StaticEnhance(img, 1.3, 20);

    cout << "       \033[1;32mAfter (Brighter, Alpha = 1.3, Beta = 20, new image brightness = old image brightness x 1.3 + 20)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/StaticEnhance.jpg");

    cout << endl;

    // Show example 6
    cout << "       \033[47m\033[30m***** 6. Histogram Equalization *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/lena.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    HistogramEqualization(img);

    cout << "       \033[1;32mAfter (Contrast Enhance)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/HistogramEqualization.jpg");

    cout << endl;

    // Show example 7
    cout << "       \033[47m\033[30m***** 7. Sepia Tone *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/lena.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    SepiaTone(img);

    cout << "       \033[1;32mAfter (Sepia Tone)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/SepiaTone.jpg");

    cout << endl;

    // Show example 8
    cout << "       \033[47m\033[30m***** 8. Cool Tone *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/lena.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    CoolTone(img);

    cout << "       \033[1;32mAfter (Cool Tone)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/CoolTone.jpg");

    cout << endl;

    // Show example 9
    cout << "       \033[47m\033[30m***** 9. Warm Tone *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/lena.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    WarmTone(img);

    cout << "       \033[1;32mAfter (Warm Tone)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/WarmTone.jpg");

    cout << endl;

    // Show example 10
    cout << "       \033[47m\033[30m***** 10. Duo Tone *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/lena.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    DuoTone(img, 4);

    cout << "       \033[1;32mAfter (Yellow Tone)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/DuoTone.jpg");

    cout << endl;


    // Show example 11
    cout << "       \033[47m\033[30m***** 11. Negative Film *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/cat.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    NegativeFilm(img);

    cout << "       \033[1;32mAfter (Negative Film)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/NegativeFilm.jpg");

    cout << endl;

    // Show example 12
    cout << "       \033[47m\033[30m***** 12. Max RGB *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/sea.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    MaxRGB(img);

    cout << "       \033[1;32mAfter (White Balance)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/MaxRGB.jpg");

    cout << endl;

    // Show example 13
    cout << "       \033[47m\033[30m***** 13. Gray World *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/handsomeman.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    GrayWorld(img);

    cout << "       \033[1;32mAfter (White Balance)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/GrayWorld.jpg");

    cout << endl;

    // Show example 14
    cout << "       \033[47m\033[30m***** 14. Box Filter *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/peppersaltnoise.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    BoxFilter(img, 7);

    cout << "       \033[1;32mAfter (Denoise, Kernel size = 7)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/BoxFilter.jpg");

    cout << endl;

    // Show example 15
    cout << "       \033[47m\033[30m***** 15. Gaussian Filter *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/peppersaltnoise.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    GaussianFilter(img, 7);

    cout << "       \033[1;32mAfter (Denoise, Kernel size = 7)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/GaussianFilter.jpg");

    cout << endl;

    // Show example 16
    cout << "       \033[47m\033[30m***** 16. Median Filter *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/peppersaltnoise.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    MedianFilter(img, 3);

    cout << "       \033[1;32mAfter (Denoise, Kernel size = 3)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/MedianFilter.jpg");

    cout << endl;

    // Show example 17
    cout << "       \033[47m\033[30m***** 17. Mosaic Filter *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/nakedlena.jpg");

    cout << "       \033[1;34mBefore (Naked Lena)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    MosaicFilter(img, 7);

    cout << "       \033[1;32mAfter (Mosaic Naked Lena, Kernel size = 7)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/MosaicFilter.jpg");

    cout << endl;

    // Show example 18
    cout << "       \033[47m\033[30m***** 18. Motion Blur *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/cat.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    MotionBlur(img, 15, 30);

    cout << "       \033[1;32mAfter (Linear Motion Blur, Theta = 30°)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/MotionBlur.jpg");

    cout << endl;

    // Show example 19
    cout << "       \033[47m\033[30m***** 19. Laplacian Filter A *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/cat.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    LaplacianFilter_A(img);

    cout << "       \033[1;32mAfter (Sharpness Enhancement)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/LaplacianFilter_A.jpg");

    cout << endl;

    // Show example 20
    cout << "       \033[47m\033[30m***** 20. Laplacian Filter B *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/cat.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    LaplacianFilter_B(img);

    cout << "       \033[1;32mAfter (Sharpness Enhancement)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/LaplacianFilter_B.jpg");

    cout << endl;

    // Show example 21
    cout << "       \033[47m\033[30m***** 21. Prewitt Filter Horizontal *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/cat.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    PrewittFilter_H(img);

    cout << "       \033[1;32mAfter (Sharpness Enhancement)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/PrewittFilter_H.jpg");

    cout << endl;

    // Show example 22
    cout << "       \033[47m\033[30m***** 22. Prewitt Filter Vertical *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/cat.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    PrewittFilter_V(img);

    cout << "       \033[1;32mAfter (Sharpness Enhancement)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/PrewittFilter_V.jpg");

    cout << endl;

    // Show example 23
    cout << "       \033[47m\033[30m***** 23. Sobel Filter Horizontal *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/cat.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    SobelFilter_H(img);

    cout << "       \033[1;32mAfter (Sharpness Enhancement)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/SobelFilter_H.jpg");

    cout << endl;

    // Show example 24
    cout << "       \033[47m\033[30m***** 24. Sobel Filter Verical *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/cat.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    SobelFilter_V(img);

    cout << "       \033[1;32mAfter (Sharpness Enhancement)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/SobelFilter_V.jpg");

    cout << endl;

    // Show example 25
    cout << "       \033[47m\033[30m***** 25. Emboss Filter *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/cat.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    EmbossFilter(img);

    cout << "       \033[1;32mAfter (Sharpness Enhancement)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/EmbossFilter.jpg");

    cout << endl;

    // Show example 26
    cout << "       \033[47m\033[30m***** 26. Saturation Enhance *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/lena.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    SaturationEnhance(img, 0.7);

    cout << "       \033[1;32mAfter (Saturation Enhance)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/SaturationEnhance.jpg");

    cout << endl;

    // Show example 27
    cout << "       \033[47m\033[30m***** 27. Edge Detection *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/lena.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    EdgeDetection(img);

    cout << "       \033[1;32mAfter \033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/EdgeDetection.jpg");

    cout << endl;

    // Show example 28
    cout << "       \033[47m\033[30m***** 28. Swirl Filter *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/lena.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    SwirlFilter(img, 20);

    cout << "       \033[1;32mAfter (Strength = 20)\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/SwirlFilter.jpg");

    cout << endl;

    // Show example 26
    cout << "       \033[47m\033[30m***** 29. Fish Eye Filter *****\033[m" << endl << endl;
    img -> LoadImage("Image-Folder/lena.jpg");

    cout << "       \033[1;34mBefore\033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();

    FishEyeFilter(img);

    cout << "       \033[1;32mAfter \033[m" << endl;
    if(DISPLAY_FLAG) img -> Display_X_Server();
    img -> DumpImage("./Result/FishEyeFilter.jpg");

    cout << endl;

    // End Introduction
    cout << "       \033[1;33m\033[5mEnd intro of bit-field filter  (All demo images have been dumped in 'Result' folder)\033[m" << endl << endl;
    cout << "       Let's modify images by yourself." << endl;
    cout << "       Continue [y/n]? ";
    char tmp_c;
    cin >> tmp_c;
    if(tmp_c != 'y'  && tmp_c != 'Y') exit(1);

    // Free memory
    delete img;
}

void PM(PhotoMosaic pm)
{
    cout << endl << endl;
    cout << "       ========================================================" << endl;
    cout << "       |\033[47m\033[30m           Now, let's do Photo Mosaic!!!!!            \033[m|" << endl;
    cout << "       ========================================================" << endl;
    cout << endl;
    string str;
    cout << "       Please input a file path of the image you want to do Photo Mosaic: ";
    cin >> str;

    str = "Image-Folder/" + str;

    pm.setPath(str, "Image-Folder/cifar10");
    pm.GetPhotoMosaic(32);

    cout << endl;
    // End Photo Mosaic
    cout << "       \033[1;33m\033[5mEnd Photo Mosaic (Image has been dumped in 'Result' folder)\033[m" << endl << endl;
}