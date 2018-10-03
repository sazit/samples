/*
 * RSA Implementation
 *
 *  Created on: Sep 24, 2018
 *      Author: sajitgurubacharya
 *
 *  Implementation of an RSA encryption and decryption algorithm
 *  using the square-multiply algorithm, finding the gcd and input
 *  validations.
 */

#ifndef TASKTWO_H_
#define TASKTWO_H_

#include <cmath>

void taskTwo();
bool testPQ(int, int);
bool testE(int, int);
int gcd(int, int);
void input(int&,int&,int&,int&,int&,int&);
int encryption(int, int, int);
int decryption(int, int, int, int);
vector<int> getBinary(int);
void convertToBinary(unsigned int n, vector<int>&);
int inverse(int e, int phi);

/*
 * All values stored as integers (decimals and validated)
 */
void taskTwo() {
	int p, q, e, m, phi, n, o, d;
	input(p, q, e, m, phi, n);
	o = encryption(m, e, n);
	cout << "\nOutput Encryption: " << o;
	d = decryption(e, phi, n, o);
	cout << "\nOutput Decryption: " << d;
}

/*
 * Test functions ahve been included for p, q and e values
 */
void input(int& p, int& q, int& e, int& m, int& phi, int& n) {
	do {
		cout << "P: ";
		cin >> p;
		cout << "Q: ";
		cin >> q;
	} while (!testPQ(p, q));
	phi = (p - 1) * (q - 1);
	n = p * q;
	do {
		cout << "E: ";
		cin >> e;
	} while (!testE(e, phi));
	cout << "Message: ";
	cin >> m;

}

/*
 * Encryption and decryption functions are similar with values
 * changes. Binary representation of the exponent is stored in a
 * vector. The value of c will equal to the decimal equivalent of the
 * binary input. Square-Multiply algorithm implemented here to handle
 * large numbers generated due to use of exponents.
 */
int encryption(int m, int e, int n){
	int c = 0, d = 1;
	cout<< "\n***Encryption***";
	cout<<"\nE: " << e <<"(10) ->";
	vector<int> eBinary = getBinary(e);
	for (int i = 0; i < eBinary.size(); i++) {
		c = 2 * c;
		d = (d * d) % n;
		cout << "\nD: " << d << " C: " << c;
		if (eBinary[i] == 1) {
			c = c + 1;
			d = (d * m) % n;
			cout << "\nD: " << d << "(1) C: " << c;
		}
	}
	return d;
}

int decryption(int e, int phi, int n, int o ){
	cout << "\n\n***Decryption***";
	int d = inverse(e, phi);
	cout<<"\n"<< e << " * "<< d << "MOD "<< phi << " = " << 1;
	int c = 0, toReturn = 1;
	cout<<"\nD: " << d <<"(10) ->";
	vector<int> eBinary = getBinary(d);
	for (int i = 0; i < eBinary.size(); i++) {
		c = 2 * c;
		toReturn = (toReturn * toReturn) % n;
		cout << "\nE: " << toReturn << " C: " << c;
		if (eBinary[i] == 1) {
			c = c + 1;
			toReturn = (toReturn * o) % n;
			cout << "\nE: " << toReturn << "(1) C: " << c;
		}
	}
	return toReturn;
}

/*
 * Returns the multiplicative inverse of e with phi
 */
int inverse(int e, int phi){
	int i=0;
	while (i<phi){
		i++;
		if (e*i % phi ==1){
			return i;
		}
	}
	return -1;
}

/*
 * Uses a recursion function to push back the remainders
 * into a vector as the binary representation of e.
 */
vector<int> getBinary(int e) {
	vector<int> toReturn;
	convertToBinary(e, toReturn);
	for (int i = 0; i < toReturn.size(); i++) {
		cout << toReturn[i];
	}
	return toReturn;
}

void convertToBinary(unsigned int n, vector<int>& toReturn) {
	if (n / 2 != 0) {
		convertToBinary(n / 2, toReturn);
	}
	toReturn.push_back(n % 2);
}

/*
 * Validates values of P and Q
 */
bool testPQ(int p, int q) {
	if (p == q) {
		cout<<"P = Q\n";
		return false;
	}
	for (int i = 2; i < p / 2; i++) {
		if (p % i == 0) {
			cout<<"P is not prime\n";
			return false;
		}
	}
	for (int i = 2; i < q / 2; i++) {
		if (q % i == 0) {
			cout<<"Q is not prime\n";
			return false;
		}
	}
	return true;
}

/*
 * Validates values of E with generated Phi
 */
bool testE(int e, int phi) {
	if (e < 1 || e > phi) {
		cout << e << " > " << phi << " or " << e << " < 1\n";
		return false;
	}
	if (gcd(phi, e) != 1) {
		cout << e << " and " << phi << " are not relatively prime\n";
		return false;
	}
	return true;
}

/*
 * Returns the greatest common divisior of the two inputs
 */
int gcd(int first, int second) {
	static int count=0;
	int remainder;
	count++;
	if (second==0){
		return first;
	}
	remainder = first % second;
	return gcd(second, remainder);
}

#endif /* TASKTWO_H_ */
