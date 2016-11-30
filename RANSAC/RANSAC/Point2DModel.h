#pragma once

#include "Model.h"
#include "Point2D.h"

class Point2DModel :
	public Model<Point2D>
{
private:
	//We assume we try to find a line of equation y = a*x + b
	double a;
	double b;

public:
	Point2DModel(vector<Point2D> dataPoints) : Model<Point2D>(dataPoints)
	{

	};

	double getA() { return a; }
	double getB() { return b; }
	void setA(double a0) { a = a0; }
	void setB(double b0) { b = b0; }
	
	
	Point2DModel* getSubSample(int k) const
	{
		set<int> indexes;
		vector<Point2D> choices;
		int max_index = points.size();
		while (indexes.size() < min(k, max_index))
		{
			int random_index = rand() % max_index;
			if (indexes.find(random_index) == indexes.end())
			{
				choices.push_back(points[random_index]);
				indexes.insert(random_index);
			}
		}
		return new Point2DModel(choices);
	}

	void computeParameters() {
		a = 0.;
		b = 0.;
		for (unsigned int i = 0; i < points.size(); i++) {
			for (unsigned int j = i + 1; j < points.size(); j++) {
				a += (points.at(j).getY() - points.at(i).getY()) / (points.at(j).getX() - points.at(i).getX());
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
		cout << "Point2DModel : Parameters are a = " << a << ", b= " << b << endl;
	}

	~Point2DModel() {} ;
};

