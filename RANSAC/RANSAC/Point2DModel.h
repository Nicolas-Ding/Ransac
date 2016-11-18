#pragma once

#include "Model.h"
#include "Point2D.h"

class Point2DModel :
	public Model<Point2D>
{
public:
	Point2DModel(vector<Point2D> dataPoints) : Model<Point2D>(dataPoints)
	{

	};
	~Point2DModel();
};

