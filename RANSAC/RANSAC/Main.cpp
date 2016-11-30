#include <iostream>
#include <string>
#include <time.h>
#include "Model.h"
#include "Ransac.h"
#include "Point2D.h"
#include "Point2DModel.h"

using namespace std;

int main() {
	srand(time(NULL));
	vector<Point2D> input;
	for (int i = 0; i < 100; i++) {
		input.push_back(Point2D(i,i));
	}

	Point2DModel* test = new Point2DModel(input);
	test->printClass();
	Ransac<Point2D> ransac(test);
	ransac.compute(10,30, 2);
	int t;
	cin >> t;
}