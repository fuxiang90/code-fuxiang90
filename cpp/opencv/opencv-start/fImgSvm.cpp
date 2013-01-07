#include"fImgSvm.h"


static string grootpath = "/home/fuxiang/code-fuxiang90/cpp/opencv/opencv-start/";
extern void print_message(FILE* target, const char* str)
{
	fprintf(target, "%s", str);
}

void fImgSvm::PreProcess(string dirname)
{
    createFeatureFile(dirname,1);
    createFeatureFile("test",2);
    createFeatureDict();
    vectorImg("feature",imgvec ,imglabelvec);
    //test_libsvm();
    test_libsvm2();

}
int fImgSvm::createFeatureFile(string dirname ,int flag)
{
    chdir(grootpath.c_str());
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if( (dp = opendir(dirname.c_str() ) ) == NULL ) {
        fprintf(stderr, "cannot open directory: %s\n", dirname.c_str());
        return -1;
    }

    chdir(dirname.c_str());
    while( (entry = readdir(dp)) != NULL) {
        if( S_ISDIR(statbuf.st_mode)  && (strcmp(".." , entry->d_name) ==0) ) {
            continue;
        } else {

            //strcpy(filename[filenum++], entry->d_name);
            string filename = entry->d_name;

            if(filename == "." || filename == "..")
                continue;
            int pos =  filename.find(".jpg") ;

            if(pos == -1 )
                continue;
            string storefilename = filename.substr(0 , filename.find(".jpg") - 0);
            storefilename = storefilename + ".feature";
            if(flag == 2)
                mfimgfeature.StoreImgSift(filename , "../testfeature/"+storefilename);
            else
                mfimgfeature.StoreImgSift(filename , "../feature/"+storefilename);

            printf("%s\n",  entry->d_name);
        }
    }

}
//从所有的feature 文件中读出所有的feature 。
void fImgSvm::createFeatureDict()
{
    static char * dirname = "/home/fuxiang/code-fuxiang90/cpp/opencv/opencv-start/feature";
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    chdir("/home/fuxiang/code-fuxiang90/cpp/opencv/opencv-start");
    if( (dp = opendir( "/home/fuxiang/code-fuxiang90/cpp/opencv/opencv-start/feature" ) ) == NULL ) {
        fprintf(stderr, "cannot open directory: %s\n", dirname);
        //return ;
    }

    //double darray[SIFTN] ;
    vector < vector<double > > featurevec;
    int featuresum = 0;
    chdir(dirname);
    while( (entry = readdir(dp)) != NULL) {
        if( S_ISDIR(statbuf.st_mode)  ) {
            continue;
        } else {

            //strcpy(filename[filenum++], entry->d_name);
            string filename = entry->d_name;
            //filename = ""
            if(filename == "." || filename == "..")
                continue;
            int pos =  filename.find(".feature") ;
            if(pos == -1 )
                continue;

            mfimgfeature.getSiftFeatureFile(filename ,featurevec);
        }
    }
    int nfeature = featurevec.size();
   // imglabelvec.assign(nfeature+1,0);
    //double (*pszDiscriptor)[SIFTN] = new double[nfeature][SIFTN];
//    double pszDiscriptor[nfeature][SIFTN] ;


//    double **pszDiscriptor;
//    pszDiscriptor = (double ** ) malloc(nfeature * sizeof(double *));
//    for(int i = 0 ; i < nfeature ; i ++){
//        double *temp = NULL;
//        temp = (double *) malloc(sizeof(double) * SIFTN );
//        if(temp == NULL){
//            printf("malloc error\n");
//            return ;
//        }
//        *(pszDiscriptor + i) = temp;
//    }
//    for (int i = 0; i < nfeature; ++i)  {
//        for (int j = 0; j < SIFTN; j++) {
//            pszDiscriptor[i][j] = featurevec[i][j];
//        }
//    }

    SGMatrix<float64_t> data(SIFTN, nfeature) ;
    for (int i = 0; i < nfeature; ++i)  {
        for (int j = 0; j < SIFTN; j++) {
            data(j ,i) = featurevec[i][j];
        }
    }

    CDenseFeatures<float64_t>* centers;
    kmeans(data,centers,nfeature);

//    int cnClusterNumber = mwordnum;
//    CvMat *pszLabels = cvCreateMat(nfeature, 1, CV_32SC1);
//    CvMat szSamples, *pszClusterCenters ;
//    pszClusterCenters =  cvCreateMat(cnClusterNumber, SIFTN, CV_32FC1);
//    cvInitMatHeader ( &szSamples,nfeature,SIFTN, CV_32FC1, pszDiscriptor);
//    cvKMeans2(&szSamples, cnClusterNumber, pszLabels,cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 1.0 ),1, (CvRNG *)0, 0, pszClusterCenters);
    //cvKMeans2(&szSamples, cnClusterNumber, pszLabels, pszClusterCenters);
    ofstream fout("dict");
    for(int i = 0 ; i < mwordnum ; i ++) {
        vector<double > d ;
        for(int j = 0 ; j < SIFTN ; j ++) {
            fout << data(j,i) << " " ;
            d.push_back(data(j,i) );
        }
        dictmap.insert( map<int ,vector<double> >::value_type(i ,d) );

        fout << endl;
    }
    fout.close();

    SG_UNREF(data);
    SG_UNREF(centers);
}

/*
把一个目录下的所有feature 向量化
*/
void fImgSvm::vectorImg(string subpath , vector< vector<double > >  & imgfeaturevec,vector < int32_t > & lab)
{
    printf("------------img vector-------------------------\n");
    string dirname = grootpath + subpath;
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    chdir(grootpath.c_str());




    if( (dp = opendir( dirname.c_str() ) ) == NULL ) {
        fprintf(stderr, "cannot open directory: %s\n", dirname.c_str() );
        //return ;
    }
    int imgcount = 0;
    while( (entry = readdir(dp)) != NULL){
        string filestr = entry->d_name;
        if(filestr.find(".feature") != -1) imgcount ++;
    }
    if(subpath == "feature") fImgSvm::mtrainimgsum  = imgcount;
    else fImgSvm::mtestingsum  = imgcount;
    imgfeaturevec.resize(imgcount);
    int indexid = -1;

    for(int i = 0 ; i < imgfeaturevec.size()  ; i ++){
        imgfeaturevec[i].assign(mwordnum ,0);
    }
    //double darray[SIFTN] ;

    int imgid = 0;
    chdir(dirname.c_str());

    if( (dp = opendir( dirname.c_str() ) ) == NULL ) {
        fprintf(stderr, "cannot open directory: %s\n", dirname.c_str() );
        //return ;
    }
    while( (entry = readdir(dp)) != NULL) {
        if( S_ISDIR(statbuf.st_mode)  && (strcmp(".." , entry->d_name) ==0) ) {
            continue;
        } else {

            //strcpy(filename[filenum++], entry->d_name);
            string filename = entry->d_name;
            //filename = ""
            if(filename == "." || filename == "..")
                continue;
            int pos =  filename.find(".feature") ;
            if(pos == -1 )
                continue;
            indexid = filename[0] -'0' ;
            lab.push_back(indexid);
            vector <vector <double > > vec;


            mfimgfeature.getSiftFeatureFile(filename ,vec);

            int len = vec.size();
            for(int i = 0 ; i < len ;  i ++){
                int t = getNearVec(vec[i]);
                imgfeaturevec[imgid][t] ++;
            }
            imgid ++ ;

            printf("%s\n",filename.c_str());
        }
    }

    string outfilename = subpath+"vector";
    ofstream fout(outfilename.c_str() );
    for(int i = 0 ; i < imgcount ; i ++){
        for(int j = 0 ; j < mwordnum ; j ++){
            fout << imgfeaturevec[i][j] <<" ";
        }
        fout << endl;
    }
    fout.close();
}
void fImgSvm::getDictFile()
{
    ifstream fin("dict");

}
int fImgSvm::getNearVec(vector<double > & dvec)
{
    double dist = 999999.0;
    int32_t nearpos = -1;
    for(map<int ,vector<double> > ::iterator it = dictmap.begin() ; \
        it != dictmap.end() ; it ++){
        vector<double > &t = it->second;
        int len = t.size();
        double d = 0.0;
        for(int i = 0 ; i < len ; i ++){
            d += (dvec[i] -  t[i] ) *(dvec[i] -  t[i] );
        }
        d = sqrt(d);
        if(d < dist) {
            dist = d;
            nearpos = it->first;
        }
    }
    return nearpos;
}
void fImgSvm::test_libsvm()
{
	init_shogun(&print_message);
	index_t num_vec=imgvec.size();
	index_t num_feat=SIFTN;
	index_t num_class=2;

	// create some data
	SGMatrix<float64_t> matrix(num_feat, num_vec);
	for(int i = 0 ; i < num_vec ; i ++ ){
        for(int j = 0 ; j < num_feat ; j ++ ){
            matrix(j,i) = imgvec[i][j];
        }
	}
	//SGVector<float64_t>::range_fill_vector(matrix.matrix, num_feat*num_vec);

	// create vectors
	// shogun will now own the matrix created
	CDenseFeatures<float64_t>* features=new CDenseFeatures<float64_t>(matrix);

	// create three labels
	CMulticlassLabels* labels=new CMulticlassLabels(num_vec);
	for (index_t i=0; i<num_vec; ++i)
		labels->set_label(i,imglabelvec[i]);

	// create gaussian kernel with cache 10MB, width 0.5
	CGaussianKernel* kernel = new CGaussianKernel(10, 0.5);
	kernel->init(features, features);

	// create libsvm with C=10 and train
	CMulticlassLibSVM* svm = new CMulticlassLibSVM(10, kernel, labels);
	svm->train();

	// classify on training examples
	CMulticlassLabels* output=CMulticlassLabels::obtain_from_generic(svm->apply());
	SGVector<float64_t>::display_vector(output->get_labels().vector, output->get_num_labels(),
			"初始的 output");

	/* assert that batch apply and apply(index_t) give same result */
	for (index_t i=0; i<output->get_num_labels(); ++i)
	{
		float64_t label=svm->apply_one(i);
		SG_SPRINT("result output[%d]=%f\n", i, label);
		ASSERT(output->get_label(i)==label);
	}
	SG_UNREF(output);

	// free up memory
	SG_UNREF(svm);

	exit_shogun();
}
void fImgSvm::test_libsvm2()
{
    init_shogun(&print_message);
    const int32_t feature_cache=0;
	const int32_t kernel_cache=0;
	const float64_t rbf_width=10;
	const float64_t svm_C=10;
	const float64_t svm_eps=0.001;

	int32_t num=mtrainimgsum;
	int32_t dims=SIFTN;
	float64_t dist=0.5;

	SGVector<float64_t> lab(num); //标签
	SGMatrix<float64_t> feat(dims, num);

	//gen_rand_data(lab, feat, dist);
    for(int i = 0 ; i < num ; i ++ ){
        for(int j = 0 ; j < dims ; j ++ ){
            feat(j,i) = imgvec[i][j];
        }
	}

	 for(int i = 0 ; i < num ; i ++ ){
        //lab[i] = imglabelvec[i]*1.0;
        if(imglabelvec[i] ==  1) lab[i] = -1.0;
        else lab[i] = 1.0;
	 }

	// create train labels
	CLabels* labels=new CBinaryLabels(lab);

	// create train features
	CDenseFeatures<float64_t>* features=new CDenseFeatures<float64_t>(feature_cache);
	SG_REF(features);
	features->set_feature_matrix(feat);

	// create gaussian kernel
	CGaussianKernel* kernel=new CGaussianKernel(kernel_cache, rbf_width);
	SG_REF(kernel);
	kernel->init(features, features);

	// create svm via libsvm and train
	CLibSVM* svm=new CLibSVM(svm_C, kernel, labels);
	SG_REF(svm);
	svm->set_epsilon(svm_eps);
	svm->train();

	SG_SPRINT("num_sv:%d b:%f\n", svm->get_num_support_vectors(),
			svm->get_bias());

	// classify + display output
	CBinaryLabels* out_labels=CBinaryLabels::obtain_from_generic(svm->apply());

	for (int32_t i=0; i<num; i++)
	{
		SG_SPRINT("out[%d]=%f (%f)\n", i, out_labels->get_label(i),
				out_labels->get_confidence(i));
	}

    CBinaryLabels* result = CBinaryLabels::obtain_from_generic (svm->apply(features) );
    for (int32_t i=0; i<3; i++)
                SG_SPRINT("output[%d]=%f\n", i, result->get_label(i));

    // update
    // predict the
    printf("----------------test -----------------\n");

    getTestImg(imgtestvec);
    int32_t testnum = mtestingsum;
    SGMatrix<float64_t> testfeat(dims, testnum);

    for(int i = 0 ; i < testnum ; i ++ ){
        for(int j = 0 ; j < dims ; j ++ ){
            testfeat(j,i) = imgtestvec[i][j];
        }
	}

    CDenseFeatures<float64_t>* testfeatures=new CDenseFeatures<float64_t>(feature_cache);
	SG_REF(testfeatures);
	testfeatures->set_feature_matrix(testfeat);
    CBinaryLabels* testresult = CBinaryLabels::obtain_from_generic (svm->apply(testfeatures) );
    int32_t rightnum1 = 0;
    int32_t rightsum1 = 0;
    int32_t rightnum2 = 0;
    for (int32_t i=0; i<testnum; i++){
         SG_SPRINT("output[%d]=%f\n", i, testresult->get_label(i));
         if(labtestvec[i] == 1  ){
            if( (testresult->get_label(i))  < 0.0){
                rightnum1 ++;
            }
            rightsum1 ++ ;
         }else if(labtestvec[i] == 2 && testresult->get_label(i) > 0.0){
            rightnum2 ++ ;
         }
     }

     printf(" %lf\n ",(rightnum1+rightnum2)*1.0 / testnum);
     printf("class 1 : %lf\n",rightnum1 *1.0 / rightsum1);
     printf("class 2 : %lf\n",rightnum2 *1.0 / (testnum -  rightsum1));



	SG_UNREF(out_labels);
	SG_UNREF(kernel);
	SG_UNREF(features);
	SG_UNREF(svm);

	exit_shogun();
}

void fImgSvm::getTestImg(vector< vector<double > >  &test)
{
    vectorImg("testfeature",test,labtestvec);
}

void fImgSvm::Work()
{
    string dir = grootpath+"feature";
    chdir(dir.c_str());
    ifstream fin("dict");
    for(int i = 0 ; i < mwordnum ; i ++ ){
        vector<double > dvec;
        for(int j = 0 ; j < SIFTN ; j ++ ){
            double d;
            fin>> d;
            dvec.push_back(d);
        }
        dictmap.insert( map<int ,vector<double > >::value_type(i ,dvec ));
    }
    vectorImg("feature",imgvec ,imglabelvec);
    test_libsvm2();
}

bool fImgSvm::kmeans(SGMatrix<float64_t> &data ,  CDenseFeatures<float64_t>*  &centers ,int32_t num_features)
{
    init_shogun(&print_message);


	int32_t num_clusters= mwordnum ;


	int32_t dim_features=SIFTN;

	float64_t cluster_std_dev=2.0;

	/* build random cluster centers */
	SGMatrix<float64_t> cluster_centers(dim_features, num_clusters);
	SGVector<float64_t>::random_vector(cluster_centers.matrix, dim_features*num_clusters,
			0, 20.0);
	//SGMatrix<float64_t>::display_matrix(cluster_centers.matrix, cluster_centers.num_rows,
	//		cluster_centers.num_cols, "cluster centers");




	/* create features, SG_REF to avoid deletion */
	CDenseFeatures<float64_t>* features=new CDenseFeatures<float64_t> ();
	features->set_feature_matrix(data);
	SG_REF(features);

	/* create labels for cluster centers */
	CMulticlassLabels* labels=new CMulticlassLabels(num_features);
	for (index_t i=0; i<num_features; ++i)
		labels->set_label(i, 0);

	/* create distance */
	CEuclideanDistance* distance=new CEuclideanDistance(features, features);

	/* create distance machine */
	CKMeans* clustering=new CKMeans(num_clusters, distance);
	clustering->train(features);

	/* build clusters */
//	CMulticlassLabels* result=CMulticlassLabels::obtain_from_generic(clustering->apply());
//	for (index_t i=0; i<result->get_num_labels(); ++i)
//		SG_SPRINT("cluster index of vector %i: %f\n", i, result->get_label(i));

	/* print cluster centers */
    centers = (CDenseFeatures<float64_t>*)distance->get_lhs();

	SGMatrix<float64_t> centers_matrix=centers->get_feature_matrix();


	//SG_UNREF(result);
	SG_UNREF(centers);
	SG_UNREF(clustering);
	SG_UNREF(labels);
	SG_UNREF(features);

	exit_shogun();
}
