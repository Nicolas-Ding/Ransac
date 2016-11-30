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
	Model<T>* input;

public:
	Ransac(Model<T>* points)
	{
		input = points;
	}
	
	Model<T> getInput() const
	{
		return *input;
	}

	void compute(int iterationNb, int subSampleSize, double allowedError)
	{
		int bestCorr = -1;
		Model<T>* bestModel = NULL;
		for (int i = 0; i < iterationNb; i++) {
			Model<T>* subSample = input->getSubSample(subSampleSize);
			subSample->computeParameters();
			int corr = input->testCorrelation(*subSample, allowedError);
			if (corr > bestCorr) {
				bestCorr = corr;
				bestModel = subSample;
			}
		}
		bestModel->printClass();
	}


	friend ostream & operator<<(ostream & flux, const Ransac<T> r)
	{
		flux << r.getInput() << endl;
		return flux;
	}
};

#endif
