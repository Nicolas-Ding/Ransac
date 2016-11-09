#include <iostream>
#include "Ransac.h"

using namespace std;

int main() {
	Ransac<string> ransac = Ransac<string>("Hello world");
	cout << ransac << endl;
}