/*
 * S-DES Implementation
 *
 *  Created on: Sep 24, 2018
 *      Author: sajitgurubacharya
 *
 *  To implemented a modified S-DES algorithm, all binary values are
 *  stored as vectors and conversion functions have been added where
 *  necessary.
 */

#ifndef TASKONE_H_
#define TASKONE_H_

#include <vector>
#include <string>
#include <stack>

using namespace std;

/* Permutations declared here, including S-Box*/
int IP[] = {3,5,10,9,16,8,7,1,14,12,2,13,4,11,6,15};
int IPinv[] ={8,11,1,13,2,15,7,6,4,3,14,10,12,9,16,5};
int EP[]={5,7,3,2,8,4,6,1,1,6,4,8,2,3,7,5};
int P8[]={2,6,3,1,4,5,8,7};
int P20[]={5,2,9,12,1,19,10,3,8,11,7,17,4,15,6,20};
int P16[]={11,2,13,8,9,14,6,10,16,1,5,12,3,7,15,4};
int S1[16]={1,0,3,2,3,2,1,0,0,2,1,3,3,1,3,2};
int S2[16]={0,1,2,3,2,0,1,3,3,0,1,0,2,1,0,3};
int S3[16]={0,3,2,1,1,0,3,2,3,2,0,1,2,3,0,1};
int S4[16]={3,2,0,1,0,3,1,2,2,1,0,3,1,2,3,0};

/*
 * Functions have been made generic enough to be used a second time
 * for the second half of the function.
 *
 * Functions for main encryption
 */
void input(vector<int>&,vector<int>&);
void halfize(int[],vector<int>&, vector<int>&,vector<int>);
void permute(int[], vector<int>,vector<int>&, int);
void XOR(vector<int>, vector<int>, vector<int>&);
void quaterize(vector<int>,vector<int>&);
void combquaterize(vector<int>,vector<int>,vector<int>,vector<int>,vector<int>&, int[]);
int returnNumericalFromBinaryForSBox(int);
void  returnBinaryFromNumericalForSBox(int, vector<int>&);

/*
 * Functions to generate the two keys
 */
void generateKeys(vector<int>, vector<int>&, vector<int>&);
void LS(vector<int>&, int);

void taskOne(){
	vector<int> plaintext, key, IP8_1, IP8_2, EP_1, XOR1;
	vector<int> SBox1, P8_1, XOR2, combined, cipher, key1, key2;

	input(plaintext, key); // cannot start with 0, 16/20bits not validated

	generateKeys(key, key1, key2); // returns first and second key
	// Printing keys text
	cout << "Key 1: ";
	for (int i = 0; i < key1.size(); i++) {
		cout << key1[i];
	}
	cout << "\nKey 2: ";
	for (int i = 0; i < key2.size(); i++) {
		cout << key2[i];
	}

	halfize(IP,IP8_1,IP8_2, plaintext); // IP8_1 and IP8_2 have been updated
	permute(EP, IP8_2, EP_1, 16); // EP_1 updated
	XOR(EP_1, key1, XOR1); // XOR1 updated
	quaterize(XOR1, SBox1); // SBox1 updated
	permute(P8, SBox1, P8_1, 8); // P8_1 updated
	XOR(IP8_1, P8_1, XOR2); // XOR2 updated
	/*
	 * Switching IP8_1 and IP8_2. IP8_2 had been used before
	 * so IP8_1 (XOR2) will be used now.
	 *
	 * Clearing vectors for re-use.
	 */
	IP8_1.clear();
	EP_1.clear();
	XOR1.clear();
	SBox1.clear();
	P8_1.clear();
	IP8_1=XOR2;
	XOR2.clear();

	// Second half starts here
	permute(EP, IP8_1, EP_1, 16); // EP_1 updated
	XOR(EP_1, key2, XOR1); // XOR1 updated
	quaterize(XOR1, SBox1); // SBox1 updated
	permute(P8, SBox1, P8_1, 8); // P8_1 updated
	XOR(IP8_2, P8_1, XOR2); // XOR2 updated

	// Combining two vectors before final permuation
	combined.reserve(XOR2.size() + IP8_1.size()); // preallocate memory
	combined.insert(combined.end(), XOR2.begin(), XOR2.end());
	combined.insert(combined.end(), IP8_1.begin(), IP8_1.end());
	permute(IPinv, combined, cipher, 16); // cipher updated

	// Printing cipher text
	cout<<"\nCipher: ";
	for (int i=0;i<cipher.size();i++){
		cout<<cipher[i];
	}

}

void generateKeys(vector<int> key, vector<int>& key1, vector<int>& key2){
	vector<int> tempLeft, tempRight, tempCombined;
	permute(P20, key, tempCombined, 16); // tempCombined updated

	for (int i=0;i<8;i++){
		tempLeft.push_back(tempCombined[i]);
	}
	for (int i = 8; i < 16; i++) {
		tempRight.push_back(tempCombined[i]);
	}

	// Re-use of vectors to find both LS1 and LS2
	LS(tempLeft, 1);	// 1 indicates left shift of
	LS(tempRight, 1);

	tempCombined.clear();
	tempCombined.reserve( tempLeft.size() + tempRight.size()); // preallocate memory
	tempCombined.insert( tempCombined.end(), tempLeft.begin(), tempLeft.end() );
	tempCombined.insert( tempCombined.end(), tempRight.begin(), tempRight.end() );
	permute(P16, tempCombined, key1, 16); // tempCombined updated

	LS(tempLeft, 2);
	LS(tempRight, 2);

	tempCombined.clear();
	tempCombined.reserve(tempLeft.size() + tempRight.size()); // preallocate memory
	tempCombined.insert(tempCombined.end(), tempLeft.begin(), tempLeft.end());
	tempCombined.insert(tempCombined.end(), tempRight.begin(), tempRight.end());
	permute(P16, tempCombined, key2, 16); // tempCombined updated
}

/*
 * LS function defined for circular left shift either one or two times
 */
void LS(vector<int>& input, int no){
	vector<int> temp;
	if (no==1){
		temp.push_back(input[0]);
		for (int i=1;i<8;i++){
			input[i-1]=input[i];
		}
		input[7]=temp[0];
	}else{
		temp.push_back(input[0]);
		temp.push_back(input[1]);
		for (int i = 2; i < 8; i++) {
			input[i - 2] = input[i];
		}
		input[6] = temp[0];
		input[7] = temp[1];
	}
}

/*
 * Divides the input vector into 4 equal parts and applies the corresponding S-Box
 * premutations and returns a single output vector.
 */
void quaterize(vector<int> input, vector<int>& output) {
	vector<int> s1t, s2t, s3t, s4t;
	vector<int> s1v, s2v, s3v, s4v;
	for (int i = 0; i < input.size(); i++) {
		if (i < input.size() / 4) {
			s1t.push_back(input[i]); // temporarily storing input values
		} else if (i < input.size() / 2 && i >= input.size() / 4) {
			s2t.push_back(input[i]);
		} else if (i >= input.size() / 2 && i < 3 * input.size() / 4) {
			s3t.push_back(input[i]);
		} else {
			s4t.push_back(input[i]);
		}
	}
	returnBinaryFromNumericalForSBox(
			S1[returnNumericalFromBinaryForSBox(s1t[0] * 10 + s1t[3]) * 4
					+ returnNumericalFromBinaryForSBox(s1t[1] * 10 + s1t[2])],
			s1v);
	returnBinaryFromNumericalForSBox(
			S2[returnNumericalFromBinaryForSBox(s2t[0] * 10 + s2t[3]) * 4
					+ returnNumericalFromBinaryForSBox(s2t[1] * 10 + s2t[2])],
			s2v);
	returnBinaryFromNumericalForSBox(
			S3[returnNumericalFromBinaryForSBox(s3t[0] * 10 + s3t[3]) * 4
					+ returnNumericalFromBinaryForSBox(s3t[1] * 10 + s3t[2])],
			s3v);
	returnBinaryFromNumericalForSBox(
			S4[returnNumericalFromBinaryForSBox(s4t[0] * 10 + s4t[3]) * 4
					+ returnNumericalFromBinaryForSBox(s4t[1] * 10 + s4t[2])],
			s4v);
	output.push_back(s1v[0]);
	output.push_back(s1v[1]);
	output.push_back(s2v[0]);
	output.push_back(s2v[1]);
	output.push_back(s3v[0]);
	output.push_back(s3v[1]);
	output.push_back(s4v[0]);
	output.push_back(s4v[1]);
}

/*
 * Input of binary returns the decimal value in integer form.
 */
int returnNumericalFromBinaryForSBox(int binary) {
	if (binary == 0) {
		return 0;
	} else if (binary == 1) {
		return 1;
	} else if (binary == 10) {
		return 2;
	} else if (binary == 11) {
		return 3;
	} else {
		return -1;
	}
}

/*
 * Input of decimal returns the binary value in vector form.
 */
void returnBinaryFromNumericalForSBox(int numerical, vector<int>& binary) {
	if (numerical == 0) {
		binary.push_back(0);
		binary.push_back(0);
	} else if (numerical == 1) {
		binary.push_back(0);
		binary.push_back(1);
	} else if (numerical == 2) {
		binary.push_back(1);
		binary.push_back(0);
	} else if (numerical == 3) {
		binary.push_back(1);
		binary.push_back(1);
	} else {

	}
}

/*
 * Returns a result vector with the XOR (^) function applied to corresponding binary inputs.
 */
void XOR(vector<int> inputOne, vector<int> inputTwo, vector<int>& output) {
	for (int i = 0; i < inputOne.size(); i++) {
		output.push_back(inputOne[i] ^ inputTwo[i]);
	}
}

/*
 * Useful generic function that returns the permuted vector given required inputs.
 */
void permute(int permutation[], vector<int> input, vector<int>& output,
		int outputSize) {
	for (int i = 0; i < outputSize; i++) {
		output.push_back(input[permutation[i] - 1]); // Permutations start at 1, arrays do not
	}
}

/*
 * Splits the vector into halves and applies a permutation.
 */
void halfize(int permutation[], vector<int>& first, vector<int>& second,
		vector<int> input) {
	for (int i = 0; i < input.size(); i++) {
		if (i < input.size() / 2) {
			first.push_back(input[permutation[i] - 1]); // Permutations start at 1, arrays do not
		} else {
			second.push_back(input[permutation[i] - 1]);
		}
	}
}

/*
 * Takes in and validates plaintext and key inputs. long long are used to store
 * values upto 16 bits. String is used to store 20bits. String is converted into char for
 * individual extraction, then back to single String to be converted into int.
 */
void input(vector<int>& plaintext, vector<int>& key) {
	long long p;
	vector<char> tempChar;
	vector<string> tempString;
	string k;
	stack<int> sd;
	do {
		plaintext.clear();
		cout << "Input the plaintext of 16 btis: ";
		cin >> p;
		while (p > 0) {
			int digit = p % 10;
			p /= 10;
			sd.push(digit);
		}
		while (!sd.empty()) {
			plaintext.push_back(sd.top());
			sd.pop();
		}
	} while (plaintext.size() != 16);

	do {
		key.clear();
		cout << "Input the key of 20 bits: ";
		cin >> k;

		for (int i = 0; i < 20; i++) {
			tempChar.push_back(k[i]);
		}
		for (int i = 0; i < 20; i++) {
			string str;
			str = tempChar[i];
			tempString.push_back(str);
		}
		for (int i = 0; i < 20; i++) {
			int kk;
			kk = stoi(tempString[i]);
			key.push_back(kk);
		}
	} while (key.size() != 20);

}

#endif /* TASKONE_H_ */
