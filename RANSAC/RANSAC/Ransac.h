#include <iostream>

using namespace std;

#pragma once
template <class T>
class Ransac
{
private:
	T data;

public:
	Ransac(T points);
	T getData() const;
	template <class T> friend ostream& operator<<(ostream &flux, const Ransac r);
};

