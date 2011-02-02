#include <iostream>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

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
ofstream file;
IplImage* original;
IplImage* originalUnderLSD;
IplImage* composedLSDImage;

IplImage* originalUnderLSDColor;
IplImage* composedLSDImageColor;

bool useWindows;


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
			file << RealColor << " ";
		}
		file << endl;
	}file << endl;

	lsdOut = LineSegmentDetection( lsdImage, 1,	1, 0.1,22.0, 0, 0.1,	1280, 60,NULL);//LineSegmentDetection(lsdImage, 1);

	if (lsdOut->size == 0)
	{
		file << "0 0 0 0";

	}
	else
	{
		linesFoundOnPicture = linesFoundOnPicture +1;
		file << lsdOut->values[ 0 * lsdOut->dim + 0 ] << " " <<  lsdOut->values[ 0 * lsdOut->dim + 1] << " ";
		file << lsdOut->values[ 0 * lsdOut->dim + 2 ] << " " << lsdOut->values[ 0 * lsdOut->dim + 3 ] << " ";

		if(useWindows){
			currentY =currentY*roiSize;
			currentX = currentX*roiSize;

			CvPoint pt1 = {currentX + lsdOut->values[ 0 * lsdOut->dim + 0 ], currentY + lsdOut->values[ 0 * lsdOut->dim + 1]};
			CvPoint pt2 = {currentX+ lsdOut->values[ 0 * lsdOut->dim + 2 ], currentY + lsdOut->values[ 0 * lsdOut->dim + 3 ] };
			cvLine(composedLSDImageColor, pt1, pt2, CV_RGB(240, 50, 50), 1, CV_AA,0);
		}

	}
	file << endl;
	file << endl;
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
	if(useWindows){
		composedLSDImage = cvCreateImage(cvSize(w, h),IPL_DEPTH_8U,1);

		cvCopy(originalUnderLSD, composedLSDImage, NULL);
	}

	linesFoundOnPicture = 0;
	for(int j = 1; j < originalUnderLSD->width/roiSize-1; j=j++) {
		for(int i = 1; i < originalUnderLSD->height/roiSize-1; i=i++) {    
			cvSetImageROI(originalUnderLSD, cvRect(j*roiSize, i*roiSize,roiSize, roiSize));
			IplImage *cropSource = cvCreateImage(cvGetSize(originalUnderLSD), originalUnderLSD->depth, originalUnderLSD->nChannels);
			// cropped image
			// copy
			cvCopy(originalUnderLSD, cropSource, NULL);
			ProcessLSD(cropSource, j, i);
			// ... do what you want with your cropped image ...
			// always reset the ROI
			cvResetImageROI(originalUnderLSD);

		}
	}
	if(useWindows){
		ProcessLSD(originalUnderLSD);
		cvNamedWindow( "original Under LSD", CV_WINDOW_AUTOSIZE );
		cvShowImage( "original Under LSD", originalUnderLSDColor );

		cvNamedWindow( "composed LSD'd Image", CV_WINDOW_AUTOSIZE );
		cvShowImage( "composed LSD'd Image", composedLSDImageColor );
		cvWaitKey(0);
	}

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
				if(useWindows){	
					cvNamedWindow( "Original Image", CV_WINDOW_AUTOSIZE );
					cvShowImage( "Original Image", original );

					composedLSDImageColor = cvCreateImage(cvGetSize(original), original->depth, original->nChannels);
					originalUnderLSDColor = cvCreateImage(cvGetSize(original), original->depth, original->nChannels);

					cvCopy(original, composedLSDImageColor, NULL);
					cvCopy(original, originalUnderLSDColor, NULL);
				}			
				UseLSD(original);
				//cvReleaseImage( &original );
				//cvDestroyWindow( "CurrentImage" );

			}
		}
	}
	else {cout << (boost::filesystem::exists(p) ? "Found: " : "Not found: ") << p << '\n'; file << (boost::filesystem::exists(p) ? "Found: " : "Not found: ") << p << '\n';}
}



int main()
{
	cout << "Hello dear user." << endl << "I am a program that can take folder with images and perform on tham slysing into peaces of desired size and perform filtering (line searching) algorithm on each peace. This can and will take some time. Data would be outputed into CSV text file." << endl;

	cout << "Please input desired output file name (for example GeneratedTrainingDataSet.txt  )" << endl;
	string fn;
	cin >> fn;
	file.open (fn.c_str());
	file.clear();
	cout << endl << "Please input path to directory with images (for example C:/Temp/TestDir ) " << endl;
	string dn;
	cin >> dn;
	cout << endl << "Please input slices length (for example 10). Slices are square B&W image peaces"<< endl ;
	string rs;
	cin >> rs;	
	roiSize = atoi(rs.c_str());
	cout << endl << "Please input 1 to use preview mode (you will have to press any key on window with image / or images from time to time) or input 0 for silent mode (best for Training Data Set Generation)" << endl;
	string model;
	cin >> model;	
	useWindows = atoi(model.c_str());

	ElementTimer.restart();

	OpenDirectory(dn);
	file << "Time spent on tasks performing" << ElementTimer.elapsed() << endl;
	cout << endl << "Time spent on tasks performing" << ElementTimer.elapsed() << endl;

	file.close();
	cin.get();

}