# include "image.h"
# include "gray_image.h"
# include "inc/bit_field_filter.h"
# include "rgb_image.h"
# include "photo_mosaic.h"
# include "bit_field_filter.h"

int main(int argc, char *argv[])
{
    Image *img1 = new GrayImage();
    img1 -> LoadImage("Image-Folder/dark_landscape.jpg");
    img1 -> DumpImage("img1_1.jpg");
    img1 -> Display_X_Server();
    GammaCorrection(img1, 0.75);
    img1 -> DumpImage("img1_2.jpg");
    img1 -> Display_X_Server();

    Image *img2 = new RGBImage();
    img2 -> LoadImage("Image-Folder/lena.jpg");
    img2 -> DumpImage("img2_1.jpg");
    img2 -> Display_X_Server();
    GammaCorrection(img2, 0.75);
    img2 -> DumpImage("img2_2.jpg");
    img2 -> Display_X_Server();

    Image *img3 = new RGBImage();
    img3 -> LoadImage("Image-Folder/dark_landscape.jpg");
    img3 -> DumpImage("img3_1.jpg");
    img3 -> Display_X_Server();
    GammaCorrection(img3, 0.75);
    img3 -> DumpImage("img3_2.jpg");
    img3 -> Display_X_Server();

    // some bit field filter design driven code here

    // some photo mosaic driven code here

    // Free memory
    delete img1;
    delete img2;
    delete img3;

    return 0;
}
