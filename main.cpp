# include "image.h"
# include "gray_image.h"
#include "inc/bit_field_filter.h"
# include "rgb_image.h"
# include "photo_mosaic.h"
# include "bit_field_filter.h"

int main(int argc, char *argv[])
{
    /*Image* img1 = new RGBImage();
    img1 -> LoadImage("Image-Folder/lena.jpg");
    img1 -> Display_X_Server();
    GammaCorrection(img1, 0.75);
    img1 -> DumpImage("lena_gamma_correction.jpg");
    img1 -> Display_X_Server();

    Image* img2 = new RGBImage();
    img2 -> LoadImage("Image-Folder/lena.jpg");
    StaticEnhance(img2,1.25 , 15);
    img2 -> DumpImage("lena_static_enhance.jpg");
    img2 -> Display_X_Server();

    Image* img3 = new RGBImage();
    img3 -> LoadImage("Image-Folder/lena.jpg");
    Flip(img3);
    img3 -> DumpImage("lena_flip.jpg");
    img3 -> Display_X_Server();

    Image* img4 = new RGBImage();
    img4 -> LoadImage("Image-Folder/lena.jpg");
    Quantization(img4, 2);
    img4 -> DumpImage("lena_quan_6.jpg");
    img4 -> Display_X_Server();
    Quantization(img4, 4);
    img4 -> DumpImage("lena_quan_4.jpg");
    img4 -> Display_X_Server();

    Image* img5 = new RGBImage();
    img5 -> LoadImage("Image-Folder/lena.jpg");
    HistogramEqualization(img5);
    img5 -> DumpImage("lena_hist_equal.jpg");
    img5 -> Display_X_Server();

    Image* img6 = new RGBImage();
    img6 -> LoadImage("Image-Folder/lena.jpg");
    MaxRGB(img6);
    img6 -> DumpImage("lena_maxrgb.jpg");
    img6 -> Display_X_Server();*/

    /*Image* img7 = new GrayImage();
    img7 -> LoadImage("Image-Folder/crowd.png");
    img7 -> Display_X_Server();
    HistogramEqualization(img7);
    img7 -> DumpImage("crowd_hist_equal.png");
    img7 -> Display_X_Server();

    Image* img8 = new RGBImage();
    img8 -> LoadImage("Image-Folder/handsomeman.jpg");
    img8 -> Display_X_Server();
    MaxRGB(img8);
    img8 -> DumpImage("handsomeman_maxRGB.jpg");
    img8 -> Display_X_Server();

    Image* img9 = new RGBImage();
    img9 -> LoadImage("Image-Folder/handsomeman.jpg");
    GrayWorld(img9);
    img9 -> DumpImage("handsomeman_grayworld.jpg");
    img9 -> Display_X_Server();*/

    /*Image* img10 = new RGBImage();
    img10 -> LoadImage("Image-Folder/lena.jpg");
    BoxFilter(img10, 7);
    img10 -> DumpImage("lena_box_7.jpg");
    img10 -> Display_X_Server();

    Image* img11 = new RGBImage();
    img11 -> LoadImage("Image-Folder/lena.jpg");
    BoxFilter(img11, 31);
    img11 -> DumpImage("lena_box_31.jpg");
    img11 -> Display_X_Server();

    Image* img12 = new GrayImage();
    img12 -> LoadImage("Image-Folder/lena.jpg");
    BoxFilter(img12, 7);
    img12 -> DumpImage("lena_box_7_gray.jpg");
    img12 -> Display_X_Server();

    Image* img13 = new GrayImage();
    img13 -> LoadImage("Image-Folder/lena.jpg");
    BoxFilter(img13, 31);
    img13 -> DumpImage("lena_box_31_gray.jpg");
    img13 -> Display_X_Server();*/

    /*Image* img14 = new RGBImage();
    img14 -> LoadImage("Image-Folder/lena.jpg");
    MedianFilter(img14, 3);
    img14 -> DumpImage("lena_median_5.jpg");
    img14 -> Display_X_Server();

    Image* img15 = new RGBImage();
    img15 -> LoadImage("Image-Folder/lena.jpg");
    MedianFilter(img15, 7);
    img15 -> DumpImage("lena_median_11.jpg");
    img15 -> Display_X_Server();*/

    Image* img16 = new GrayImage();
    img16 -> LoadImage("Image-Folder/dog.jpg");
    img16 -> Display_X_Server();
    LaplacianFilter_A(img16);
    img16 -> DumpImage("dog_lap_A.jpg");
    img16 -> Display_X_Server();

    Image* img17 = new GrayImage();
    img17 -> LoadImage("Image-Folder/dog.jpg");
    LaplacianFilter_B(img17);
    img17 -> DumpImage("dog_lap_B.jpg");
    img17 -> Display_X_Server();
    
    Image* img18 = new GrayImage();
    img18 -> LoadImage("Image-Folder/dog.jpg");
    PrewittFilter_H(img18);
    img18 -> DumpImage("dog_lap_B.jpg");
    img18 -> Display_X_Server();

    Image* img19 = new GrayImage();
    img19 -> LoadImage("Image-Folder/dog.jpg");
    PrewittFilter_V(img19);
    img19 -> DumpImage("dog_lap_B.jpg");
    img19 -> Display_X_Server();

    Image* img20 = new GrayImage();
    img20 -> LoadImage("Image-Folder/dog.jpg");
    SobelFilter_H(img20);
    img20 -> DumpImage("dog_lap_B.jpg");
    img20 -> Display_X_Server();

    Image* img21 = new GrayImage();
    img21 -> LoadImage("Image-Folder/dog.jpg");
    SobelFilter_V(img21);
    img21 -> DumpImage("dog_lap_B.jpg");
    img21 -> Display_X_Server();
    // some bit field filter design driven code here

    // some photo mosaic driven code here

    // Free memory
    /*delete img1;
    delete img2;
    delete img3;
    delete img4;
    delete img5;
    delete img6;
    delete img7;
    delete img8;
    delete img9;*/

    return 0;
}
