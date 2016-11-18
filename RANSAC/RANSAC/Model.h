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

	Model<T> getSubSample(int k) const
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
		return Model<T>(choices);
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