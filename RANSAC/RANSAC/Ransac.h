#include <iostream>

using namespace std;

#pragma once
template <class T>
class Ransac
{
private:
	T points;

public:
	Ransac(T points);
	friend ostream& operator<<(ostream &flux, const Ransac r);
	virtual ~Ransac();
};

