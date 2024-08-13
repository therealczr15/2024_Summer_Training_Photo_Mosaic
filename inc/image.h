# ifndef _IMAGE_H_
# define _IMAGE_H_

# include "data_loader.h"
# include <iostream>
# include <string>
# include <cmath>

using namespace std;

class Image
{
    protected:
        int _w;
        int _h;
        static Data_Loader dl;

    public:
        // Constructor
        Image();
        Image(int w, int h);

        // Destructor
        virtual ~Image();

        // Pure Virtual Fucntion
        // Display Function
        virtual bool LoadImage(string filename) = 0;
        virtual void DumpImage(string filename) = 0;
        virtual void Display_X_Server() = 0;
        virtual void Display_ASCII() = 0;
        virtual void Display_CMD() = 0;

        // Flip
        virtual void Flip() = 0;

        // Brightness Adjustment
        virtual void GammaCorrection(double gamma) = 0;

        // Member Function
        int get_width();
        int get_height();
};

#endif