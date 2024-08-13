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

// Interface
void interface(){
    bool running = true;
    char c;
    while(running){
        cout << "Hello!" << endl;
        cout << "Do you want to continue?" << endl;
        cin >> c;
        if(c == 'y'){
            running = false;
        }
    }
}