#ifndef FIMGFEATURE_H_INCLUDED
#define FIMGFEATURE_H_INCLUDED

#include "fStd.h"

using namespace std;

const int SIFTN = 128;
class fImgFeature
{
public:
    fImgFeature(){}
    fImgFeature(IplImage* &img):mimg(img){}
    fImgFeature(string filename);


    //返回 siftfeature 的 个数
    int GetSift(string name ,CvMat* &mat);
    void StoreImgSift(string imgname ,string filename);
    void Test();
    void getSiftFeatureFile(string filename , vector<vector<double > > & a );

private:
    IplImage *  mimg;
    string mfilename ;

    void getColor(IplImage * img);
    void getColorByName(string name);
    void getShapeByName(string name);
    void getShape(IplImage * img);

    void getTexture(string name);


    //打印一个img 的矩阵
    void printImgMat(IplImage *img);
    void storeImgMatToFile(string name,IplImage * img);

};


#endif // FIMGFEATURE_H_INCLUDED
