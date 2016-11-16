#include "InputRansac.h"
/* DEFINITION DES FONCTIONS */

template<class T>
InputRansac<T>::InputRansac(vector<T> inputs)
{
	points = inputs;
}

template<class T>
vector<T> InputRansac<T>::getPoints() const
{
	return points;
}

template<class T>
ostream & operator<<(ostream & flux, const InputRansac<T> i)
{
	for (auto i = points.begin(); i < points.end(); i++)
		flux << *i << " ";
	return flux;
}