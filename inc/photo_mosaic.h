# ifndef _PHOTO_MOSAIC_H_
# define _PHOTO_MOSAIC_H_

# include "image.h"
# include "gray_image.h"
# include "rgb_image.h"
# include "bit_field_filter.h"

using namespace std;

# define SUB_PIC_SIZE   32      // size of src image
# define SUB_PIC_NUM    32      // number of src image at one side of target image

# define SRC_TOTAL_NUM  10      // total number of src image

class PhotoMosaic
{
    private:
        static Data_Loader dl;
        RGBImage* trgImg;

    public:
        PhotoMosaic();
        ~PhotoMosaic();
        Image* Execute(string trgPath, string srcPath);
};

void CalSrcAvg(Image* img, vector<int>& srcAvgR, vector<int>& srcAvgG, vector<int>& srcAvgB);
void AllocateAns(Image* img, int newH, int newW);
int*** GetPixel(Image* img);
void SetSrc2Trg(Image* trg, int*** srcPixel, int i_pic, int j_pic);

#endif