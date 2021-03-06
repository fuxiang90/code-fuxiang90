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

    fImgSvm():mwordnum(1000),mtrainimgsum(0),mtestingsum(0) {
        //mfeatures_num = mwordnum + 128;
        mfeatures_num = mwordnum ;
    }
    virtual ~fImgSvm() ;
    //打开file 目录下的文件，然后取出所有的jpg
    //生成feature
    //并生成字典
    //img向量化
    //得到每一类的训练向量
    void PreProcess(string file);
    void Work();
    virtual void Train() = 0;
protected:
    fImgFeature mfimgfeature;
    int32_t mfeatures_num ;
    int32_t mwordnum;
    int32_t mtrainimgsum ;
    int32_t mtestingsum;
    map < int ,vector< double > > dictmap;
    vector< vector <double > > imgvec;
    vector< vector<double > > imgtestvec;
    vector < int32_t > imgtestlabelvec;
    vector< int32_t >  imgtrainlabelvec;
    vector < int32_t > labvec;


    int createFeatureFile(string dirname ,int flag = 1);

    void createFeatureDict();

    //把图像向量化
    void vectorImg(string subpath,vector< vector<double > >  &matrix ,vector < int32_t > & lab);

    void getDictFile();
    int getNearVec(vector<double > &dvec);
    void test_libsvm();
    void test_libsvm2();
    void getTestImg(vector< vector<double > >  &matrix);
    bool kmeans(SGMatrix<float64_t> &data ,  CDenseFeatures<float64_t>*  &centers , int32_t numfeatures);

    virtual void getImgVecFile( string subpath,vector< vector<double > >  &matrix ,vector < int32_t > & lab);
};


#endif // FIMGSVM_H_INCLUDED
