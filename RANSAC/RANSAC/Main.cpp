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

#include "HomographyData.h"

using namespace std;

const int iterationNb = 100;
const int subSampleSize = 5;
const int allowedError = 150;

int main() {
	srand(time(NULL));
	
	/*Ransac<Point2DData, Point2DModel> ransac(new Point2DData()); 
	ransac.compute(100, 5, 0);*/
	/*HomographyData test = HomographyData(); 
	HomographyModel mod = test.computeModel(subSampleSize);
	test.show(mod);*/
	Ransac<HomographyData, HomographyModel> ransac(new HomographyData);
	ransac.compute(iterationNb, subSampleSize, allowedError);
	int t; 
	cin >> t;
}