# ifndef _PHOTO_MOSAIC_H_
# define _PHOTO_MOSAIC_H_

# include "image.h"
# include "gray_image.h"
# include "rgb_image.h"

using namespace std;

class PhotoMosaic
{
    private:
        static Data_Loader dl;
        RGBImage tgtImg;
};

#endif