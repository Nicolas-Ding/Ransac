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
	// On a besoin d'un modèle
	// 1) Qui puisse être calculé à partir de data points
	// 2) Qui puisse décider si un point rentre ou pas dans le modèle
	
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
