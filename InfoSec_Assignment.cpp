//============================================================================
// Name        : InfoSec_Assignment.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "taskOne.h"
#include "taskTwo.h"
using namespace std;

void start(int);

int main() {
	int choice;
	cout << "Welcome. Press 1 for Task One and 2 for Task Two" << endl;
	cin >> choice;
	start(choice);
	return 0;
}

void start(int choice){
	if (choice==1){
		cout << "S-DES" << endl;
		taskOne();
	}else{
		cout << "RSA" << endl;
		taskTwo();
	}
}


