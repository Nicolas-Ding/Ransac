#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <vector>

#include "Ransac.h"
#include "Point2D.h"
#include "Point2DData.h"
#include "Point2DModel.h"
#include "HomographyWrapper.h"
#include "HomographyData.h"

using namespace std;

const int iterationNb = 100;
const int subSampleSize = 4;
const int allowedError = 150;
const int corrBreakPoint = 100;

int main() {
	srand(time(NULL));
	
	/*Ransac<Point2DData, Point2DModel> ransac(new Point2DData()); 
	ransac.compute(100, 5, 0, 20);*/
	vector<String> imagesNames;
	/*imagesNames.push_back("Images/image0006.jpg");
	imagesNames.push_back("Images/image0007.jpg");
	imagesNames.push_back("Images/image0008.jpg");*/
	/*imagesNames.push_back("Images/pano2/pano1/IMG_0026.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0027.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0029.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0030.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0031.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0032.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0033.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0034.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0035.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0036.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0037.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0038.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0039.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0040.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0041.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0042.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0043.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0044.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0045.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0046.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0047.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0048.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0049.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0050.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0051.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0052.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0053.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0054.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0055.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0056.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0057.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0058.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0059.JPG");
	imagesNames.push_back("Images/pano2/pano1/IMG_0060.JPG");
*/

	imagesNames.push_back("Images/keble_a.JPG");
	imagesNames.push_back("Images/keble_b.JPG");
	imagesNames.push_back("Images/keble_c.JPG");

	HomographyWrapper homographyWrapper(imagesNames, iterationNb, subSampleSize, allowedError, corrBreakPoint);
	homographyWrapper.run();
	/*Ransac<HomographyData, HomographyModel> ransac(new HomographyData());
	ransac.compute(iterationNb, subSampleSize, allowedError);*/
	int t; 
	cin >> t;
}