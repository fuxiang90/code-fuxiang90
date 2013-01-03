#include "fImgFeature.h"


fImgFeature::fImgFeature(string filename)
{
    mfilename = filename;
    mimg=cvLoadImage(filename.c_str(),0);


    //cvShowImage("dst",mimg);
}
void  fImgFeature::Test()
{
//    cvNamedWindow("img",NULL);
//    cvNamedWindow("dst",NULL);
//    cvShowImage("img",mimg);

//    IplImage* img,*dst;
//    img=cvLoadImage("1.jpg",3);
//    cvNamedWindow("img",NULL);
//    cvShowImage("img",img);
//
//    IplImage * out ;
//    out = cvCreateImage( cvGetSize(img) , IPL_DEPTH_8U ,3 );
//    cvSmooth(img,out,CV_GAUSSIAN ,3,3);
//
//    cvNamedWindow("out",NULL);
//    cvShowImage("out",out);
//    cvWaitKey(10);

    //printImgMat(img);
    //getColorByName(mfilename);

    CvMat *s ;
    GetSift(mfilename,s );
    //getShapeByName(mfilename);
    //getTexture(mfilename);

}
void fImgFeature::getColorByName(string name)
{
    IplImage * src= cvLoadImage(name.c_str(),1);
    getColor(src);
}
void fImgFeature::getColor(IplImage * src)
{

    IplImage* hsv = cvCreateImage( cvGetSize(src), 8, 3 );
    IplImage* h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
    IplImage* s_plane = cvCreateImage( cvGetSize(src), 8, 1 );
    IplImage* v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
    IplImage* planes[] = { h_plane, s_plane };

    /** H 分量划分为16个等级，S分量划分为8个等级*/
    int h_bins = 16, s_bins = 8;
    int hist_size[] = {h_bins, s_bins};

    /** H 分量的变化范围*/
    float h_ranges[] = { 0, 180 };

    /** S 分量的变化范围*/
    float s_ranges[] = { 0, 255 };
    float* ranges[] = { h_ranges, s_ranges };

    /** 输入图像转换到HSV颜色空间*/
    cvCvtColor( src, hsv, CV_BGR2HSV );
    cvCvtPixToPlane( hsv, h_plane, s_plane, v_plane, 0 );

    /** 创建直方图，二维, 每个维度上均分*/
    CvHistogram * hist = cvCreateHist( 2, hist_size, CV_HIST_ARRAY, ranges, 1 );
    /** 根据H,S两个平面数据统计直方图*/
    cvCalcHist( planes, hist, 0, 0 );

    /** 获取直方图统计的最大值，用于动态显示直方图*/
    float max_value;
    cvGetMinMaxHistValue( hist, 0, &max_value, 0, 0 );


    /** 设置直方图显示图像*/
    int height = 240;
    int width = (h_bins*s_bins*6);
    IplImage* hist_img = cvCreateImage( cvSize(width,height), 8, 3 );
    cvZero( hist_img );

    /** 用来进行HSV到RGB颜色转换的临时单位图像*/
    IplImage * hsv_color = cvCreateImage(cvSize(1,1),8,3);
    IplImage * rgb_color = cvCreateImage(cvSize(1,1),8,3);
    int bin_w = width / (h_bins * s_bins);

    ofstream fout ("color");
    for(int h = 0; h < h_bins; h++) {
        for(int s = 0; s < s_bins; s++) {
            int i = h*s_bins + s;
            /** 获得直方图中的统计次数，计算显示在图像中的高度*/
            float bin_val = cvQueryHistValue_2D( hist, h, s );
            int intensity = cvRound(bin_val*height/max_value);

            fout << intensity << "\t" << endl;
            /** 获得当前直方图代表的颜色，转换成RGB用于绘制*/
            cvSet2D(hsv_color,0,0,cvScalar(h*180.f / h_bins,s*255.f/s_bins,255,0));
            cvCvtColor(hsv_color,rgb_color,CV_HSV2BGR);
            CvScalar color = cvGet2D(rgb_color,0,0);

            cout <<  color.val << endl;
            cvRectangle( hist_img, cvPoint(i*bin_w,height),
                         cvPoint((i+1)*bin_w,height - intensity),
                         color, -1, 8, 0 );
        }
    }

    fout.close();
    cvNamedWindow( "Source", 1 );
    cvShowImage( "Source", src );

    cvNamedWindow( "H-S Histogram", 1 );
    cvShowImage( "H-S Histogram", hist_img );

    cvWaitKey(10);

}

void fImgFeature::getShapeByName(string name)
{
    IplImage * img = cvLoadImage(name.c_str(),1);

    getShape(img);

}
void fImgFeature::getShape(IplImage * src)
{
    IplImage* pImg = NULL;
    IplImage* pCannyImg = NULL;
    //载入图像，强制转化为Gray
    pImg = src;
    //为canny边缘图像申请空间
    pCannyImg = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 1);
    //canny边缘检测
    cvCanny(pImg, pCannyImg, 50, 150, 3);
    //创建窗口
    cvNamedWindow("src", 1);
    cvNamedWindow("canny",1);
    //显示图像
    cvShowImage( "src", pImg );
    cvShowImage( "canny", pCannyImg );
    //等待按键
    cvWaitKey(-1);
    //销毁窗口
    cvDestroyWindow( "src" );
    cvDestroyWindow( "canny" );
    //释放图像
    cvReleaseImage( &pImg );
    cvReleaseImage( &pCannyImg );
}

void fImgFeature::getTexture(string name)
{

    int tmp[8]= {0};
    int sum=0;
    int k=0;
    IplImage* img,*dst;
    img=cvLoadImage(name.c_str(),1);
    CvScalar s;
    cvNamedWindow("img",NULL);
    cvNamedWindow("dst",NULL);
    cvShowImage("img",img);

    uchar* data=(uchar*)img->imageData;
    int step=img->widthStep;
    dst=cvCreateImage(cvSize(img->width,img->height),img->depth,1);
    dst->widthStep=img->widthStep;
    for(int i=1; i<img->height-1; i++)
        for(int j=1; j<img->width-1; j++) {
            if(data[(i-1)*step+j-1]>data[i*step+j])
                tmp[0]=1;
            else
                tmp[0]=0;
            if(data[i*step+(j-1)]>data[i*step+j])
                tmp[1]=1;
            else
                tmp[1]=0;
            if(data[(i+1)*step+(j-1)]>data[i*step+j])
                tmp[2]=1;
            else
                tmp[2]=0;
            if (data[(i+1)*step+j]>data[i*step+j])
                tmp[3]=1;
            else
                tmp[3]=0;
            if (data[(i+1)*step+(j+1)]>data[i*step+j])
                tmp[4]=1;
            else
                tmp[4]=0;
            if(data[i*step+(j+1)]>data[i*step+j])
                tmp[5]=1;
            else
                tmp[5]=0;
            if(data[(i-1)*step+(j+1)]>data[i*step+j])
                tmp[6]=1;
            else
                tmp[6]=0;
            if(data[(i-1)*step+j]>data[i*step+j])
                tmp[7]=1;
            else
                tmp[7]=0;
            for(k=0; k<=7; k++)
                sum+=abs(tmp[k]-tmp[k+1]);
            sum=sum+abs(tmp[7]-tmp[0]);
            if (sum<=2)
                s.val[0]=(tmp[0]*128+tmp[1]*64+tmp[2]*32+tmp[3]*16+tmp[4]*8+tmp[5]*4+tmp[6]*2+tmp[7]);
            else
                s.val[0]=59;
            cvSet2D(dst,i,j,s);
        }

    // CvFileStorage *fs = cvOpenFileStorage("iris.xml", NULL, CV_STORAGE_WRITE);
    //cvWrite(fs, "A", dst->imageData , cvAttrList(0, 0));
    storeImgMatToFile("dst",dst);
    cvShowImage("dst",dst);
    cvWaitKey(-1);


}
void fImgFeature::printImgMat(IplImage * img)
{
    for(int i = 0 ; i < img->height ; i ++) {
        for(int j = 0 ; j < img->width ; j ++) {
            for(int k = 0 ; k < img->nChannels ; k ++)
                cout <<  int(img->imageData[ i * (img->widthStep) + j * (img->nChannels) + k])  << "\t";
        }
        cout <<endl;
    }
}
void fImgFeature::storeImgMatToFile(string filename ,IplImage * img)
{
    ofstream fout(filename.c_str());
    for(int i = 0 ; i < img->height ; i ++) {
        for(int j = 0 ; j < img->width ; j ++) {
            for(int k = 0 ; k < img->nChannels ; k ++)
                fout <<  int(img->imageData[ i * (img->widthStep) + j * (img->nChannels) + k])  << "\t";
        }
        fout <<endl;
    }
    fout.close();
}

int fImgFeature::GetSift(string name ,CvMat * &samples )
{
    IplImage *img=cvLoadImage(name.c_str(),0);
    struct feature* features;
    int dims = SIFTN;
    int n = _sift_features(img, &features, SIFT_INTVLS/*3*/, SIFT_SIGMA/*1.6*/, SIFT_CONTR_THR/*0.04*/,
                           SIFT_CURV_THR/*10*/, SIFT_IMG_DBL/*1*/, SIFT_DESCR_WIDTH/*4*/, SIFT_DESCR_HIST_BINS/*8*/); //SIFTfeature提取

    //export_features("1.out", features, n);
    samples=cvCreateMat(n, dims, CV_32FC1);
    int k = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < dims; j++) {
            samples->data.fl[k++] = features[i].descr[j];
        }
    }

    //cvReleaseImage( &img );
    return n;

}
void fImgFeature::StoreImgSift(string imgname ,string filename)
{
    CvMat * imgMat  ;

    int n = GetSift(imgname , imgMat);
    int dims = SIFTN;
    ofstream fout(filename.c_str() );

    fout<< n << " " << SIFTN << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < dims; j++) {
           fout << imgMat->data.fl[i *(dims ) + j] << " " ;
           //imgMat->data.fl[i *(imgMat->step ) + j] ;
           //imgMat->step 是4*dims 因为一个double 占4个字节
        }
        fout << endl;
    }
    fout.close();
    cvReleaseMat(&imgMat);
}

void fImgFeature::getSiftFeatureFile(string filename , vector< vector<double > > & data )
{
    //chdir("/home/fuxiang/code-fuxiang90/cpp/opencv/opencv-start/feature");
    ifstream  fin(filename.c_str());
    if(fin == NULL) cout << filename << "open error" << endl;
    int n ;
    int m = SIFTN;
    fin>>n>>m;

    double d = 0.0;
    for(int i = 0  ; i < n ; i ++){
        vector<double > temp;
        for(int j = 0 ; j < m ; j ++){
                fin>>d;
                temp.push_back(d);
        }
        data.push_back(temp);
    }
    fin.close();
}
