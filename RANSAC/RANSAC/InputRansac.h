#ifndef HEADER_INPUTRANSAC
#define HEADER_INPUTRANSAC

#include <iostream>
#include <vector>

using namespace std;

template <class T>
class InputRansac
{
private:
	vector<T> points;

public:
	
	InputRansac(vector<T> inputs)
	{
		points = inputs;
	}

	
	vector<T> getPoints() const
	{
		return points;
	}

	
	friend ostream & operator<<(ostream & flux, const InputRansac<T> i)
	{
		for (auto i = points.begin(); i < points.end(); i++)
			flux << *i << " ";
		return flux;
	}
};

#endif