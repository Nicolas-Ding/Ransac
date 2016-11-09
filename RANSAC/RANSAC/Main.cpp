#include <iostream>
#include <string>
#include "Ransac.cpp"

using namespace std;

int main() {
	InputRansac<string> test("3 4");
	Ransac<string> ransac(test);
	cout << ransac << endl;
	int t;
	cin >> t;
}