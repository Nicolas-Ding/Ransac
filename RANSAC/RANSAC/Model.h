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

	Model<T>* getSubSample(int k) const
	{
		set<int> indexes;
		vector<T> choices;
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
		return new Model<T>(choices);
	}

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

	void printClass() {
		cout << "Model" << endl;
	}
};

#endif