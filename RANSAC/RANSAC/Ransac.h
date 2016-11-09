#include <iostream>
#include <vector>

using namespace std;

#pragma once
template <class T>
class Ransac
{
private:
	vector<T> data;

public:
	Ransac(vector<T> points);
	vector<T> getData() const;
	template <class T> friend ostream& operator<<(ostream &flux, const Ransac r);
};

