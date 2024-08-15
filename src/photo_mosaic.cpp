# include "photo_mosaic.h"

# define SUB_IMG_SIZE 32

using namespace std;

// ===== Initialize Data Loader =====
Data_Loader PhotoMosaic::dl;

// ===== Constructor =====

PhotoMosaic::PhotoMosaic(string filename, string directoryPath)
{
    tgtImg.LoadImage(filename);
    dl.List_Directory(directoryPath, directoryImg);
}

// ===== Destructor =====
PhotoMosaic::~PhotoMosaic()
{
    ;
}

//
void PhotoMosaic::GetPhotoMosaic(int sub_img_size)
{
    int h = tgtImg.get_height();
    int w = tgtImg.get_width();
    h = int( round( h * 1.0 / sub_img_size ) ) * sub_img_size;
    w = int( round( w * 1.0 / sub_img_size ) ) * sub_img_size;

    tgtImg.Scaling(h, w);

    tgtImg.Display_X_Server();
       
    vector<RGBImage> allImg (directoryImg.size());
    for(int i = 0; i < directoryImg.size(); i++)
        allImg[i].LoadImage(directoryImg[i]);

    vector<vector<double>> allImgRGB (directoryImg.size(), vector<double> (3));
    for(int i = 0; i < directoryImg.size(); i++)
    {
        double meanR = 0, meanG = 0, meanB = 0;
        for(int j = 0; j < allImg[i].get_height(); j++)
        {
            for(int k = 0; k < allImg[i].get_width(); k++)
            {
                meanR += allImg[i].GetPixel()[j][k][0];
                meanG += allImg[i].GetPixel()[j][k][1];
                meanB += allImg[i].GetPixel()[j][k][2];
            }
        }
        meanR = meanR * 1.0 / (allImg[i].get_height() * allImg[i].get_width());
        meanG = meanG * 1.0 / (allImg[i].get_height() * allImg[i].get_width());
        meanB = meanB * 1.0 / (allImg[i].get_height() * allImg[i].get_width());

        allImgRGB[i][0] = meanR;
        allImgRGB[i][1] = meanG;
        allImgRGB[i][2] = meanB;
    }
    
    for(int i = 0; i < h; i += sub_img_size)
    {
        for(int j = 0; j < w; j += sub_img_size)
        {
            double meanR = 0, meanG = 0, meanB = 0;
            for(int k = 0; k < sub_img_size; k++)
            {
                for(int l = 0; l < sub_img_size; l++)
                {
                    int row = i + k;
                    int col = j + l;
                    meanR += tgtImg.GetPixel()[row][col][0];
                    meanG += tgtImg.GetPixel()[row][col][1];
                    meanB += tgtImg.GetPixel()[row][col][2];
                }
            }
            meanR = meanR * 1.0 / (sub_img_size * sub_img_size);
            meanG = meanG * 1.0 / (sub_img_size * sub_img_size);
            meanB = meanB * 1.0 / (sub_img_size * sub_img_size);

            double diffR, diffG, diffB, diff;
            double diffMin = DBL_MAX;
            int minIdx;
            for(int m = 0; m < directoryImg.size(); m++)
            {
                diffR = meanR - allImgRGB[m][0];
                diffG = meanG - allImgRGB[m][1];
                diffB = meanB - allImgRGB[m][2];
                diff = sqrt(diffR * diffR + diffG * diffG + diffB * diffB);
                if(diff < diffMin)
                {
                    diffMin = diff;
                    minIdx = m;
                }
            }

            for(int k = 0; k < sub_img_size; k++)
            {
                for(int l = 0; l < sub_img_size; l++)
                {
                    int row = i + k;
                    int col = j + l;
                    for(int n = 0; n < 3; n++)
                    {
                        if(sub_img_size != SUB_IMG_SIZE)
                            allImg[minIdx].Scaling(sub_img_size, sub_img_size);
                        tgtImg.pixel[row][col][n] = allImg[minIdx].pixel[k][l][n];
                    }
                }
            }
        }
    }

    tgtImg.Display_X_Server();
    tgtImg.DumpImage("PhotoMosaic.jpg");

}
