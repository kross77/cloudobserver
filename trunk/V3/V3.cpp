// V3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>


using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	char path[256];

	cout << "Hello! Input file path" << endl;

	cin.getline(path, 265);
	cout << path << endl;
	IplImage *img = cvLoadImage(path);
	cvNamedWindow("Image:",1);
	cvShowImage("Image:",img);

	cvWaitKey();
	cvDestroyWindow("Image:");
	cvReleaseImage(&img);

	return 0;
}

