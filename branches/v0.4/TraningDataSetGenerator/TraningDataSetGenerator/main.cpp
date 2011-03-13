#include <iostream>

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

#include <algorithm>
#include <math.h>

#include <boost/filesystem.hpp>
#include <boost/timer.hpp>

// OpenCV
#include <opencv/cv.h>
#include <opencv/cxcore.h>
#include <opencv/highgui.h>

#include "LSD.h"

using namespace std;
int linesFoundInGeneral;
int desiredNumOfLines;
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
bool roundUp;
int normalyzeMatrix;
bool linesOnly;
bool anglesOnly;

float gmax;
float gmin;

float min1;
float max2;
float min3;
float max4;
float min5;
float max6;
float min7;
float max8;

int round(double a) {
	return int(a + 0.5);
}
float angle(double Ax,double  Ay,double  Bx,double  By)
{
	double ly = (By-Ay);
	double lx = (Bx-Ax);
	return atan2 ( ly, lx ) ;
}

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
		}
	}

	lsdOut = LineSegmentDetection( lsdImage, 1,	1, 0.1,22.0, 0, 0.1,	1280, 60,NULL);//LineSegmentDetection(lsdImage, 1);

	if (lsdOut->size == 0)
	{
		if(!linesOnly)
		{
			if(normalyzeMatrix <= 1){
				if(normalyzeMatrix == 0){ // print matrix in form of bool values
					cvNormalize(source,source,1,0,CV_MINMAX );
				}
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){

						double RealColor = cvGetReal2D(source, y, x);
						file << RealColor << " ";
					}
					file << endl;
				}file << endl;
			}
			if(normalyzeMatrix==2){
				int maxVal;
				int minVal;
				int wh = w*h;
				int values[1000];
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){
						double RealColor = cvGetReal2D(source, y, x);
						values[x*h + y] = RealColor; 
					}
				}
				minVal = *min_element(values,(values+wh));
				maxVal = *max_element(values,(values+wh));
				float dif = maxVal - minVal;
				float fminVal;
				fminVal = minVal;
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){
						float rc = cvGetReal2D(source, y, x);
						float normRealColor;
						if(minVal== maxVal)
						{
							normRealColor = 0;
						}
						else{
							normRealColor	=(rc - fminVal) / dif;
						}
						file << normRealColor << " ";
					}
					file << endl;
				}file << endl;
			}
			file << "-1";
			file << endl;
		}	
	}
	else
	{
		float an = angle((lsdOut->values[ 0 * lsdOut->dim + 0 ]) ,  (lsdOut->values[ 0 * lsdOut->dim + 1]) , (lsdOut->values[ 0 * lsdOut->dim + 2 ]) , (lsdOut->values[ 0 * lsdOut->dim + 3 ])) ;
		if ((an <= max2) && (an >= min1))
		{
			linesFoundInGeneral = linesFoundInGeneral +1;
			if(normalyzeMatrix <= 1){
				if(normalyzeMatrix == 0){ // print matrix in form of bool values
					cvNormalize(source,source,1,0,CV_MINMAX );
				}
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){

						double RealColor = cvGetReal2D(source, y, x);
						file << RealColor << " ";
					}file << endl;
				}file << endl;
			}
			if(normalyzeMatrix==2){
				int maxVal;
				int minVal;
				int wh = w*h;
				int values[1000];
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){
						double RealColor = cvGetReal2D(source, y, x);
						values[x*h + y] = RealColor; 
					}
				}
				minVal = *min_element(values,(values+wh));
				maxVal = *max_element(values,(values+wh));
				float dif = maxVal - minVal;
				float fminVal;
				fminVal = minVal;
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){
						float rc = cvGetReal2D(source, y, x);
						float normRealColor;
						if(minVal== maxVal)
						{
							normRealColor = 1;
						}
						else{
							normRealColor	=(rc - fminVal) / dif;
						}
						file << normRealColor << " ";
					}
					file << endl;
				}file << endl;
			}

			file <<  "1";
			file << endl;
		}
		else if ((an <= max4) && (an >= min3))
		{
			linesFoundInGeneral = linesFoundInGeneral +1;
			if(normalyzeMatrix <= 1){
				if(normalyzeMatrix == 0){ // print matrix in form of bool values
					cvNormalize(source,source,1,0,CV_MINMAX );
				}
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){

						double RealColor = cvGetReal2D(source, y, x);
						file << RealColor << " ";
					}file << endl;
				}file << endl;
			}
			if(normalyzeMatrix==2){
				int maxVal;
				int minVal;
				int wh = w*h;
				int values[1000];
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){
						double RealColor = cvGetReal2D(source, y, x);
						values[x*h + y] = RealColor; 
					}
				}
				minVal = *min_element(values,(values+wh));
				maxVal = *max_element(values,(values+wh));
				float dif = maxVal - minVal;
				float fminVal;
				fminVal = minVal;
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){
						float rc = cvGetReal2D(source, y, x);
						float normRealColor;
						if(minVal== maxVal)
						{
							normRealColor = 1;
						}
						else{
							normRealColor	=(rc - fminVal) / dif;
						}
						file << normRealColor << " ";
					}
					file << endl;
				}file << endl;
			}

			file <<  "1";
			file << endl;
		}
		else if ((an <= max6) && (an >= min5))
		{
			linesFoundInGeneral = linesFoundInGeneral +1;
			if(normalyzeMatrix <= 1){
				if(normalyzeMatrix == 0){ // print matrix in form of bool values
					cvNormalize(source,source,1,0,CV_MINMAX );
				}
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){

						double RealColor = cvGetReal2D(source, y, x);
						file << RealColor << " ";
					}file << endl;
				}file << endl;
			}
			if(normalyzeMatrix==2){
				int maxVal;
				int minVal;
				int wh = w*h;
				int values[1000];
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){
						double RealColor = cvGetReal2D(source, y, x);
						values[x*h + y] = RealColor; 
					}
				}
				minVal = *min_element(values,(values+wh));
				maxVal = *max_element(values,(values+wh));
				float dif = maxVal - minVal;
				float fminVal;
				fminVal = minVal;
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){
						float rc = cvGetReal2D(source, y, x);
						float normRealColor;
						if(minVal== maxVal)
						{
							normRealColor = 1;
						}
						else{
							normRealColor	=(rc - fminVal) / dif;
						}
						file << normRealColor << " ";
					}
					file << endl;
				}file << endl;
			}

			file <<  "1";
			file << endl;
		}
		else if ((an <= max8) && (an >= min7))
		{
			linesFoundInGeneral = linesFoundInGeneral +1;
			if(normalyzeMatrix <= 1){
				if(normalyzeMatrix == 0){ // print matrix in form of bool values
					cvNormalize(source,source,1,0,CV_MINMAX );
				}
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){

						double RealColor = cvGetReal2D(source, y, x);
						file << RealColor << " ";
					}file << endl;
				}file << endl;
			}
			if(normalyzeMatrix==2){
				int maxVal;
				int minVal;
				int wh = w*h;
				int values[1000];
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){
						double RealColor = cvGetReal2D(source, y, x);
						values[x*h + y] = RealColor; 
					}
				}
				minVal = *min_element(values,(values+wh));
				maxVal = *max_element(values,(values+wh));
				float dif = maxVal - minVal;
				float fminVal;
				fminVal = minVal;
				for(x=0;x<w;x++){
					for(y=0;y<h;y++){
						float rc = cvGetReal2D(source, y, x);
						float normRealColor;
						if(minVal== maxVal)
						{
							normRealColor = 1;
						}
						else{
							normRealColor	=(rc - fminVal) / dif;
						}
						file << normRealColor << " ";
					}
					file << endl;
				}file << endl;
			}

			file <<  "1";
			file << endl;
		}
		else
		{
			if(!anglesOnly)
			{
				if(normalyzeMatrix <= 1){
					if(normalyzeMatrix == 0){ // print matrix in form of bool values
						cvNormalize(source,source,1,0,CV_MINMAX );
					}
					for(x=0;x<w;x++){
						for(y=0;y<h;y++){

							double RealColor = cvGetReal2D(source, y, x);
							file << RealColor << " ";
						}file << endl;
					}file << endl;
				}
				if(normalyzeMatrix==2){
					int maxVal;
					int minVal;
					int wh = w*h;
					int values[1000];
					for(x=0;x<w;x++){
						for(y=0;y<h;y++){
							double RealColor = cvGetReal2D(source, y, x);
							values[x*h + y] = RealColor; 
						}
					}
					minVal = *min_element(values,(values+wh));
					maxVal = *max_element(values,(values+wh));
					float dif = maxVal - minVal;
					float fminVal;
					fminVal = minVal;
					for(x=0;x<w;x++){
						for(y=0;y<h;y++){
							float rc = cvGetReal2D(source, y, x);
							float normRealColor;
							if(minVal== maxVal)
							{
								normRealColor = 1;
							}
							else{
								normRealColor	=(rc - fminVal) / dif;
							}
							file << normRealColor << " ";
						}
						file << endl;
					}file << endl;
				}

				file << "-1";
				file << endl;
			}
		}
		
		if(useWindows){
			currentY =currentY*roiSize;
			currentX = currentX*roiSize;
			CvPoint pt1 = {currentX + lsdOut->values[ 0 * lsdOut->dim + 0 ], currentY + lsdOut->values[ 0 * lsdOut->dim + 1]};
			CvPoint pt2 = {currentX+ lsdOut->values[ 0 * lsdOut->dim + 2 ], currentY + lsdOut->values[ 0 * lsdOut->dim + 3 ] };
			cvLine(composedLSDImageColor, pt1, pt2, CV_RGB(240, 50, 50), 1, CV_AA,0);
		}
	}
//	file << endl;
//	file << endl;
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

	
	cout << endl << "Progress:";
	for(int j = 1; j < originalUnderLSD->width/roiSize-1; j=j++) {
		cout << "." ;
		for(int i = 1; i < originalUnderLSD->height/roiSize-1; i=i++) {  
			if(!(linesFoundInGeneral > desiredNumOfLines))
			{
				cvSetImageROI(originalUnderLSD, cvRect(j*roiSize, i*roiSize,roiSize, roiSize));
				IplImage *cropSource = cvCreateImage(cvGetSize(originalUnderLSD), originalUnderLSD->depth, originalUnderLSD->nChannels);
				cvCopy(originalUnderLSD, cropSource, NULL);
				ProcessLSD(cropSource, j, i);
				cvResetImageROI(originalUnderLSD);
			}
		}
	}
	cout << endl;
	if(useWindows){
		ProcessLSD(originalUnderLSD);

		cvNamedWindow( "Original Image", CV_WINDOW_AUTOSIZE );
		cvShowImage( "Original Image", destination );
		cout << endl<< "We wait for you to press any key on window with image" << endl;
		cvNamedWindow( "original Under LSD", CV_WINDOW_AUTOSIZE );
		cvShowImage( "original Under LSD", originalUnderLSDColor );

		cvNamedWindow( "composed LSD'd Image", CV_WINDOW_AUTOSIZE );
		cvShowImage( "composed LSD'd Image", composedLSDImageColor );

		cvWaitKey(0);
	}

	cout << "LSD:line detector found " << linesFoundInGeneral << " desired lines." << endl;

}

void OpenDirectory(string p)
{

	if (boost::filesystem::is_directory(p))
	{

		for (boost::filesystem::directory_iterator itr(p); itr!=boost::filesystem::directory_iterator(); ++itr)
		{

			if (!boost::filesystem::is_directory(itr->path())){
				if(!(linesFoundInGeneral > desiredNumOfLines))
				{
				cout << "I am currently working on: " <<  itr->path().filename()  << " : " <<itr->path()<< ' '; 
				cout << '\n';
				original = cvLoadImage( itr->path().string().c_str() );
				if(useWindows){					
					cout << endl<< "Please wait..." << endl;


					composedLSDImageColor = cvCreateImage(cvGetSize(original), original->depth, original->nChannels);
					originalUnderLSDColor = cvCreateImage(cvGetSize(original), original->depth, original->nChannels);

					cvCopy(original, composedLSDImageColor, NULL);
					cvCopy(original, originalUnderLSDColor, NULL);
				}			
				UseLSD(original);
				if(useWindows){	
					string NameLSDOriginal;

					NameLSDOriginal += itr->path().filename();
					NameLSDOriginal += "_LSDOriginal.jpg";
					string NameCompositLSD;

					NameCompositLSD += itr->path().filename();
					NameCompositLSD += "_CompositLSD.jpg";
					cvSaveImage(NameCompositLSD.c_str() ,composedLSDImageColor);
					cvSaveImage(NameLSDOriginal.c_str() ,originalUnderLSDColor);
				}
				}
			}
		}
	}
	else {cout << (boost::filesystem::exists(p) ? "Found: " : "Not found: ") << p << '\n'; file << (boost::filesystem::exists(p) ? "Found: " : "Not found: ") << p << '\n';}
}



int main(int argc, char* argv[])
{
	linesFoundInGeneral = 0;
	for(int i = 1; i<argc; i=i+2){}

	cout << "Hello dear user." << endl << "I am a program that can take folder with images and perform on them slicing into peaces of desired size and perform filtering (line searching) algorithm on each peace. This can and will take some time. Data would be outputted into CSV text file." << endl;

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

	roundUp = 0;

	normalyzeMatrix = 2;

	cout << endl << "Please input 1 to print only images on which lines were found. Input 0 for all found images." << endl;
	string doLines;
	cin >> doLines;	
	linesOnly = atoi(doLines.c_str());

	cout << endl << "angle 1 (bottom):" << endl;
	string min1;
	cin >> min1;	
	min1 = atof(min1.c_str());   
	cout << endl << "angle 2 (top):" << endl;
	string max2;
	cin >> max2;	
	max2 = atof(max2.c_str());
	cout << endl << "angle 3 (bottom):" << endl;
	string min3;
	cin >> min3;	
	min3 = atof(min3.c_str());   
	cout << endl << "angle 4 (top):" << endl;
	string max4;
	cin >> max4;	
	max4 = atof(max4.c_str());
	cout << endl << "angle 5 (bottom):" << endl;
	string min5;
	cin >> min5;	
	min5 = atof(min5.c_str());   
	cout << endl << "angle 6 (top):" << endl;
	string max6;
	cin >> max6;	
	max6 = atof(max6.c_str());
	cout << endl << "angle 7 (bottom):" << endl;
	string min7;
	cin >> min7;	
	min7 = atof(min7.c_str());   
	cout << endl << "angle 8 (top):" << endl;
	string max8;
	cin >> max8;	
	max8 = atof(max8.c_str());

	cout << endl << "Please input 1 to print only images on which lines were found with correct angle. Input 0 for all found images to be printed." << endl;
	string doAngles;
	cin >> doAngles;	
	anglesOnly = atoi(doAngles.c_str());

	cout << endl << "Please input Desired Num Of Lines to be found and placed into file with learning pairs." << endl;
	string doDesiredNumOfLines;
	cin >> doDesiredNumOfLines;	
	desiredNumOfLines = atoi(doDesiredNumOfLines.c_str());

	ElementTimer.restart();

	OpenDirectory(dn);
	cout << endl << "Time spent on tasks performing " << ElementTimer.elapsed() << endl;
	cin.get();
	file.close();
	return 0;

}