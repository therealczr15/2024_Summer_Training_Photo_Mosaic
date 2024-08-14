# include "image.h"
# include "gray_image.h"
# include "inc/bit_field_filter.h"
# include "rgb_image.h"
# include "photo_mosaic.h"
# include "bit_field_filter.h"

# define DISPLAY_FLAG false 
                            // true: display image on xserver
                            // false: for checking memory leak

int main(int argc, char *argv[])
{
    //// ===== GammaCorrection test =====
    //Image* img1 = new RGBImage();
    //img1 -> LoadImage("Image-Folder/lena.jpg");
    //if(DISPLAY_FLAG) img1 -> Display_X_Server();
    //GammaCorrection(img1, 0.75);
    //img1 -> DumpImage("lena_gamma_correction.jpg");
    //if(DISPLAY_FLAG) img1 -> Display_X_Server();

    //// ===== StaticEnhance test =====
    //Image* img2 = new RGBImage();
    //img2 -> LoadImage("Image-Folder/lena.jpg");
    //StaticEnhance(img2,1.25 , 15);
    //img2 -> DumpImage("lena_static_enhance.jpg");
    //if(DISPLAY_FLAG) img2 -> Display_X_Server();

    //// ===== Flip test =====
    //Image* img3 = new RGBImage();
    //img3 -> LoadImage("Image-Folder/lena.jpg");
    //Flip(img3);
    //img3 -> DumpImage("lena_flip.jpg");
    //if(DISPLAY_FLAG) img3 -> Display_X_Server();

    //// ===== Quantization test =====
    //Image* img4 = new RGBImage();
    //img4 -> LoadImage("Image-Folder/lena.jpg");
    //Quantization(img4, 2);
    //img4 -> DumpImage("lena_quan_6.jpg");
    //if(DISPLAY_FLAG) img4 -> Display_X_Server();
    //Quantization(img4, 4);
    //img4 -> DumpImage("lena_quan_4.jpg");
    //if(DISPLAY_FLAG) img4 -> Display_X_Server();

    //// ===== HistogramEqualization test =====
    //Image* img5 = new RGBImage();
    //img5 -> LoadImage("Image-Folder/lena.jpg");
    //HistogramEqualization(img5);
    //img5 -> DumpImage("lena_hist_equal.jpg");
    //if(DISPLAY_FLAG) img5 -> Display_X_Server();

    //// ===== MaxRGB test =====
    //Image* img6 = new RGBImage();
    //img6 -> LoadImage("Image-Folder/lena.jpg");
    //MaxRGB(img6);
    //img6 -> DumpImage("lena_maxrgb.jpg");
    //if(DISPLAY_FLAG) img6 -> Display_X_Server();

    //// ===== HistogramEqualization test =====
    //Image* img7 = new GrayImage();
    //img7 -> LoadImage("Image-Folder/crowd.png");
    //if(DISPLAY_FLAG) img7 -> Display_X_Server();
    //HistogramEqualization(img7);
    //img7 -> DumpImage("crowd_hist_equal.png");
    //if(DISPLAY_FLAG) img7 -> Display_X_Server();

    //// ===== MaxRGB test =====
    //Image* img8 = new RGBImage();
    //img8 -> LoadImage("Image-Folder/handsomeman.jpg");
    //if(DISPLAY_FLAG) img8 -> Display_X_Server();
    //MaxRGB(img8);
    //img8 -> DumpImage("handsomeman_maxRGB.jpg");
    //if(DISPLAY_FLAG) img8 -> Display_X_Server();

    //// ===== GrayWorld test =====
    //Image* img9 = new RGBImage();
    //img9 -> LoadImage("Image-Folder/handsomeman.jpg");
    //GrayWorld(img9);
    //img9 -> DumpImage("handsomeman_grayworld.jpg");
    //if(DISPLAY_FLAG) img9 -> Display_X_Server();

    //// ===== BoxFilter test =====
    //Image* img10 = new RGBImage();
    //img10 -> LoadImage("Image-Folder/lena.jpg");
    //BoxFilter(img10, 7);
    //img10 -> DumpImage("lena_box_7.jpg");
    //if(DISPLAY_FLAG) img10 -> Display_X_Server();

    //// ===== BoxFilter test =====
    //Image* img11 = new RGBImage();
    //img11 -> LoadImage("Image-Folder/lena.jpg");
    //BoxFilter(img11, 31);
    //img11 -> DumpImage("lena_box_31.jpg");
    //if(DISPLAY_FLAG) img11 -> Display_X_Server();

    //// ===== BoxFilter test =====
    //Image* img12 = new GrayImage();
    //img12 -> LoadImage("Image-Folder/lena.jpg");
    //BoxFilter(img12, 7);
    //img12 -> DumpImage("lena_box_7_gray.jpg");
    //if(DISPLAY_FLAG) img12 -> Display_X_Server();

    //// ===== BoxFilter test =====
    //Image* img13 = new GrayImage();
    //img13 -> LoadImage("Image-Folder/lena.jpg");
    //BoxFilter(img13, 31);
    //img13 -> DumpImage("lena_box_31_gray.jpg");
    //if(DISPLAY_FLAG) img13 -> Display_X_Server();

    //// ===== MedianFilter test =====
    //Image* img14 = new RGBImage();
    //img14 -> LoadImage("Image-Folder/lena.jpg");
    //MedianFilter(img14, 3);
    //img14 -> DumpImage("lena_median_5.jpg");
    //if(DISPLAY_FLAG) img14 -> Display_X_Server();

    //// ===== MedianFilter test =====
    //Image* img15 = new RGBImage();
    //img15 -> LoadImage("Image-Folder/lena.jpg");
    //MedianFilter(img15, 7);
    //img15 -> DumpImage("lena_median_11.jpg");
    //if(DISPLAY_FLAG) img15 -> Display_X_Server();

    //// ===== LaplacianFilter_A test =====
    //Image* img16 = new RGBImage();
    //img16 -> LoadImage("Image-Folder/dog.jpg");
    //if(DISPLAY_FLAG) img16 -> Display_X_Server();
    //LaplacianFilter_A(img16);
    //img16 -> DumpImage("dog_lap_A.jpg");
    //if(DISPLAY_FLAG) img16 -> Display_X_Server();

    //// ===== LaplacianFilter_B test =====
    //Image* img17 = new RGBImage();
    //img17 -> LoadImage("Image-Folder/dog.jpg");
    //LaplacianFilter_B(img17);
    //img17 -> DumpImage("dog_lap_B.jpg");
    //if(DISPLAY_FLAG) img17 -> Display_X_Server();
    
    //// ===== PrewittFilter_H test =====
    //Image* img18 = new RGBImage();
    //img18 -> LoadImage("Image-Folder/dog.jpg");
    //PrewittFilter_H(img18);
    //img18 -> DumpImage("dog_pre_h.jpg");
    //if(DISPLAY_FLAG) img18 -> Display_X_Server();

    //// ===== PrewittFilter_V test =====
    //Image* img19 = new RGBImage();
    //img19 -> LoadImage("Image-Folder/dog.jpg");
    //PrewittFilter_V(img19);
    //img19 -> DumpImage("dog_pre_v.jpg");
    //if(DISPLAY_FLAG) img19 -> Display_X_Server();

    //// ===== SobelFilter_H test =====
    //Image* img20 = new RGBImage();
    //img20 -> LoadImage("Image-Folder/dog.jpg");
    //SobelFilter_H(img20);
    //img20 -> DumpImage("dog_sob_h.jpg");
    //if(DISPLAY_FLAG) img20 -> Display_X_Server();

    //// ===== SobelFilter_V test =====
    //Image* img21 = new RGBImage();
    //img21 -> LoadImage("Image-Folder/dog.jpg");
    //SobelFilter_V(img21);
    //img21 -> DumpImage("dog_sob_v.jpg");
    //if(DISPLAY_FLAG) img21 -> Display_X_Server();

    //// ===== bit-field filter test =====
    Image* img = new RGBImage();
    img -> LoadImage("Image-Folder/lena.jpg");
    Filter(img);

    // some bit field filter design driven code here

    // some photo mosaic driven code here

    // Free memory
    //delete img1;
    //delete img2;
    //delete img3;
    //delete img4;
    //delete img5;
    //delete img6;
    //delete img7;
    //delete img8;
    //delete img9;
    //delete img16;
    //delete img17;
    //delete img18;
    //delete img19;
    //delete img20;
    //delete img21;
    delete img;

    return 0;
}
