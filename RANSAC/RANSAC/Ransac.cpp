#include "Ransac.h"

/* DEFINITION DES FONCTIONS */

template<class T>
Ransac<T>::Ransac(vector<T> points)
{
	data = points;
}

template<class T>
vector<T> Ransac<T>::getData() const
{
	return data;
}

template<class T>
ostream & operator<<(ostream & flux, const Ransac<T> r)
{
	vector<T> test = r.getData();
	for (auto i = test.begin(); i < test.end(); i++)
		flux << *i << " ";
	return flux;
}


