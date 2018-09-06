//============================================================================
// Name        : Ackermann.cpp
// Author      : Sajit Gurubacharya
// Version     : 1.0
// Description : Ackerman Function
// Warning	   : 'M' should not exceed 4!
//============================================================================

#include <iostream>
#include <iomanip>
#include <chrono>

using namespace std;

class Ackerman {
private:
	int m, n;
public:
	int ack(int, int);
};

int Ackerman::ack(int m2, int n2) {
	m = m2;
	n = n2;
	int ans;
	if (m == 0) {
		ans = n + 1;
	} else if (n == 0) {
		ans = ack(m - 1, 1);
	} else {
		ans = ack(m - 1, ack(m, n - 1));
	}
	return ans;
}

int main() {
	clock_t time = clock();
	int m1, n1;
	do {
		cout << "M: ";
		cin >> m1;
	} while (m1 > 4);

	cout << "N: ";
	cin >> n1;
	Ackerman testOne;
	for (int i = 0; i <= m1; i++) {
		for (int j = 0; j <= n1; j++) {
			cout << "\nAckerMan(" << i << "," << j << "): "<<left <<setw(5)
					<< testOne.ack(i, j);
			time = clock() - time;
			double ms = (double) time;
			ms=ms/1000000; // time in microseconds (10^-6)
			cout<<" Time: "<< ms << " secs";
		}
	}
	return 0;
}
