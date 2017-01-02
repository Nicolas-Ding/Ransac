#pragma once
#include<vector>
#include<set>
#include<iostream>

using namespace std;

class RansacUtils {
	public : 
		template<class T>
		static vector<T> getSubVector(vector<T> points, int k)
		{
			set<int> indexes;
			vector<T> choices;
			int max_index = points.size();
			while (indexes.size() < min(k, max_index))
			{
				int random_index = rand() % max_index;
				if (indexes.find(random_index) == indexes.end())
				{
					choices.push_back(points[random_index]);
					indexes.insert(random_index);
				}
			}
			return choices;
		};

		template<typename T>
		static void printVector(vector<T> vec) {
			for (vector<T>::iterator i = vec.begin(); i != vec.end(); ++i)
				cout << ' ';
		};
};