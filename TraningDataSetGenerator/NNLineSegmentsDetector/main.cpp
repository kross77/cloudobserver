#include <iostream>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/timer.hpp>

// OpenCV
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#include "LSD.h"

using namespace std;
int linesFoundOnPicture;
int roiSize;

boost::timer ElementTimer;

boost::timer LSDTimer;
boost::timer NNGTimer;

double scale, sigma_scale,  quant, gradientAngleTolerance,  eps,  density_th, max_grad;
int n_bins;
image_int * region ;

IplImage* original;
IplImage* originalUnderLSD;
IplImage* composedLSDImage;

IplImage* originalUnderLSDColor;
IplImage* composedLSDImageColor;
IplImage* originalUnderNNlsdColor;

bool useWindows;
bool roundUp;
int normalyzeMatrix;
bool linesOnly;


void ProcessLSD(IplImage* source)
{
	int w = source->width;
	int h = source->height;
	image_double lsdImage;
	ntuple_list lsdOut;
	unsigned int x,y,i,j;
	lsdImage = new_image_double(w,h);

	for(x=0;x<w;x++){
		for(y=0;y<h;y++){
			double RealColor = cvGetReal2D(source, y, x);
			lsdImage->data[ x + y * lsdImage->xsize ] = RealColor;/* image(x,y) */
		}
	}

	lsdOut = LineSegmentDetection( lsdImage, 1,	1, 0.1,22.0, 0, 0.1,	1280, 60,NULL);//LineSegmentDetection(lsdImage, 1);
	for(i=0;i<lsdOut->size;i++)
	{
		CvPoint pt1 = { lsdOut->values[ i * lsdOut->dim + 0 ], lsdOut->values[ i * lsdOut->dim + 1]};
		CvPoint pt2 = { lsdOut->values[ i * lsdOut->dim + 2 ], lsdOut->values[ i * lsdOut->dim + 3 ] };
		cvLine(originalUnderLSDColor, pt1, pt2, CV_RGB(240, 50, 50), 1, CV_AA,0);
	}

	//	cvReleaseImage(&source);
	free_image_double(lsdImage);
	free_ntuple_list(lsdOut);
}

float NN1Y(IplImage* source,  float w0y00, float  w0y01, float  w0y02, float  w0y03, float  w0y04, float  w0y05, float  w0y06, float  w0y07, float  w0y10, float  w0y11, float  w0y12, float  w0y13, float  w0y14, float  w0y15, float  w0y16, float  w0y20, float  w0y21, float  w0y22, float  w0y23, float  w0y24, float  w0y25, float  w0y30, float  w0y31, float  w0y32, float  w0y33, float  w0y34, float  w0y40, float  w0y41, float  w0y42, float  w0y43, float  w0y50, float  w0y51, float  w0y52, float  w0y60, float  w0y61, float  w0y70, float  pn0, float  pn1, float  pn2, float  pn3, float  pn4, float  pn5, float  pn6, float  pn7)
{
	float z0y0  = w0y00*cvGetReal2D(source, 0 , 0 )+w0y01*cvGetReal2D(source, 0 , 1 )+w0y02*cvGetReal2D(source, 0 , 2 )+w0y03*cvGetReal2D(source, 0 , 3 )+w0y04*cvGetReal2D(source, 0 , 4 )+w0y05*cvGetReal2D(source, 0 , 5 )+w0y06*cvGetReal2D(source, 0 , 6 )+w0y07*cvGetReal2D(source, 0 , 7 );
	float z0y1  = w0y10*cvGetReal2D(source, 1 , 0 )+w0y11*cvGetReal2D(source, 1 , 1 )+w0y12*cvGetReal2D(source, 1 , 2 )+w0y13*cvGetReal2D(source, 1 , 3 )+w0y14*cvGetReal2D(source, 1 , 4 )+w0y15*cvGetReal2D(source, 1 , 5 )+w0y16*cvGetReal2D(source, 1 , 6 );
	float z0y2  = w0y20*cvGetReal2D(source, 2 , 0 )+w0y21*cvGetReal2D(source, 2 , 1 )+w0y22*cvGetReal2D(source, 2 , 2 )+w0y23*cvGetReal2D(source, 2 , 3 )+w0y24*cvGetReal2D(source, 2 , 4 )+w0y25*cvGetReal2D(source, 2 , 5 );
	float z0y3  = w0y30*cvGetReal2D(source, 3 , 0 )+w0y31*cvGetReal2D(source, 3 , 1 )+w0y32*cvGetReal2D(source, 3 , 2 )+w0y33*cvGetReal2D(source, 3 , 3 )+w0y34*cvGetReal2D(source, 3 , 4 );
	float z0y4  = w0y40*cvGetReal2D(source, 4 , 0 )+w0y41*cvGetReal2D(source, 4 , 1 )+w0y42*cvGetReal2D(source, 4 , 2 )+w0y43*cvGetReal2D(source, 4 , 3 );
	float z0y5  = w0y50*cvGetReal2D(source, 5 , 0 )+w0y51*cvGetReal2D(source, 5 , 1 )+w0y52*cvGetReal2D(source, 5 , 2 );
	float z0y6  = w0y60*cvGetReal2D(source, 6 , 0 )+w0y61*cvGetReal2D(source, 6 , 1 );
	float z0y7  = w0y70*cvGetReal2D(source, 7 , 0 );

	float Sz0y0  = 1/(1+exp(-z0y0));
	float Sz0y1  = 1/(1+exp(-z0y1));
	float Sz0y2  = 1/(1+exp(-z0y2));
	float Sz0y3  = 1/(1+exp(-z0y3));
	float Sz0y4  = 1/(1+exp(-z0y4));
	float Sz0y5  = 1/(1+exp(-z0y5));
	float Sz0y6  = 1/(1+exp(-z0y6));
	float Sz0y7  = 1/(1+exp(-z0y7));

	float y0hat  = pn0*Sz0y0+pn1*Sz0y1+pn2*Sz0y2+pn3*Sz0y3+pn4*Sz0y4+pn5*Sz0y5+pn6*Sz0y6+pn7*Sz0y7;
	return y0hat;
}

void ProcessNN(IplImage* source, int  currentX, int currentY) 
{


float nny1 = NN1Y(source,    0.99999997828423858,    0.99999997828423858,    0.99999995656847718,    0.99999993485271588,    0.99999991313695480,    0.99999989142119338,    0.99999986970543176,    0.99999986970543176,    0.99999999999985290,    0.99999999999990164,    0.99999999999985290,    0.99999999999970534,    0.99999999999960720,    0.99999999999955824,    0.99999999999950940,    1.01194310406623744,    1.00597155196736487,   1.01194310406623744,    1.01791465642812629,    1.02388620918453865,    1.02985776246698402,    1.35785659062579156,    1.11928436668597020,    1.23856960593371724,    1.35785659062579156,    1.59643929140530538,    33.8710540203341212,    7.11233060828376562,    7.11233060828376562,    19.5495983323157496,    1.00327154289493148,    1.00178447784441782,    1.00089223878569422,    1.00131298158196502,    1.00098473559129442,    1.27421592173992316 ,    0.256791895722095820,    0.256791894793337860,    0.256537797097353914,    0.251702497893972754,    -0.126316683575109778,    0.256779241804798886,    0.256787239960715786,    0.256067858147848548);
cout << nny1 << endl; // this is proof of idea fail=(

/*
	if (lsdOut->size == 0)
	{	}
	else
	{
		linesFoundOnPicture = linesFoundOnPicture +1;

		currentY =currentY*roiSize;
		currentX = currentX*roiSize;

		CvPoint pt1 = {currentX + lsdOut->values[ 0 * lsdOut->dim + 0 ], currentY + lsdOut->values[ 0 * lsdOut->dim + 1]};
		CvPoint pt2 = {currentX+ lsdOut->values[ 0 * lsdOut->dim + 2 ], currentY + lsdOut->values[ 0 * lsdOut->dim + 3 ] };
		cvLine(originalUnderNNlsdColor, pt1, pt2, CV_RGB(240, 50, 50), 1, CV_AA,0);

	}*/

}
void ProcessLSD(IplImage* source, int  currentX, int currentY)
{
	int w = source->width;
	int h = source->height;
	image_double lsdImage;
	ntuple_list lsdOut;
	unsigned int x,y,i,j;
	lsdImage = new_image_double(w,h);

	for(x=0;x<w;x++){
		for(y=0;y<h;y++){
			double RealColor = cvGetReal2D(source, y, x);
			lsdImage->data[ x + y * lsdImage->xsize ] = RealColor;/* image(x,y) */
		}
	}

	lsdOut = LineSegmentDetection( lsdImage, 1,	1, 0.1,22.0, 0, 0.1,	1280, 60,NULL);//LineSegmentDetection(lsdImage, 1);

	if (lsdOut->size == 0)
	{	}
	else
	{
		linesFoundOnPicture = linesFoundOnPicture +1;

			currentY =currentY*roiSize;
			currentX = currentX*roiSize;

			CvPoint pt1 = {currentX + lsdOut->values[ 0 * lsdOut->dim + 0 ], currentY + lsdOut->values[ 0 * lsdOut->dim + 1]};
			CvPoint pt2 = {currentX+ lsdOut->values[ 0 * lsdOut->dim + 2 ], currentY + lsdOut->values[ 0 * lsdOut->dim + 3 ] };
			cvLine(composedLSDImageColor, pt1, pt2, CV_RGB(240, 50, 50), 1, CV_AA,0);
		
	}

	//	cvReleaseImage(&source);
	free_image_double(lsdImage);
	free_ntuple_list(lsdOut);
}
void UseLSD(IplImage* destination)
{
	int w = destination->width;
	int h = destination->height;

	originalUnderLSD = cvCreateImage(cvSize(w, h),IPL_DEPTH_8U,1);
	cvCvtColor(destination,originalUnderLSD,CV_RGB2GRAY);

	linesFoundOnPicture = 0;
	cout << endl << "Progress:";
	for(int j = 1; j < originalUnderLSD->width/roiSize-1; j=j++) {
		cout << "." ;
		for(int i = 1; i < originalUnderLSD->height/roiSize-1; i=i++) {    

			cvSetImageROI(originalUnderLSD, cvRect(j*roiSize, i*roiSize,roiSize, roiSize));
			IplImage *cropSource = cvCreateImage(cvGetSize(originalUnderLSD), originalUnderLSD->depth, originalUnderLSD->nChannels);
			// cropped image
			// copy
			cvCopy(originalUnderLSD, cropSource, NULL);
			ProcessLSD(cropSource, j, i);
			ProcessNN(cropSource, j, i);
			// ... do what you want with your cropped image ...
			// always reset the ROI
			cvResetImageROI(originalUnderLSD);

		}
	}
	cout << endl;

		ProcessLSD(originalUnderLSD);	
		cout << endl<< "We wait for you to press any key on window with image" << endl;

		cvNamedWindow( "Original Image", CV_WINDOW_AUTOSIZE );
		cvShowImage( "Original Image", destination );

		cvNamedWindow( "original Under LSD", CV_WINDOW_AUTOSIZE );
		cvShowImage( "original Under LSD", originalUnderLSDColor );

		cvNamedWindow( "composed LSD'd Image", CV_WINDOW_AUTOSIZE );
		cvShowImage( "composed LSD'd Image", composedLSDImageColor );

		cvNamedWindow( "composed NNLSD Image", CV_WINDOW_AUTOSIZE );
		cvShowImage( "composed NNLSD Image", originalUnderNNlsdColor );

		cvWaitKey(0);

	cout << "LSD:line detector found " << linesFoundOnPicture << " lines on picture fragments." << endl;

}

void OpenDirectory(string p)
{
	if (boost::filesystem::is_directory(p))
	{
		for (boost::filesystem::directory_iterator itr(p); itr!=boost::filesystem::directory_iterator(); ++itr)
		{
			if (!boost::filesystem::is_directory(itr->path())){
				cout << "I am currently working on: " <<  itr->path().filename()  << " : " <<itr->path()<< ' '; 
				//file << itr->path() << " " << itr->path().filename() << ' ' << endl; // display filename only
				//		if (boost::filesystem::is_regular_file(itr->status())) cout << " [" << file_size(itr->path()) << ']';
				cout << '\n';
				original = cvLoadImage( itr->path().string().c_str() );
				 				
					cout << endl<< "Please wait..." << endl;

					composedLSDImageColor = cvCreateImage(cvGetSize(original), original->depth, original->nChannels);
					originalUnderLSDColor = cvCreateImage(cvGetSize(original), original->depth, original->nChannels);
					originalUnderNNlsdColor = cvCreateImage(cvGetSize(original), original->depth, original->nChannels);
					cvCopy(original, composedLSDImageColor, NULL);
					cvCopy(original, originalUnderLSDColor, NULL);
					cvCopy(original, originalUnderNNlsdColor, NULL);

				UseLSD(original);
				 
					string NameLSDOriginal;

					NameLSDOriginal += itr->path().filename();
					NameLSDOriginal += "_LSDOriginal.jpg";

					string NameCompositLSD;

					NameCompositLSD += itr->path().filename();
					NameCompositLSD += "_CompositLSD.jpg";

					string NameNNCompositLSD;

					NameNNCompositLSD += itr->path().filename();
					NameNNCompositLSD += "_NNCompositLSD.jpg";

					cvSaveImage(NameCompositLSD.c_str() ,composedLSDImageColor);
					cvSaveImage(NameLSDOriginal.c_str() ,originalUnderLSDColor);
					cvSaveImage(NameNNCompositLSD.c_str() ,originalUnderNNlsdColor);
	
			}
		}
	}
	else {cout << (boost::filesystem::exists(p) ? "Found: " : "Not found: ") << p << '\n'; cout << (boost::filesystem::exists(p) ? "Found: " : "Not found: ") << p << '\n';}
}



int main(int argc, char* argv[])
{
	for(int i = 1; i<argc; i=i+2){}

	cout << "Hello dear user." << endl << "I am a program that can take folder with images and perform on them line segments detection. I will use LSD and NNLSD for you to compare results." << endl;

	cout << endl << "Please input path to directory with images (for example C:/Temp/TestDir ) " << endl;
	string dn;
	cin >> dn;

	roiSize = 8;

	ElementTimer.restart();

	OpenDirectory(dn);
	//	file << "Time spent on tasks performing " << ElementTimer.elapsed() << endl;
	cout << endl << "Time spent on tasks performing " << ElementTimer.elapsed() << endl;
	cin.get();

}