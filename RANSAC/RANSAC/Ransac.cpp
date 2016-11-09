#include "Ransac.h"


template<class T>
Ransac<T>::Ransac(T points)
{
	self.points = points;
}

template<class T>
ostream & operator<<(ostream & flux, const Ransac<T> r)
{
	flux << r.points;
	return flux;
}

template<class T>
Ransac<T>::~Ransac()
{
}
