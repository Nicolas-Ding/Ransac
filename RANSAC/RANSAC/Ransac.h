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
	Ransac(InputRansac<T> points);
	InputRansac<T> getInput() const;
	InputRansac<T> getSubSample(int n) const;
	template <class T> friend ostream& operator<<(ostream &flux, const Ransac r);
};

#endif
