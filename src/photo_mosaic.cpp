# include "photo_mosaic.h"

// ===== Initialize Data Loader =====
Data_Loader PhotoMosaic::dl;

// ===== Constructor =====
PhotoMosaic::PhotoMosaic()
{
    trgImg = nullptr;
}

// ===== Destructor =====
PhotoMosaic::~PhotoMosaic()
{
    delete trgImg;
}

// ===== Public Member Function =====

Image* PhotoMosaic::Execute(string trgPath, string srcPath)
{
    //==================================================
    // Load images
    trgImg = new RGBImage();
    trgImg->LoadImage(trgPath);

    vector<string> srcFilenames;
    Image** srcImgs = new Image*[SRC_TOTAL_NUM];
    for(int i = 0; i < SRC_TOTAL_NUM; i++)
        srcImgs[i] = new RGBImage();
    int numSrc = 0;

    dl.List_Directory(srcPath, srcFilenames);
    for(string srcFilename : srcFilenames){
        if(srcImgs[numSrc]->LoadImage(srcFilename))
            numSrc++;
        if(numSrc == SRC_TOTAL_NUM)
            break;
    }

    cout << "Load images finished" << endl;

    //==================================================
    // Scale images into appropriate size
    int newH, newW;
    double factor;

    newH = SUB_PIC_SIZE * SUB_PIC_NUM;
    factor = (double)newH / (double)trgImg->get_height();
    newW = ((int)(factor * trgImg->get_width()) / SUB_PIC_SIZE) * SUB_PIC_SIZE; 

    //cout << "Origin target(H, W) = (" << trgImg->get_height() << " ," << trgImg->get_width() << ")" << endl;
    Scaling(trgImg, newH, newW);
    //cout << "New target(H, W) = (" << trgImg->get_height() << " ," << trgImg->get_width() << ")" << endl;
    for(int i = 0; i < numSrc; i++){
        //if(i == 0) cout << "Origin source(H, W) = (" << srcImgs[i]->get_height() << " ," << srcImgs[i]->get_width() << ")" << endl;
        Scaling(srcImgs[i], SUB_PIC_SIZE, SUB_PIC_SIZE);
        //if(i == 0) cout << "Origin source(H, W) = (" << srcImgs[i]->get_height() << " ," << srcImgs[i]->get_width() << ")" << endl;
    }
    
    cout << "Scale images finished" << endl;

    //==================================================
    // Calculate average of each source image
    vector<int> srcAvgR, srcAvgG, srcAvgB;

    for(int i_src; i_src < numSrc; i_src++){
        CalSrcAvg(srcImgs[i_src], srcAvgR, srcAvgG, srcAvgB);
    }

    cout << "Calculate srcAvg finished" << endl;

    //==================================================
    // Calculate average of each target image
    vector<vector<int> > trgAvgR ,trgAvgG ,trgAvgB;
    int tmpR ,tmpG ,tmpB;

    trgAvgR.resize(SUB_PIC_NUM, vector<int>(SUB_PIC_NUM));
    trgAvgG.resize(SUB_PIC_NUM, vector<int>(SUB_PIC_NUM));
    trgAvgB.resize(SUB_PIC_NUM, vector<int>(SUB_PIC_NUM));
    for(int i_pic = 0; i_pic < SUB_PIC_NUM; i_pic++){
        for(int j_pic = 0; j_pic < SUB_PIC_NUM; j_pic++){
            tmpR = tmpG = tmpB = 0; 
            for(int row = i_pic*SUB_PIC_SIZE; row < (i_pic + 1)*SUB_PIC_SIZE; row++){
                for(int col = j_pic*SUB_PIC_SIZE; col < (j_pic + 1)*SUB_PIC_SIZE; col++){
                    tmpR += trgImg->pixel[row][col][0];
                    tmpG += trgImg->pixel[row][col][1];
                    tmpB += trgImg->pixel[row][col][2];
                }
            }
            trgAvgR[i_pic][j_pic] = int(tmpR / (SUB_PIC_SIZE * SUB_PIC_SIZE));
            trgAvgG[i_pic][j_pic] = int(tmpG / (SUB_PIC_SIZE * SUB_PIC_SIZE));
            trgAvgB[i_pic][j_pic] = int(tmpB / (SUB_PIC_SIZE * SUB_PIC_SIZE));
        }
    }

    cout << "Calculate trgAvg finished" << endl;

    //==================================================
    // Find minimum difference index
    vector<vector<int> > minDiffIdxs;
    int minDiffIdx;
    double rDiff, gDiff, bDiff, minDiff, diff;

    minDiffIdxs.resize(SUB_PIC_NUM, vector<int>(SUB_PIC_NUM, 0));
    for(int i_pic = 0; i_pic < SUB_PIC_NUM; i_pic++){
        for(int j_pic = 0; j_pic < SUB_PIC_NUM; j_pic++){
            minDiff = 442; // sqrt(255^2 * 3)
            for(int i_src = 0; i_src; i_src++){
                rDiff = trgAvgR[i_pic][j_pic] - srcAvgR[i_src];
                gDiff = trgAvgG[i_pic][j_pic] - srcAvgG[i_src];
                bDiff = trgAvgB[i_pic][j_pic] - srcAvgB[i_src];
                diff = sqrt(rDiff*rDiff + gDiff*gDiff + bDiff*bDiff);
                if(minDiff > diff){
                    minDiff = diff;
                    minDiffIdx = i_src;
                }
            }
            minDiffIdxs[i_pic][j_pic] = minDiffIdx;
        }
    }

    cout << "Find minDiffIdx finished" << endl;

    //==================================================
    // Set corresponding source images into target image
    Image* ansImage = new RGBImage();
    int*** tmpPixel;
    
    AllocateAns(ansImage, newH, newW);

    for(int i_pic = 0; i_pic < SUB_PIC_NUM; i_pic++){
        for(int j_pic = 0; j_pic < SUB_PIC_NUM; j_pic++){
            minDiffIdx = minDiffIdxs[i_pic][j_pic];
            tmpPixel = GetPixel(srcImgs[minDiffIdx]);
            SetSrc2Trg(ansImage, tmpPixel, i_pic, j_pic);
        }
    }

    cout << "Photo Mosaic finished" << endl;

    ansImage -> DumpImage("./result/test.jpg");

    //==================================================
    //Free memory
    for(int i = 0; i < numSrc; i++)
        delete srcImgs[i];
    delete[] srcImgs;

    srcAvgR.clear();
    srcAvgG.clear();
    srcAvgB.clear();

    for(int i = 0; i < SUB_PIC_NUM; i++){
        trgAvgR[i].clear();
        trgAvgG[i].clear();
        trgAvgB[i].clear();
    }
    trgAvgR.clear();
    trgAvgG.clear();
    trgAvgB.clear();

    cout << "Free finished" << endl;

    return ansImage;
}

void CalSrcAvg(Image* img, vector<int>& srcAvgR, vector<int>& srcAvgG, vector<int>& srcAvgB){
    img -> CalSrcAvg(srcAvgR, srcAvgG, srcAvgB);
}

void AllocateAns(Image* img, int newH, int newW){
    img -> AllocateAns(newH, newW);
}

int*** GetPixel(Image* img){
    return img -> GetPixel();
}

void SetSrc2Trg(Image* trg, int*** srcPixel, int i_pic, int j_pic){
    trg -> SetSrc2Trg(srcPixel, i_pic, j_pic);
}
