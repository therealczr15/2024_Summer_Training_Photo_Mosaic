# include "photo_mosaic.h"

# define SUB_IMG_SIZE 32
# define DISPLAY_FLAG true

using namespace std;

void printProgressBar(double progress, double total, int barwidth)
{
    double percentage = progress / total;
    int filledLength = barwidth * percentage;
    //cout << "percentage: " << percentage << endl;
    //cout << "filledLength: " << filledLength << endl;
    cout << "\r       \033[1;32m|\033[m";
    for(int i = 0; i < barwidth; i++)
    {
        if(i < filledLength)
            cout << "\033[1;32m▉\033[m";
        else
            cout << " ";
    }
    cout << "\033[1;32m|\033[m  Processing " << fixed << setprecision(3) << percentage * 100 << " %";
    cout.flush();
}

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
void PhotoMosaic::setPath(string filename, string directoryPath)
{
    tgtImg.LoadImage(filename);
    dl.List_Directory(directoryPath, directoryImg);
}

void PhotoMosaic::GetPhotoMosaic(int sub_img_size)
{
    int h = tgtImg.get_height();
    int w = tgtImg.get_width();
    h = int( round( h * 1.0 / sub_img_size ) ) * sub_img_size;
    w = int( round( w * 1.0 / sub_img_size ) ) * sub_img_size;

    tgtImg.Scaling(h, w);

    // check origin image
    if(DISPLAY_FLAG)
    {
        cout << "       Do you want to see the origin image [y/n]? ";
        char tmp_c;
        cin >> tmp_c;
        if(tmp_c == 'y'  || tmp_c == 'Y') tgtImg.Display_X_Server();
    }

    cout << endl << endl;

    vector<RGBImage> allImg (directoryImg.size());
    for(unsigned int i = 0; i < directoryImg.size(); i++)
        allImg[i].LoadImage(directoryImg[i]);

    vector<vector<double>> allImgRGB (directoryImg.size(), vector<double> (3));
    for(unsigned int i = 0; i < directoryImg.size(); i++)
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
            for(unsigned int m = 0; m < directoryImg.size(); m++)
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

            printProgressBar(i / sub_img_size * (w / sub_img_size) + j / sub_img_size + 1, h * w / (sub_img_size * sub_img_size) , 54);
        }
    }

    cout << endl;

    if(DISPLAY_FLAG)
    {
        cout << "       Do you want to see the result [y/n]? ";
        char tmp_c;
        cin >> tmp_c;
        if(tmp_c == 'y' || tmp_c == 'Y') tgtImg.Display_X_Server();
    }
    tgtImg.DumpImage("Result/PhotoMosaic.jpg");

}
