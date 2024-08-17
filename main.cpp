# include "image.h"
# include "gray_image.h"
# include "rgb_image.h"
# include "photo_mosaic.h"
# include "bit_field_filter.h"

# define DISPLAY_FLAG false 
                            // true: display image on xserver
                            // false: for checking memory leak

int main(int argc, char *argv[])
{
    Introduction();
    Image* img = new RGBImage();
    Filter(img);
    delete img;

    PhotoMosaic pm;
    PM(pm);
    
    return 0;
}
