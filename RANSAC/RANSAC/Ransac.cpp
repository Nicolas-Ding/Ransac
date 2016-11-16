#include "Ransac.h"
/* DEFINITION DES FONCTIONS */

template<class T>
Ransac<T>::Ransac(InputRansac<T> points)
{
	input = points;
}

template<class T>
InputRansac<T> Ransac<T>::getInput() const
{
	return input;
}

template<class T>
InputRansac<T> Ransac<T>::getSubSample(int k) const
{
	return input.getSubSample(k);
}

template<class T>
ostream & operator<<(ostream & flux, const Ransac<T> r)
{
	T test = r.getInput();
	flux << T << endl;
	return flux;
}


