#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Point2D.h"

using namespace cv;
using namespace std;

class Point2DModel
{
private:
	//We assume we try to find a line of equation y = a*x + b
	double a;
	double b;

public:
	Point2DModel()
	{
		a = 0;
		b = 0;
	}

	Point2DModel(int a, int b)
	{
		this->a = a;
		this->b = b;
	};

	double getA() { return a; }
	double getB() { return b; }
	void setA(double a0) { a = a0; }
	void setB(double b0) { b = b0; }
	
	bool isInlier(Point2D pt, double allowedErr) const {
		return (abs(pt.getX() * a + b - pt.getY()) <= allowedErr);
	} 

	int countInliers(vector<Point2D> points, int allowedError) {
		int res = 0;
		for (auto i = points.begin(); i < points.end(); i++)
			res += (isInlier(*i, allowedError) ? 1 : 0);
		return res;
	}

	void printClass() { 
		cout << "Point2DModel : Parameters are a = " << a << ", b= " << b << endl;
	} 
	 
	~Point2DModel() {} ;
};

