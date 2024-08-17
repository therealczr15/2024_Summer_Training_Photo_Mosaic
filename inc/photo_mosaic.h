# ifndef _PHOTO_MOSAIC_H_
# define _PHOTO_MOSAIC_H_

# include "image.h"
# include "gray_image.h"
# include "rgb_image.h"
# include <unistd.h>
# include <iomanip>

using namespace std;

class PhotoMosaic
{
    private:
        static Data_Loader dl;
        RGBImage tgtImg;
        vector<string> directoryImg;
    public:
        PhotoMosaic(string filename = "Image-Folder/girl_2x.png", string directoryPath = "Image-Folder/cifar10");
        ~PhotoMosaic();
        void setPath(string filename, string directoryPath);
        void GetPhotoMosaic(int sub_img_size);
};

void printProgressBar(double progress, double total, int barwidth);

#endif