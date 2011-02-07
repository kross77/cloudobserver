#include <iostream>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <algorithm>

#include <boost/filesystem.hpp>
#include <boost/timer.hpp>

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#include "LSD.h"

using namespace std;
int linesFoundOnPicture;
int roiSize;

boost::timer ElementTimer;

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

void ProcessNN( IplImage * cropSource, int j, int i ) 
{
	//throw std::exception("The method or operation is not implemented.");
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
	//roundUp = 1;
	for(int i = 1; i<argc; i=i+2){
		//	if(string(argv[i]) == "-roiSize" ){roiSize = atoi(argv[i+1]);} 
		//	if(string(argv[i]) == "-useWindows" ) {useWindows = atoi(argv[i+1]);} 
		//	if(string(argv[i]) == "-doRound" ) {roundUp = atoi(argv[i+1]);} 
		//	if(string(argv[i]) == "-normtype" ) {normalyzeMatrix = atoi(argv[i+1]);} 
		//	if(string(argv[i]) == "-linesOnly" ) {linesOnly = atoi(argv[i+1]);} 
		// example -server http://127.0.0.1:4773 -nickname vasia  // if you change w and h do not forget about stream bit rate!!!
	}

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