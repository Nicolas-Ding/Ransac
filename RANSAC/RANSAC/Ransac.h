#ifndef HEADER_RANSAC
#define HEADER_RANSAC

#include <iostream>
#include <vector>
#include "Model.h"

using namespace std;

template <class T>
class Ransac
{
private:
	Model<T> input;

public:
	Ransac(Model<T> points)
	{
		input = points;
	}
	
	Model<T> getInput() const
	{
		return input;
	}

	//Notes : 
	// On a besoin d'un mod�le
	// 1) Qui puisse �tre calcul� � partir de data points
	// 2) Qui puisse d�cider si un point rentre ou pas dans le mod�le
	
	Model<T> getSubSample(int k) const
	{
		return input.getSubSample(k);
	}

	void compute(int iterationNb, int subSampleSize)
	{

	}


	friend ostream & operator<<(ostream & flux, const Ransac<T> r)
	{
		flux << r.getInput() << endl;
		return flux;
	}
};

#endif
