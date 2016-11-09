#include <iostream>
#include <vector>

using namespace std;

#pragma once
template <class T>
class InputRansac
{
private:
	T point;

public:
	T getPoint() const;
	InputRansac(T pointInput);
	template <T> friend ostream& operator<<(ostream &flux, const InputRansac i);
};

