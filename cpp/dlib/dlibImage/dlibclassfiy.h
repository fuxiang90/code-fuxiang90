#ifndef DLIBCLASSFIY_H_INCLUDED
#define DLIBCLASSFIY_H_INCLUDED

#include "dlib/svm.h"

#include <iostream>
#include <vector>
#include <fstream>
#include "dlib/rand.h"
using namespace std;
using namespace dlib;

// Our data will be 2-dimensional data. So declare an appropriate type to contain these points.
typedef matrix<double,1000,1> sample_type;
typedef one_vs_one_trainer<any_trainer<sample_type> > ovo_trainer;
// ----------------------------------------------------------------------------------------

void generate_data (
    std::vector<sample_type>& samples,
    std::vector<double>& labels
);


class dlibClassfiy
{
public:
    dlibClassfiy(int _features_num):features_num(_features_num){}
    void Train(string filename);
    void Predict(string filename);

private :
    int features_num;
    std::vector<sample_type> train_feature;
    std::vector<double> train_labels;

    std::vector<sample_type> test_feature;
    std::vector<double> test_labels;
    one_vs_one_decision_function<ovo_trainer> df;




    // Finally, make the one_vs_one_trainer.
    ovo_trainer trainer;

};


void testMain();
#endif // DLIBCLASSFIY_H_INCLUDED
