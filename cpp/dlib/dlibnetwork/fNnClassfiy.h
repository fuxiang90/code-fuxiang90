#ifndef FNNCLASSFIY_H_INCLUDED
#define FNNCLASSFIY_H_INCLUDED

#include <iostream>
#include <dlib/mlp.h>

using namespace std;
using namespace dlib;

class fNnClassfiy
{
public:
    fNnClassfiy(){
        features_num = 4;
    };

    void Work();

private:
    int features_num;

};
void NnMain();
#endif // FNNCLASSFIY_H_INCLUDED
