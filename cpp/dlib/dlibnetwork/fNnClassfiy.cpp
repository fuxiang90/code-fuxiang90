
#include "fNnClassfiy.h"


void fNnClassfiy::Work()
{
    typedef matrix<double, 4, 1> fsample_type;





    mlp::kernel_1a_c net(4,5);

    // train

    ifstream fin;
    fin.open("traindata");
    int n ;
    fin>>n;
    for(int i = 0 ; i < n ; ++i){
        double label;


        double num;
        fsample_type temp;
        for(int j = 0 ; j < features_num ; ++j){
            fin>>num;
            temp(j) = num;
        }
        fin>>label;

         net.train(temp,(label)/3);
    }
    fin.close();


    //

    fin.open ("testdata");
    fin>>n;
    int right_num = 0;
    for(int i = 0 ; i < n ; ++i){
        double label;


        double num;
        fsample_type temp;
        for(int j = 0 ; j < features_num ; ++j){
            fin>>num;
            temp(j) = num;
        }
        fin>>label;


        cout << "This sample should be close to" <<  (label)/3 <<"and it is classified as a " << net(temp) << endl;
        if(net(temp) ==  (label)/3 )
            right_num ++;
    }
    fin.close();

    cout << "正确率："<< right_num*1.0 / n <<endl;
}

void NnMain()
{
    fNnClassfiy test;
    test.Work();
}
