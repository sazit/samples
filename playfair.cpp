//============================================================================
// Name        : InfoSec_a.cpp
// Author      : Sajit Gurubacharya
// Description : PLayfair Cipher Code in C++
//============================================================================

#include <iostream>
#include<stdio.h>
#include <vector>
#include <string>
using namespace std;

const string padding="z";

void findText(string&);
string getLetter(int);
void getCiphers(string&, string&, vector<int>);

int main() {
	string key;
	string plainText;
	int main[26];
	vector<int> ciphered;

	for (int i = 0; i < 26; i++) { /* fill default array */
		main[i] = i;
	}

	findText(key);	/* get key input */
	bool charRep=false; /* repetition character flag */

	// check if char repeats in key and insert in ciphered
	for (int i=0;i<key.length();i++){
		for (int j=0;j<ciphered.size();j++){
			if ((int)key[i]-97==ciphered[j]){
				charRep=true;
			}
		}
		if (!charRep){
			ciphered.push_back((int)key[i]-97); // storing 0-26 values
		}else{
			charRep=false;
		}
	}

	charRep=false;
	for (int i=0;i<26;i++){
		for (int j=0;j<ciphered.size();j++){
			if (i==ciphered[j]){
				charRep=true; // scan all current letters for repetitions
			}
		}

		if (!charRep){
			ciphered.push_back(i);
		}else{
			charRep=false; // for next round
		}
	}

	// parsing ciphered for i/j
	bool firstIJinstance=false;
	for (int i=0;i<ciphered.size();i++){
		if (!firstIJinstance){
			if (ciphered[i]==8 || ciphered[i]==9){
						firstIJinstance=true;
						ciphered[i]=8; // store i/j as i (8)
			}
		}else{
			if (ciphered[i]==8 || ciphered[i]==9){
				ciphered.erase(ciphered.begin()+i);
			}
		}

	}
	// resizing array to 25
	for (int i=0;i<ciphered.size();i++){
		if (ciphered[i]>9){
			ciphered[i]-=1;
		}
	}
	for (int i=0;i<ciphered.size();i++){
		if (i % 5 == 0) {
			cout<<"\n";
		}
		cout<< " " << ciphered[i] << " ";

	}
	cout<<"\n";
	for (int i=0;i<ciphered.size();i++){
		if (i % 5 == 0) {
				cout<<"\n";
			}
			cout<< " " << getLetter(ciphered[i]) << " ";
		}

	findText(plainText);

	if (plainText.length()%2==1){
		plainText+=padding;
	}
	// looking for repeating paired words


	int halflength = plainText.length() / 2;
	vector<string> finalCipher;
	for (int i=0;i<halflength;i++){
		string first="";
		first+=plainText[i*2];
		string second="";
		second+=plainText[i*2+1];
		if(first==second){
			/*AAB -> AABZ -> AZ AZ BZ
			 *AABC -> AA BC -> AZ AZ BC*/
			string tempFirst, tempSecond;
			tempFirst+=padding;
			tempSecond+=padding;
			cout << "Current Letters " << first << tempFirst;
			getCiphers(first, tempFirst, ciphered);
			finalCipher.push_back(first);
			finalCipher.push_back(tempFirst);
			cout << "Current Letters " << second << tempSecond;
			getCiphers(second, tempSecond, ciphered);
			finalCipher.push_back(second);
			finalCipher.push_back(tempSecond);
		} else {
			cout << "Current Letters " << first << second;
			getCiphers(first, second, ciphered);
			finalCipher.push_back(first);
			finalCipher.push_back(second);
		}
	}
	cout<<"Final Cipher: ";

	for (int i=0;i<finalCipher.size();i++){
		cout<<finalCipher[i];
	}


	return 0;
}

void findText(string& text) {
	cout << "\nEnter a string: ";
	cin >> text;
}

string getLetter(int val){
	string toReturn;
	if (val>8){
		val++;
	}
	toReturn += char(val + 97);
	return toReturn;
}


void getCiphers(string& first, string& second, vector<int> ciphers){
	int firstPosition, secondPosition;
	int fRow, fCol, sRow, sCol;
	for (int i=0;i<ciphers.size();i++){
		if (getLetter(ciphers[i])==first){
			firstPosition=i;
		}
		if (getLetter(ciphers[i])==second){
			secondPosition = i;
		}
		// getLetter will never return 'j'
		if (first=="j" && getLetter(ciphers[i])=="i" ){
			firstPosition=i;
		}
		if (second=="j" && getLetter(ciphers[i])=="i" ){
			secondPosition=i;
		}
	}
	fRow = firstPosition / 5;
	fCol = firstPosition % 5;
	sRow = secondPosition / 5;
	sCol = secondPosition % 5;

	cout  << "\n( "<<fRow << ", "<< fCol << "), ("<< sRow << ", "<< sCol << ")";

	// switcharoo
	if (fRow==sRow){
		fCol=(fCol+1)%5;
		sCol=(sCol+1)%5;
	}else if (fCol==sCol){
		fRow=(fRow+1)%5;
		sRow=(sRow+1)%5;
	}else{
		int tempCol= fCol;
		fCol=sCol;
		sCol=tempCol;
	}

	cout  << "\n( "<<fRow << ", "<< fCol << "), ("<< sRow << ", "<< sCol << ")\n";
	firstPosition = fRow * 5 + fCol;
	secondPosition = sRow * 5 + sCol;

	first = getLetter(ciphers[firstPosition]);
	second = getLetter(ciphers[secondPosition]);

}


