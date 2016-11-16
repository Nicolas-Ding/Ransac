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
	InputRansac(vector<T> inputs);
	vector<T> getPoints() const;
	template <T> friend ostream& operator<<(ostream &flux, const InputRansac i);
};

#endif