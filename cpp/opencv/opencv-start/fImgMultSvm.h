#ifndef FIMGMULTSVM_H_INCLUDED
#define FIMGMULTSVM_H_INCLUDED
#include "fImgSvm.h"

class fImgMultSvm : public fImgSvm
{
public:
    fImgMultSvm(){
        //fImgSvm::fImgSvm();

    }

    virtual void Train();
    void Predict();
private:
    void multSvm();
};

#endif // FIMGMULTSVM_H_INCLUDED
