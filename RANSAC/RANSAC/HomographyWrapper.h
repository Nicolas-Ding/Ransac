#pragma once

#include "Ransac.h"
#include "HomographyData.h"
#include "HomographyModel.h"

using namespace std;
using namespace cv;

class HomographyWrapper {
private : 
	vector<Mat> images;
	Mat constructed;
	Ransac<HomographyData, HomographyModel> ransac;
	int iterationNb; 
	int subSampleSize; 
	int allowedError;
	int corrBreakPoint; 

public :
	HomographyWrapper(vector<String> imagesNames, int iterNb, int subSampSize, int allowError, int corrBreakPt) {
		for (int i = 1; i < imagesNames.size(); i++) {
			images.push_back(imread(imagesNames.at(i), CV_LOAD_IMAGE_COLOR));
		}
		constructed = imread(imagesNames.at(0), CV_LOAD_IMAGE_COLOR);
		//ransac.setData(new HomographyData());
		iterationNb = iterNb;
		subSampleSize = subSampSize;
		allowedError = allowError;
		corrBreakPoint = corrBreakPt;
	};

	void run() {
		while (images.size() > 0) {
			Mat currentImage = images.front(); 
			/*imshow("constructed", constructed);
			waitKey();
			imshow("currrentImage",currentImage);
			waitKey();*/
			HomographyData* currentHomography = new HomographyData(constructed, currentImage);
			if (currentHomography->getDistsAt(10) > 150)
			{
				cout << "10th dist is " << currentHomography->getDistsAt(10) << endl;
				images.push_back(currentImage);
			}
			else
			{
				cout << "computing ..." << endl;
				ransac.setData(currentHomography);
				HomographyModel model = ransac.compute(iterationNb, subSampleSize, currentHomography->getMeanDist(), corrBreakPoint);
				constructed = currentHomography->getPanorama(model);
			}
			images.erase(images.begin());
		}
		imshow("Panorama", constructed);
		waitKey();
	}

};