# ifndef _IMAGE_H_
# define _IMAGE_H_

# include "data_loader.h"
# include <iostream>
# include <string>

using namespace std;

class Image
{
    protected:
        int _w;
        int _h;
        static Data_Loader dl;

    public:
        // constructor
        Image();
        Image(int w, int h);

        // destructor
        ~Image();

        // pure virtual fucntion
        virtual bool LoadImage(string filename) = 0;
        virtual void DumpImage(string filename) = 0;
        virtual void Display_X_Server() = 0;
        virtual void Display_ASCII() = 0;
        virtual void Display_CMD() = 0;

        // member function
        int get_width();
        int get_height();
};

#endif