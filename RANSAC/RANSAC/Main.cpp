#include <iostream>
#include "Ransac.cpp"

using namespace std;

int main() {
	Ransac<int> ransac(3);
	cout << ransac << endl;
	int t;
	cin >> t;
}