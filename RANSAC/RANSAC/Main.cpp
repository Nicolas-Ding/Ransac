#include <iostream>
#include <string>
#include <time.h>
#include "InputRansac.h"
#include "Ransac.h"

using namespace std;

int main() {
	srand(time(NULL));
	vector<int> input;
	for (int i = 0; i < 100; i++) {
		input.push_back(i);
	}
	for (auto i = input.begin(); i < input.end(); i++)
		cout << *i << " ";
	cout << endl;
	Model<int> test(input);
	Ransac<int> ransac(test);
	cout << ransac.getSubSample(5) << endl;
	int t;
	cin >> t;
}