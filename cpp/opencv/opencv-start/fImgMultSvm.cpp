#include "fImgMultSvm.h"

static string grootpath = "/home/fuxiang/code-fuxiang90/cpp/opencv/opencv-start/";
static void print_message(FILE* target, const char* str)
{
    fprintf(target, "%s", str);
}
void fImgMultSvm::Train()
{
    createFeatureFile("imgfile",1);
    createFeatureFile("test",2);
    createFeatureDict();
    //vectorImg("feature",imgvec ,imglabelvec);
}

 void fImgMultSvm::Predict()
 {
    string dir = grootpath+"feature";
    chdir(dir.c_str());
    ifstream fin("dict");
    for(int i = 0 ; i < mwordnum ; i ++ ) {
        vector<double > dvec;
        for(int j = 0 ; j < SIFTN ; j ++ ) {
            double d;
            fin>> d;
            dvec.push_back(d);
        }
        dictmap.insert( map<int ,vector<double > >::value_type(i ,dvec ));
    }
    vectorImg("feature",imgvec ,imgtrainlabelvec);
    #if 0
        exit(0);
    #endif
    multSvm();
 }

void fImgMultSvm::multSvm()
{
    const int32_t feature_cache=0;
    int32_t num_vec=mtrainimgsum;
	int32_t num_feat=mfeatures_num;
	int32_t num_class=2;
    init_shogun(&print_message);
	// create some data
	SGMatrix<float64_t> matrix(num_feat, num_vec);
	//SGVector<float64_t>::range_fill_vector(matrix.matrix, num_feat*num_vec);

    for(int i = 0 ; i < mtrainimgsum ; i ++ ) {
        for(int j = 0 ; j < num_feat ; j ++ ) {
            matrix(j,i) = imgvec[i][j];
        }
    }


	// create vectors
	// shogun will now own the matrix created
	CDenseFeatures<float64_t>* features=new CDenseFeatures<float64_t>(matrix);

	// create three labels
	CMulticlassLabels* labels=new CMulticlassLabels(num_vec);
	for (index_t i=0; i<num_vec; ++i)
		labels->set_label(i, imgtrainlabelvec[i] - 1);

	// create gaussian kernel with cache 10MB, width 0.5
	CGaussianKernel* kernel = new CGaussianKernel(10, 0.5);
	kernel->init(features, features);

	// create libsvm with C=10 and train
	CMulticlassLibSVM* svm = new CMulticlassLibSVM(10, kernel, labels);
	svm->train();

	// classify on training examples
	CMulticlassLabels* output=CMulticlassLabels::obtain_from_generic(svm->apply());

    printf("----------------predict -----------------\n");

    getTestImg(imgtestvec);
    int32_t testnum = mtestingsum;
    int32_t dims = mfeatures_num;
    SGMatrix<float64_t> testfeat(dims, testnum);

    for(int i = 0 ; i < testnum ; i ++ ) {
        for(int j = 0 ; j < dims ; j ++ ) {
            testfeat(j,i) = imgtestvec[i][j];
        }
    }

    CDenseFeatures<float64_t>* testfeatures=new CDenseFeatures<float64_t>(feature_cache);
    SG_REF(testfeatures);
    testfeatures->set_feature_matrix(testfeat);
    CMulticlassLabels* testresult = CMulticlassLabels::obtain_from_generic (svm->apply(testfeatures) );

    int32_t rightnum = 0;
	for (int32_t i=0; i<testnum; i++) {
        int mlabel = testresult->get_label(i);
        if(mlabel == imgtestlabelvec[i] - 1 ) {
            rightnum++;
        }

        SG_SPRINT("output[%d]=%f\n", i, testresult->get_label(i));

    }
    printf("%d %f\n",testnum ,rightnum*1.0/testnum);

	SG_UNREF(output);

	// free up memory
	SG_UNREF(svm);

	exit_shogun();

}
