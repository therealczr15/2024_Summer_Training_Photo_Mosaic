# ifndef _RGB_IMAGE_H_
# define _RGB_IMAGE_H_

# include "image.h"

class RGBImage : public Image
{
    private:
        int*** pixel;

    public:
        // constructor
        RGBImage();
        RGBImage(int w, int h, int*** p);

        // destructor
        ~RGBImage();

        // member function
        bool LoadImage(string filename);
        void DumpImage(string filename);
        void Display_X_Server();
        void Display_ASCII();
        void Display_CMD();
};

#endif