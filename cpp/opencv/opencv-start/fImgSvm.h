#ifndef FIMGSVM_H_INCLUDED
#define FIMGSVM_H_INCLUDED

#include "fStd.h"
#include "fImgFeature.h"


#include <sys/stat.h>
#include <sys/types.h>

using namespace std;
const int rows = 128;



class fImgSvm
{
public:
    fImgSvm():mwordnum(500),mimgsum(0){}
    //打开file 目录下的文件，然后取出所有的jpg
    //生成feature
    //并生成字典
    //img向量化
    //得到每一类的训练向量
    void PreProcess(string file);
private:
    fImgFeature mfimgfeature;
    int32_t mwordnum;
    int32_t mimgsum ;
    map < int ,vector< double > > dictmap;
    vector < vector <double > > imgvec;
    vector< int32_t >  imglabelvec;
    vector < int32_t > labvec;

    int createFeatureFile(string dirname);

    void createFeatureDict();

    //把图像向量化
    void vectorImg();

    void getDictFile();
    int getNearVec(vector<double > &dvec);
    void test_libsvm();
    void test_libsvm2();
};


#endif // FIMGSVM_H_INCLUDED
