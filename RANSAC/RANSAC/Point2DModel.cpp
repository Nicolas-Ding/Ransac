/*#include "Point2DModel.h"

using namespace std;

void Point2DModel::show(Point2DData data)
{
	//TODO : recadrer la zone pour voir tous les points de manière centrée
	vector<Point2D> points = data.getPoints();
	const int WIDTH = 500; 
	const int HEIGHT = 500;
	Mat image(WIDTH, WIDTH, CV_32F, 1);
	for (auto i = points.begin(); i < points.end(); i++) {
		circle(image, Point(i->getX(), HEIGHT - i->getY()), 3, Scalar(0, 0, 255), -1);
	}
	line(image, Point(0, HEIGHT - b), Point(WIDTH, HEIGHT - a*WIDTH + b), Scalar(0, 0, 255), 1);
	imshow("Regression", image);
	waitKey();
}*/