#include <iostream>

using namespace std;

#pragma once
class Ransac
{
public:
	Ransac();
	friend ostream& operator<<(ostream &flux, const Ransac r);
	virtual ~Ransac();
};

