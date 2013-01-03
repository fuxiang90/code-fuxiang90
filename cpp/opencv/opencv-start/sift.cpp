#include <iostream>
#include <math.h>
#include <cv.h>
#include <highgui.h>


#include "sift.h"
#include "imgfeatures.h"
#include "utils.h"
int main(int argc, char* argv[])
{
    IplImage* img,*dst;
    img=cvLoadImage("1.jpg",0);
    struct feature* features;
    int n = 0;
    //int n = _sift_features(img, &features, SIFT_INTVLS/*3*/, SIFT_SIGMA/*1.6*/, SIFT_CONTR_THR/*0.04*/,
    //SIFT_CURV_THR/*10*/, SIFT_IMG_DBL/*1*/, SIFT_DESCR_WIDTH/*4*/, SIFT_DESCR_HIST_BINS/*8*/);
    n = sift_features( img, &features );
    export_features("1.out", features, n);
    return 0;
}
