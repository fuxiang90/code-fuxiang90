# include"fGradient-descent.h"



void fGradientDescent::Train()
{
    ifstream fin("traindata");
    int n ;
    fin>>n;
    train_num = n;
    for(int i = 0 ; i < n ; ++i){
        double label;


        double num;
        sample_type temp;
        for(int j = 0 ; j < features_num ; ++j){
            fin>>num;
            temp(j) = num;
        }
        fin>>label;
        train_labels.push_back(label);
        train_feature.push_back(temp);
    }
    fin.close();

    gaussian(train_feature);
    // 梯度下降算法
    // f(x) = w1 * x1 + w2*x2 + w3*x+w4*x4;
    gradientDesecent();
}

void fGradientDescent::gradientDesecent()
{
    int times =500;
    weights_vec.resize(features_num);
    for(int i = 0 ; i < features_num ; i ++){
        weights_vec[i] = 0.1;
    }
    double theta0 = 0.0005 ; //学习速度

    std::vector<double > delta(4,0.0);

    for(int i = 0 ; i < times ; i ++) {

        for(int i = 0 ; i < features_num ; i ++){
            delta[i] = 0;
        }

        for(int j = 0 ; j < train_num ; j ++){
            double o  = 0;
            for(int k = 0 ; k < features_num ; k ++){
                o += weights_vec[k]*train_feature[j](k);
            }

            for(int k = 0 ; k < features_num ; k ++){
                delta[k]  += theta0 *(train_labels[j] - o) *train_feature[j](k);
            }


        }

        for(int k = 0 ; k < features_num ; k ++){
            weights_vec[k]  += delta[k];
        }

        //
    }


    for(int k = 0 ; k < features_num ; k ++){
        cout << weights_vec[k] <<" " ;
    }
    cout << "\n";
}


void fGradientDescent::Predict()
{

    ifstream fin("testdata");
    int n ;
    fin>>n;
    test_num = n;
    for(int i = 0 ; i < n ; ++i){
        double label;

        double num;
        sample_type temp;
        for(int j = 0 ; j < features_num ; ++j){
            fin>>num;
            temp(j) = num;
        }
        fin>>label;
        test_labels.push_back(label);

        test_feature.push_back(temp);
    }
    fin.close();

    for(int i = 0 ; i < test_num ; i ++){
        double o  = 0;
        for(int k = 0 ; k < features_num ; k ++){
            o += weights_vec[k]*test_feature[i](k);
        }
        cout << o << "real is" << test_labels[i] <<endl;
    }


}
void fGradientDescent::gaussian(std::vector<sample_type> & features_vec)
{
    int n = features_vec.size();
    std::vector<double > u_vec(features_num ,0);
    std::vector<double> q_vec(features_num,0);
    for(int i =  0 ; i < n ; i ++){

        for(int j = 0 ; j < features_num ; j ++){
            u_vec[j]  += features_vec[i](j);
        }
    }

    //计算均值
    for(int j = 0 ; j < features_num ; j ++){
        u_vec[j] /= n;
    }


    // 计算方差
    for(int j = 0 ; j < features_num ; j ++){
        for(int i =  0 ; i < n ; i ++){
            q_vec[j]  += (features_vec[i](j) - u_vec[j]) * (features_vec[i](j) - u_vec[j]);
        }
         q_vec[j] /= n;
         q_vec[j]  = sqrt(q_vec[j]);
    }

    //归一化
    for(int i =  0 ; i < n ; i ++){

        for(int j = 0 ; j < features_num ; j ++){
           features_vec[i](j) = (features_vec[i](j) - u_vec[j])/q_vec[j];
        }
    }


}
void  gradientMain()
{
    fGradientDescent test(4) ;
    test.Train();
    test.Predict();
}
