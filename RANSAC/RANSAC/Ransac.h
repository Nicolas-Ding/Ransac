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

	Ransac() {};

	Ransac(DataClass* m)
	{
		data = m;
	}

	DataClass* getData() const
	{
		return data;
	}

	void setData(DataClass* m)
	{
		data = m;
	}

	ModelClass compute(int iterationNb, int subSampleSize, double allowedError, int corrBreakPoint)
	{
		int bestCorr = NULL;
		ModelClass* bestModel = NULL;
		for (int i = 0; i < iterationNb; i++) {
			ModelClass* model = data->computeModel(subSampleSize);
			if (model != NULL)
			{
				int corr = testCorrelation(model, data, allowedError);
				cout << "Corr --> " << corr << endl;
				if (bestCorr == NULL || corr > bestCorr) {
					bestCorr = corr;
					bestModel = model;
					if (bestCorr > corrBreakPoint)
						i = iterationNb;
				}
			}
			if (i % 20 == 0)
				corrBreakPoint -= 10;
		}
		bestModel->printClass();
		cout << "correlation is " << bestCorr << endl;
		data->show(*bestModel);
		return *bestModel;
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

