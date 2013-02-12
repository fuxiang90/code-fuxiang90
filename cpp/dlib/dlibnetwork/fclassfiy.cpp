#include "fclassfiy.h"
typedef one_vs_one_trainer<any_trainer<sample_type> > ovo_trainer;
typedef matrix<double,4,1> sample_type;

    // Finally, make the one_vs_one_trainer.

void fClassfiy::Train()
{
    ifstream fin("traindata");
    int n ;
    fin>>n;
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




    // Finally, make the one_vs_one_trainer.



    // Next, we will make two different binary classification trainer objects.  One
    // which uses kernel ridge regression and RBF kernels and another which uses a
    // support vector machine and polynomial kernels.  The particular details don't matter.
    // The point of this part of the example is that you can use any kind of trainer object
    // with the one_vs_one_trainer.
    typedef polynomial_kernel<sample_type> poly_kernel;
    typedef radial_basis_kernel<sample_type> rbf_kernel;

    // make the binary trainers and set some parameters
    krr_trainer<rbf_kernel> rbf_trainer;
    svm_nu_trainer<poly_kernel> poly_trainer;
    poly_trainer.set_kernel(poly_kernel(0.1, 1, 2));
    rbf_trainer.set_kernel(rbf_kernel(0.1));


    // Now tell the one_vs_one_trainer that, by default, it should use the rbf_trainer
    // to solve the individual binary classification subproblems.
    trainer.set_trainer(rbf_trainer);
    // We can also get more specific.  Here we tell the one_vs_one_trainer to use the
    // poly_trainer to solve the class 1 vs class 2 subproblem.  All the others will
    // still be solved with the rbf_trainer.
    trainer.set_trainer(poly_trainer, 1, 2);

    one_vs_one_decision_function<ovo_trainer> df = trainer.train(train_feature, train_labels);

    cout << "predicted label: "<< df(train_feature[0])  << ", true label: "<< train_labels[0] << endl;
    cout << "predicted label: "<< df(train_feature[2]) << ", true label: "<< train_labels[2] << endl;
}

void fClassfiy::Predict()
{

    ifstream fin("testdata");
    int n ;
    fin>>n;
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


    one_vs_one_decision_function<ovo_trainer> df = trainer.train(train_feature, train_labels);

    int test_num = test_feature.size();
    int rigth_num = 0;
    for(int i = 0 ; i < test_num ; i ++){
          cout << "predicted label: "<< df(test_feature[i])  << ", true label: "<< test_labels[i] << endl;
          if(df(test_feature[i]) == test_labels[i])
            rigth_num ++;
    }
    cout << rigth_num*1.0/test_num <<endl;
}
void testMain()
{
    fClassfiy test;
    test.Train();
    cout << "-----------------------------" <<endl;
    test.Predict();
}
