#ifndef HEADER_RANSAC
#define HEADER_RANSAC

#include <iostream>
#include <vector>
#include "InputRansac.h"

using namespace std;

#pragma once
template <class T>
class Ransac
{
private:
	InputRansac<T> input;

public:
	Ransac(InputRansac<T> points)
	{
		input = points;
	}
	
	InputRansac<T> getInput() const
	{
		return input;
	}

	
	InputRansac<T> getSubSample(int k) const
	{
		return input.getSubSample(k);
	}


	friend ostream & operator<<(ostream & flux, const Ransac<T> r)
	{
		T test = r.getInput();
		flux << T << endl;
		return flux;
	}
};

#endif
