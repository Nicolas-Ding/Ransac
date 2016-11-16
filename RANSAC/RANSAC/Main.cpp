#include <iostream>
#include <string>
#include "InputRansac.h"
#include "Ransac.h"

using namespace std;

int main() {
	vector<int> input(5, 2);
	for (auto i = input.begin(); i < input.end(); i++)
		cout << *i << " ";
	InputRansac<int> test(input);
	Ransac<int> ransac(test);
	//cout << ransac << endl;
	int t;
	cin >> t;
}