#ifndef FCLASSFIY_H_INCLUDED
#define FCLASSFIY_H_INCLUDED



#include "dlib/svm.h"

#include <iostream>
#include <vector>
#include <fstream>
#include "dlib/rand.h"
using namespace std;
using namespace dlib;

// Our data will be 2-dimensional data. So declare an appropriate type to contain these points.
typedef matrix<double,4,1> sample_type;
typedef one_vs_one_trainer<any_trainer<sample_type> > ovo_trainer;
// ----------------------------------------------------------------------------------------

void generate_data (
    std::vector<sample_type>& samples,
    std::vector<double>& labels
);


class fClassfiy
{
public:
    fClassfiy():features_num(4){}
    void Train();
    void Predict();

private :
    int features_num;
    std::vector<sample_type> train_feature;
    std::vector<double> train_labels;

    std::vector<sample_type> test_feature;
    std::vector<double> test_labels;




    // Finally, make the one_vs_one_trainer.
    ovo_trainer trainer;

};


void testMain();

#endif // FCLASSFIY_H_INCLUDED
