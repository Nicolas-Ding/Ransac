#include "Ransac.h"

/* DEFINITION DES FONCTIONS */

template<class T>
Ransac<T>::Ransac(T points)
{
	data = points;
}

template<class T>
T Ransac<T>::getData() const
{
	return data;
}

template<class T>
ostream & operator<<(ostream & flux, const Ransac<T> r)
{
	flux << r.getData();
	return flux;
}


