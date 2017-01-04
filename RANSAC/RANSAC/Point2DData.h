#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Point2DModel.h"

using namespace cv;

class Point2DData
{
private:
	vector<Point2D> points;

public:
	Point2DData()
	{
		for (int i = 0; i < 50; i++) {
			//points.push_back(Point2D(10 * i + rand() % 20 - 10, 10 * i + rand() % 20 - 10));
			 points.push_back(Point2D(10 * i , 10 * i));
		}
		for (int i = 0; i < 20; i++) {
			int a = rand() % 500;
			points.push_back(Point2D(a, rand() % a));
		}
	}

	Point2DData(vector<Point2D> dataPoints)
	{
		points = dataPoints;
	};

	vector<Point2D> getPoints() const
	{
		return points;
	}

	vector<Point2D> getInOutliersData() const
	{
		return points;
	}

	auto begin() {
		return points.begin();
	}

	auto end() {
		return points.end();
	}

	void show(Point2DModel model) {
		double a = model.getA();
		double b = model.getB();
		const int WIDTH = 500;
		const int HEIGHT = 500;
		Mat image(WIDTH, WIDTH, CV_32F, 1);
		for (auto i = points.begin(); i < points.end(); i++) {
			circle(image, Point(i->getX(), HEIGHT - i->getY()), 3, Scalar(0, 0, 255), -1);
		}
		line(image, Point(0, HEIGHT - b), Point(WIDTH, HEIGHT - a*WIDTH + b), Scalar(0, 0, 255), 1);
		imshow("Regression", image);
		waitKey();
	}

	Point2DModel* computeModel(int k) {
		vector<Point2D> subSample = RansacUtils::getSubVector<Point2D> (points,k);
		double sumX = 0;
		double sumY = 0;
		double sumXY = 0;
		double sumX2 = 0;
		for (auto i = subSample.begin(); i < subSample.end(); i++) {
			sumX += i->getX();
			sumY += i->getY();
			sumXY += i->getX() * i->getY();
			sumX2 += i->getX() * i->getX();
		}
		double a = (subSample.size() * sumXY - sumX * sumY) / (subSample.size() * sumX2 - sumX * sumX);
		double b = (sumY - a * sumX) / subSample.size();
		return new Point2DModel(a, b);
	}

	friend ostream & operator<<(ostream & flux, const Point2DData r)
	{

		flux << "Point2DData : Number of points " << r.points.size() << endl;
		return flux;
	}

	void printClass() {
		cout << "Point2DData : Number of points " << points.size() << endl;
	}

	~Point2DData() {};
};

