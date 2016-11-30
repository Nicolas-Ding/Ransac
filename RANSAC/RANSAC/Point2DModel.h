#pragma once

#include "Model.h"
#include "Point2D.h"

class Point2DModel :
	public Model<Point2D>
{
private : 
	//We assume we try to find a line of equation y = a*x + b
	double a;
	double b;

public :
	Point2DModel(vector<Point2D> dataPoints) : Model<Point2D>(dataPoints)
	{

	};

	double getA() { return a; }
	double getB() { return b; }
	void setA(double a0) { a = a0; }
	void setB(double b0) { b = b0; }

	void computeParameters() {
		a = 0;
		b = 0;
		for (unsigned int i = 0; i < points.size(); i++) {
			for (unsigned int j = 0; j < points.size(); j++) {
				if (i != j) {
					a += (points.at(j).getY() - points.at(i).getY()) / (points.at(j).getX() - points.at(i).getX());
				}
			}
		}
		a /= points.size() * (points.size() - 1) / 2;
		for (unsigned int i = 0; i < points.size(); i++) {
			b += points.at(i).getX() * a - points.at(i).getY();
		}
		b /= points.size();
	}
	
	bool isOutlier(Point2D pt, double allowedErr) const {
		return (abs(pt.getX() * a - pt.getY()) > allowedErr);
	}

	friend ostream & operator<<(ostream & flux, const Point2DModel r)
	{

		flux << "result model parameters are " << r.a << " * x + " << r.b;
		return flux;
	}

	void printClass() {
		cout << "Point2DModel" << endl;
	}

	~Point2DModel() {} ;
};

