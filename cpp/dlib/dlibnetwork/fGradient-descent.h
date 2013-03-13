#ifndef FGRADIENT-DESCENT_H_INCLUDED
#define FGRADIENT-DESCENT_H_INCLUDED

#include "dlib/svm.h"

#include <iostream>
#include <vector>
#include <fstream>
#include "dlib/rand.h"
using namespace std;
using namespace dlib;



class fGradientDescent
{
typedef matrix<double,5,1> sample_type;
public:
    fGradientDescent(int _features):features_num(_features + 1){

    }
    void Train();
    void Predict();

private:
    int features_num;
    int train_num ;
    int test_num;
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
#endif // FGRADIENT-DESCENT_H_INCLUDED
