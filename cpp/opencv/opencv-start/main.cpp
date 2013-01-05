#include "fImgFeature.h"
#include "fImgSvm.h"
int main()
{
    string name = "cat.jpg";
    //fImgFeature * ftest = new fImgFeature(name);

    //ftest->Test();
    int i;
    cout << "input for 1 ,run work:" ;
    cin>>i;
    fImgSvm * fsvm = new fImgSvm();
    if(i == 1)
        fsvm->Work();
    else
        fsvm->PreProcess("imgfile");

//    ifstream  fin( "1.feature" );
//    int n ;
//    int m = SIFTN;
//    fin>>n>>m;
//
//    double d = 0.0;
//    vector <vector <double > > data;
//    for(int i = 0  ; i < n ; i ++){
//        vector<double > temp;
//        for(int j = 0 ; j < m ; j ++){
//                fin>>d;
//                temp.push_back(d);
//        }
//        data.push_back(temp);
//    }

//
//	IplImage* pImg;
//	pImg = cvLoadImage("./cat.jpg", 1);
//
//	cvNamedWindow("Image", 1);
//	cvShowImage("Image", pImg);
//
//	cvWaitKey(0);
//
//	cvDestroyWindow("Image");
	//cvReleaseImage(&pImg);

	return 0;
}
