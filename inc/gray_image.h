# ifndef _GRAY_IMAGE_H_
# define _GRAY_IMAGE_H_

# include "image.h"

class GrayImage : public Image
{
    private:
        int** pixel;

    public:
        // Constructor
        GrayImage();
        GrayImage(int w, int h, int** p);

        // Destructor
        ~GrayImage();

        // Display Function
        bool LoadImage(string filename);
        void DumpImage(string filename);
        void Display_X_Server();
        void Display_ASCII();
        void Display_CMD();

        // Flip
        void Flip();

        // Brightness Adjustment
        void GammaCorrection(double gamma);
};

#endif