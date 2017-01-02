#pragma once

#include <iostream> 
#include <vector>
#include <set>
#include "RansacUtils.h"


using namespace std;

template <class DataClass, class ModelClass>
class Ransac
{
private:
	DataClass* data;

public:
	Ransac(DataClass* m)
	{
		data = m;
	}

	DataClass* getData() const
	{
		return data;
	}

	void compute(int iterationNb, int subSampleSize, double allowedError)
	{
		int bestCorr = NULL;
		ModelClass* bestModel = NULL;
		for (int i = 0; i < iterationNb; i++) {
			ModelClass* model = data->computeModel(subSampleSize);
			int corr = testCorrelation(model, data, allowedError);
			cout << "Corr --> " << corr << endl;
			if (bestCorr == NULL || corr > bestCorr) {
				bestCorr = corr;
				bestModel = model;
			}
		}
		bestModel->printClass();
		cout << "correlation is " << bestCorr << endl;
		data->show(*bestModel);
	}

	int testCorrelation(ModelClass* testingModel, DataClass* testingData, double allowedError) {
		int res = 0;
		/*for (auto i = testingData->begin(); i < testingData->end(); i++)
			res += (testingModel->isOutlier(*i, allowedError) ? 0 : 1);*/
		res = testingModel->countInliers(testingData->getInOutliersData(), allowedError);
		return res;
	}


	friend ostream & operator<<(ostream & flux, const Ransac<DataClass,ModelClass> r)
	{
		flux << r.getInput() << endl;
		return flux;
	}
};

