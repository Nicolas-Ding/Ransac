#include <iostream>
#include <string>
#include "Ransac.cpp"

using namespace std;

int main() {
	vector<string> test(3, "hello");
	/*for (auto i = test.begin(); i < test.end(); i++)
		cout << *i << endl;*/
	Ransac<string> ransac(test);
	cout << ransac << endl;
	int t;
	cin >> t;
}