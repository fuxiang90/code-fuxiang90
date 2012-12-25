#include "cv.h"
#include "highgui.h"
int main()
{
	IplImage* pImg;
	pImg = cvLoadImage("./cat.jpg", 1);

	cvNamedWindow("Image", 1);
	cvShowImage("Image", pImg);

	cvWaitKey(0);

	cvDestroyWindow("Image");
	cvReleaseImage(&pImg);

	return 0;
}
