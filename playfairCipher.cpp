//============================================================================
// Name        : InfoSec_a.cpp
// Author      : Sajit Gopal Gurubacharya
// Description : PLayfair Cipher Code in C++
//============================================================================

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

const string padding="z";

void getUserInput(string&, string); 	/* validates user input */
string getLetter(int);				/* get's a single letter taking into consideration i/j */
void getCiphers(string&, string&, vector<int>);	/* get's new char from ciphered array  */
void fixString(string&);				/* insert's padding letter wherever necessary */

int main() {
	string key;
	string plainText;
	int main[26];
	vector<int> ciphered;

	for (int i = 0; i < 26; i++) { /* fill default array */
		main[i] = i;
	}

	getUserInput(key, "Key");		/* get key input */
	bool charRep=false; /* repetition character flag */

	/* check if char repeats in key and insert in ciphered array*/
	for (int i=0;i<key.length();i++){
		for (int j=0;j<ciphered.size();j++){
			if ((int)key[i]-97==ciphered[j]){
				charRep=true;
			}
		}
		if (!charRep){
			ciphered.push_back((int)key[i]-97); /* storing 0-26 values */
		}else{
			charRep=false;
		}
	}


	charRep=false;
	for (int i=0;i<26;i++){
		for (int j=0;j<ciphered.size();j++){
			if (i==ciphered[j]){
				charRep=true; /* scan all current letters for repetitions */
			}
		}
		if (!charRep){
			ciphered.push_back(i);
		}else{
			charRep=false; /* for next round */
		}
	}

	/* parsing ciphered for i/j to mix as one */
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

	/* resizing array to 25 by fixing letter 'i' position*/
	for (int i=0;i<ciphered.size();i++){
		if (ciphered[i]>9){
			ciphered[i]-=1;
		}
	}
	for (int i=0;i<ciphered.size();i++){
		if (i % 5 == 0) {
			cout<<"\n";
		}
		cout<< setw(3) << ciphered[i] << setw(3);

	}
	cout<<"\n";
	for (int i=0;i<ciphered.size();i++){
		if (i % 5 == 0) {
				cout<<"\n";
			}
			cout<< " " << getLetter(ciphered[i]) << " ";
		}

	getUserInput(plainText, "Plain Text");
	cout<< "\nYour Word: "<< plainText;
	fixString(plainText);
	cout<< "\nYour New Word: "<< plainText;

	/* add final padding if required */
	if (plainText.length()%2==1){
		plainText+=padding;
	}

	/* pairing up words */
	int halflength = plainText.length() / 2;
	vector<string> finalCipher;
	for (int i=0;i<halflength;i++){
		string first = "";
		first += plainText[i * 2];
		string second = "";
		second += plainText[i * 2 + 1];
		cout << "\nCurrent Letters " << first << second;
		getCiphers(first, second, ciphered);
		finalCipher.push_back(first);
		finalCipher.push_back(second);
	}
	cout<<"\nFinal Cipher: ";
	for (int i=0;i<finalCipher.size();i++){
		cout<<finalCipher[i];
	}
	return 0;
}

void getUserInput(string& text, string word) {
	cout << "\nEnter a string "<< word << ":";
	cin >> text;
	locale loc;
	transform(text.begin(), text.end(), text.begin(), ::tolower);
}

string getLetter(int val){
	string toReturn;
	if (val>8){
		val++;
	}
	toReturn += char(val + 97);
	return toReturn;
}

void fixString(string& text){
	string previous;
	string newText="";
	previous=text[0];
	for (int i=1;i<text.length();i++){
		newText+=previous;
		if (previous[0]==text[i]){
			previous=padding;
			i--;
		}else{
			previous=text[i];
		}
	}
	newText+=previous;
	text=newText;
}

/*
 *  First and second letters of each pairs are taken into
 *  consideration and matched with ciphers vector. Then
 *  updated ciphered strings are returned.
 */

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
		/* getLetter() will never return 'j' */
		if (first=="j" && getLetter(ciphers[i])=="i" ){
			firstPosition=i;
		}
		if (second=="j" && getLetter(ciphers[i])=="i" ){
			secondPosition=i;
		}
	}

	/* Array stored as 1D array converted into 2D*/
	fRow = firstPosition / 5;
	fCol = firstPosition % 5;
	sRow = secondPosition / 5;
	sCol = secondPosition % 5;

	cout  << "\n("<<fRow << ", "<< fCol << "), ("<< sRow << ", "<< sCol << ")";

	/* Switcharoo */
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

	cout  << "\n("<<fRow << ", "<< fCol << "), ("<< sRow << ", "<< sCol << ")\n";

	/* Back to 1D array to match with ciphered array */
	firstPosition = fRow * 5 + fCol;
	secondPosition = sRow * 5 + sCol;

	first = getLetter(ciphers[firstPosition]);
	second = getLetter(ciphers[secondPosition]);

}


