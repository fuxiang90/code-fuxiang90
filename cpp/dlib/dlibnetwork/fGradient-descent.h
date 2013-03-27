#ifndef FGRADIENT_DESCENT_H_INCLUDED
#define FGRADIENT_DESCENT_H_INCLUDED

#include "dlib/svm.h"

#include <iostream>
#include <vector>
#include <fstream>
#include "dlib/rand.h"
using namespace std;
using namespace dlib;



class fGradientDescent
{

public:
    fGradientDescent(){}
    typedef matrix<double,5,1> sample_type;
    fGradientDescent(int _features):features_num(_features + 1){

    }
    ~fGradientDescent(){}
    virtual void Train();
    virtual void Predict();

    void SetTrainTimes(int _t){
        train_times = _t;
    }

protected:
    int features_num;
    int train_num ;
    int test_num;
    int train_times;
    double weigth0;
    std::vector<sample_type> train_feature;
    std::vector<double> train_labels;

    std::vector<sample_type> test_feature;
    std::vector<double> test_labels;

    std::vector<double> weights_vec;
    std::vector<double > u_vec ;
    std::vector<double> q_vec ;
    void gradientDesecent();

    void gaussian(std::vector<sample_type> & features_vec);
};
void  gradientMain();
//试着将 fGradientDescent 这里的类抽象 ，重新实现 Train 和 Pridict 函数
class fGradientDescentBus : public fGradientDescent
{
public:
    fGradientDescentBus(int _features){
        features_num = _features;
    }

    virtual void Train();
    virtual void Predict();
private:
};

void  gradientBusMain();

#endif // FGRADIENT-DESCENT_H_INCLUDED
