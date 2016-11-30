#ifndef HEADER_MODEL
#define HEADER_MODEL

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

template <class T>
class Model
{
protected:
	vector<T> points;

public:

	Model(){}
	
	Model(vector<T> inputs)
	{
		points = inputs;
	}

	vector<T> getPoints() const
	{
		return points;
	}

	virtual Model<T>* getSubSample(int k) const { return NULL; };
	virtual void printClass() { cout << "Model" << endl; };
	virtual void computeParameters() {} ;
	virtual bool isOutlier(T testInput, double err) const { return false; };

	int testCorrelation(Model<T> testingModel, double allowedError) {
		int res = 0;
		for (auto i = points.begin(); i < points.end(); i++)
			res += (testingModel.isOutlier(*i, allowedError) ? 0 : 1);
		return res;
	}
	
	friend ostream & operator<<(ostream & flux, const Model<T> r)
	{
		vector<T> vec = r.getPoints();
		for (auto i = vec.begin(); i < vec.end(); i++)
			flux << *i << " ";
		return flux;
	}


};

#endif