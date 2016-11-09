#include "InputRansac.h"

/* DEFINITION DES FONCTIONS */

template<class T>
InputRansac<T>::InputRansac(T pointInput)
{
	point = pointInput;
}

template<class T>
T InputRansac<T>::getPoint() const
{
	return point;
}

template<class T>
ostream & operator<<(ostream & flux, const InputRansac<T> i)
{
	T test = r.getPoint();
	flux << test << " ";
	return flux;
}