//My code encrypts and decrypts based on the user password and that is the only way. You can input any size password and can use any characters. 
//The code will iterate through each character in the password along with the coresponding index for the input file. That way each character has a different increase in change.
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
bool encrypt(string file, string key);
bool decrypt(string file, string key);
int main() {
	int choice = 0;
	cout << "Welcome to the encryption program" << endl;
	do {
		cout << "Enter 1 to encrypt a file\nEnter 2 to decrypt a file\nEnter 3 to exit" << endl;
		cin >> choice;
		while (choice > 3 || choice < 1) {
			cout << "Please reenter 1, 2 or 3..." << endl;
			cin >> choice;
		}
		//Choice to encrypt
		if (choice == 1) {
			string filepath;
			string key;
			cout << "Please enter an input file path and be exact" << endl;
			cin.ignore();
			getline(cin, filepath);
			cout << "Please enter a password" << endl;
			getline(cin, key);
			//Boolean method to see if file is found or not and if so it'll execute to encrypt
			while(!encrypt(filepath, key)) {
				cout << "Please re-enter the input file path..." << endl;
				getline(cin, filepath);
			}
		}
		//Choice to decrypt
		if (choice == 2) {
			string filepath;
			string key;
			cout << "Please enter an input file path and be exact" << endl;
			cin.ignore();
			getline(cin, filepath);
			cout << "Please enter a password" << endl;
			getline(cin, key);
			//Boolean method to see if file is found or not and if so it'll execute to decrypt
			while (!decrypt(filepath, key)) {
				cout << "Please re-enter the input file path..." << endl;
				getline(cin, filepath);
			}
		}
	} while ((choice == 1 || choice == 2)||choice != 3);
	system("pause");
	return 0;
}

bool encrypt(string file, string key) {
	ifstream inputfile;
	string str[20];
	string get;
	int i = 0;
	inputfile.open(file, ios::in);
	if (!inputfile) {
		cout << "Error: could not open file" << endl;
		return false;
	}
	while (!inputfile.eof()) {
		getline(inputfile, get);
		str[i++] = get;
	}
	inputfile.close();
	//For loop to put the str array into a string, then the password will iterate through each index of the password and each index of the string. 
	for (i = 0; i < sizeof(str); i++) {
		int j = 0, l=0;
		string line = str[i];
		if (line == "") {
			break;
		}		while (key.length() > j) {
			line.at(l++) += key.at(j++);
			if (j == key.length()) {
				j = 0;
			}
			if (line.length() == l) {
				break;
			}
		}
		str[i] = line;
	}
	ofstream outputFile;
	outputFile.open(file, ios::trunc);
	if (!outputFile) {
		outputFile.open(file, ios::out);
		return false;
	}
	//I put an if statement for when the empty string array is found that it will stop outputing to the file instead of creating more lines and possibly causing errors.
	for (i = 0; i < sizeof(str); i++) {
		if (str[i] != "") {
			outputFile << str[i] << endl;
		}
		else {
			break;
		}
	}
	outputFile.close();
	return true;
}
bool decrypt(string file, string key) {
	ifstream inputfile;
	string str[20];
	string get;
	int i = 0;
	inputfile.open(file, ios::in);
	if (!inputfile) {
		cout << "Error: could not open file" << endl;
		return false;
	}
	while (!inputfile.eof()) {
		getline(inputfile, get);
		str[i++] = get;
	}
	inputfile.close();

	for (i = 0; i < sizeof(str); i++) {
		int j = 0, l = 0;
		string line = str[i];
		if (line == "") {
			break;
		}		while (key.length() > j) {
			line.at(l++) -= key.at(j++);
			if (j == key.length()) {
				j = 0;
			}
			if (line.length() == l) {
				break;
			}
		}
		str[i] = line;
	}
	ofstream outputFile;
	outputFile.open(file, ios::trunc);
	if (!outputFile) {
		outputFile.open(file, ios::out);
		return false;
	}
	for (i = 0; i < sizeof(str); i++) {
		if (str[i] != "") {
			outputFile << str[i] << endl;
		}
		else {
			break;
		}
	}
	outputFile.close();
	return true;
}