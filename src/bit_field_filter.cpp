# include "bit_field_filter.h"

# define CASE_GAMMACORRECTION       0b0000000000000001
# define CASE_STATICENHANCE         0b0000000000000010
# define CASE_FLIP                  0b0000000000000100
# define CASE_QUANTIZATION          0b0000000000001000
# define CASE_HISTOGRAMEQUALIZATION 0b0000000000010000
# define CASE_MAXRGB                0b0000000000100000
# define CASE_GRAYWORLD             0b0000000001000000
# define CASE_BOXFILTER             0b0000000010000000
# define CASE_MEDIANFILTER          0b0000000100000000
# define CASE_LAPLACIANFILTER_A     0b0000001000000000
# define CASE_LAPLACIANFILTER_B     0b0000010000000000
# define CASE_PREWITTFILTER_H       0b0000100000000000
# define CASE_PREWITTFILTER_V       0b0001000000000000
# define CASE_SOBELFILTER_H         0b0010000000000000
# define CASE_SOBELFILTER_V         0b0100000000000000

# define CSE_NUM 15

# define DISPLAY_FLAG false 
                            // true: display image on xserver
                            // false: for checking memory leak

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

// Filter Interface
void Filter(Image* img){
    // Initial menu
    cout << "Welcome to use bit-field filter!!!!!" << endl;
    cout << endl;

    cout << "Here are the functions you can choose from:" << endl;
    cout << "====================================" << endl;
    cout << "|  1. GammaCorrection              |" << endl;
    cout << "|  2. StaticEnhance                |" << endl;
    cout << "|  3. Flip                         |" << endl;
    cout << "|  4. Quantization                 |" << endl;
    cout << "|  5. HistogramEqualization        |" << endl;
    cout << "|  6. MaxRGB                       |" << endl;
    cout << "|  7. GrayWorld                    |" << endl;
    cout << "|  8. BoxFilter                    |" << endl;
    cout << "|  9. MedianFilter                 |" << endl;
    cout << "| 10. LaplacianFilter_A            |" << endl;
    cout << "| 11. LaplacianFilter_B            |" << endl;
    cout << "| 12. PrewittFilter_H              |" << endl;
    cout << "| 13. PrewittFilter_V              |" << endl;
    cout << "| 14. SobelFilter_H                |" << endl;
    cout << "| 15. SobelFilter_V                |" << endl;
    cout << "====================================" << endl;
    cout << endl;

    // Input option
    string input;

    cout << "Please input the numbers of the functions you want." << endl;
    cout << "Notice that the execution order is ascending." << endl;
    cout << endl;

    cout << "For example1, input: 1 3 8, which means:" << endl;
    cout << "input image -> GammaCorrection -> Flip -> BoxFilter -> output image" << endl;
    cout << endl;

    cout << "For example2, input: 3 8 1, which means:" << endl;
    cout << "input image -> GammaCorrection -> Flip -> BoxFilter -> output image" << endl;
    cout << endl;

    cout << "Your input:" << endl;
    getline(cin, input);

    // Fetch options
    uint16_t options = 0b0000000000000000;
    string str, tmp;
    for(char c:input){
        tmp = c;
        if(c == ' ' || c == '\"'){
            LoadOptions(options, stoi(str));
            str.clear();
        }
        else{
            str = str + tmp;
        }
    }
    if(!str.empty()){
        LoadOptions(options, stoi(str));
        str.clear();
    }

    //// check options
    //bitset<16> bs(options);
    //cout << bs << endl;

    // Running options 
    RunOptions(img, options);

    // End filter
    cout << "End filter" << endl;
}

void LoadOptions(uint16_t &options, int case_n){
    switch(case_n){
        case 1:
            options = options | CASE_GAMMACORRECTION;
            break;
        case 2:
            options = options | CASE_STATICENHANCE;
            break;
        case 3:
            options = options | CASE_FLIP;
            break;
        case 4:
            options = options | CASE_QUANTIZATION;
            break;
        case 5:
            options = options | CASE_HISTOGRAMEQUALIZATION;
            break;
        case 6:
            options = options | CASE_MAXRGB;
            break;
        case 7:
            options = options | CASE_GRAYWORLD;
            break;
        case 8:
            options = options | CASE_BOXFILTER;
            break;
        case 9:
            options = options | CASE_MEDIANFILTER;
            break;
        case 10:
            options = options | CASE_LAPLACIANFILTER_A;
            break;
        case 11:
            options = options | CASE_LAPLACIANFILTER_B;
            break;
        case 12:
            options = options | CASE_PREWITTFILTER_H;
            break; 
        case 13:
            options = options | CASE_PREWITTFILTER_V;
            break;
        case 14:
            options = options | CASE_SOBELFILTER_H;
            break; 
        case 15:
            options = options | CASE_SOBELFILTER_V;
            break; 
        default:
            cout << "Case " << case_n << "is an invalid input!" << endl;
            exit(1);  
    }
}

void RunOptions(Image* img, uint16_t options){
    int tmp_int;
    double tmp_dbl1, tmp_dbl2;
    char tmp_c;

    // check origin image
    if(DISPLAY_FLAG){
        cout << "Do you want to see the origin image (y/n)? ";
        cin >> tmp_c;
        if(tmp_c == 'y') img -> Display_X_Server();
    }

    cout << endl << endl;

    // ===== GammaCorrection =====
    if(options & CASE_GAMMACORRECTION){
        cout << "===============" << endl;
        cout << "GammaCorrection" << endl;
        cout << "===============" << endl;

        cout << "Please input gamma: ";
        cin >> tmp_dbl1;
        GammaCorrection(img, tmp_dbl1);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== StaticEnhance =====
    if(options & CASE_STATICENHANCE){
        cout << "=============" << endl;
        cout << "StaticEnhance" << endl;
        cout << "=============" << endl;

        cout << "Please input alpha, beta: ";
        cin >> tmp_dbl1 >> tmp_dbl2;
        StaticEnhance(img, tmp_dbl1, tmp_dbl2);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Flip =====
    if(options & CASE_FLIP){
        cout << "====" << endl;
        cout << "Flip" << endl;
        cout << "====" << endl;

        Flip(img);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== Quantization =====
    if(options & CASE_QUANTIZATION){
        cout << "============" << endl;
        cout << "Quantization" << endl;
        cout << "============" << endl;

        cout << "Please input quan: ";
        cin >> tmp_int;
        Quantization(img, tmp_int);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== HistogramEqualization =====
    if(options & CASE_HISTOGRAMEQUALIZATION){
        cout << "=====================" << endl;
        cout << "HistogramEqualization" << endl;
        cout << "=====================" << endl;

        HistogramEqualization(img);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== MaxRGB =====
    if(options & CASE_MAXRGB){
        cout << "======" << endl;
        cout << "MaxRGB" << endl;
        cout << "======" << endl;

        MaxRGB(img);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== GrayWorld =====
    if(options & CASE_GRAYWORLD){
        cout << "=========" << endl;
        cout << "GrayWorld" << endl;
        cout << "=========" << endl;

        GrayWorld(img);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== BoxFilter =====
    if(options & CASE_BOXFILTER){
        cout << "=========" << endl;
        cout << "BoxFilter" << endl;
        cout << "=========" << endl;

        cout << "Please input kernalSize: ";
        cin >> tmp_int;
        BoxFilter(img, tmp_int);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== MedianFilter =====
    if(options & CASE_MEDIANFILTER){
        cout << "============" << endl;
        cout << "MedianFilter" << endl;
        cout << "============" << endl;

        cout << "Please input kernalSize: ";
        cin >> tmp_int;
        MedianFilter(img, tmp_int);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== LaplacianFilter_A =====
    if(options & CASE_LAPLACIANFILTER_A){
        cout << "=================" << endl;
        cout << "LaplacianFilter_A" << endl;
        cout << "=================" << endl;

        LaplacianFilter_A(img);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== LaplacianFilter_B =====
    if(options & CASE_LAPLACIANFILTER_B){
        cout << "=================" << endl;
        cout << "LaplacianFilter_B" << endl;
        cout << "=================" << endl;

        LaplacianFilter_B(img);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== PrewittFilter_H =====
    if(options & CASE_PREWITTFILTER_H){
        cout << "===============" << endl;
        cout << "PrewittFilter_H" << endl;
        cout << "===============" << endl;

        PrewittFilter_H(img);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== PrewittFilter_V =====
    if(options & CASE_PREWITTFILTER_V){
        cout << "===============" << endl;
        cout << "PrewittFilter_V" << endl;
        cout << "===============" << endl;

        PrewittFilter_V(img);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== SobelFilter_H =====
    if(options & CASE_SOBELFILTER_H){
        cout << "=============" << endl;
        cout << "SobelFilter_H" << endl;
        cout << "=============" << endl;

        SobelFilter_H(img);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }

    // ===== SobelFilter_V =====
    if(options & CASE_SOBELFILTER_V){
        cout << "=============" << endl;
        cout << "SobelFilter_V" << endl;
        cout << "=============" << endl;

        SobelFilter_V(img);

        if(DISPLAY_FLAG){
            cout << "Do you want to see the result (y/n)? ";
            cin >> tmp_c;
            if(tmp_c == 'y') img -> Display_X_Server();
        }

        cout << endl << endl;
    }
}