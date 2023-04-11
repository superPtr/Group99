#include <iostream>
#include <fstream>
#include<string>
using namespace std;

struct LoginCred {
	string username;
	string password;
};

int main_menu(int &option);
void user_register();
void user_login();

int main() {
	int option;
	bool chkpoint = false;

	do {
		main_menu(option);

		if (option == 1) {
			user_register();
		}
		else if (option == 2) {
			user_login();
		}
		else if (option == 3) {
			chkpoint = true;
		}
		else {
			cout << "Please try again!" << endl;
		}

	} while (chkpoint == false);

	return 0;
}

void user_register() {
	// fstream object
	ofstream outFile;
	outFile.open("user.txt", ios::app);

	// declare : username | password | email
	string username, password, email;

	// check whether can open targeted file 
	if (outFile.fail()) {
		cout << "Unable to open user.txt!" << endl;
	}
	else {
		// let user input required info
		cout << "Enter username (must not have spaces): ";
		cin >> username;
		cout << "Enter your email: ";
		cin >> email;
		cout << "Enter password: ";
		cin >> password;

		//output required data into user.txt
		outFile << username << "|" << password << "|" << email << "|" << endl;
		cout << "\nRegistration successful!" << endl;
		cout << endl;
	}

	outFile.close();
}

int main_menu(int &option) {
	cout << "Menu: " << endl;
	cout << "1. Register" << endl;
	cout << "2. Login" << endl;
	cout << "3. Exit" << endl;
	cout << "\nEnter your option: ";
	cin >> option;
	cout << endl;

	return option;
}

void user_login() {
	ifstream inFile;
	inFile.open("user.txt");

	LoginCred user;

	string temp_name, temp_pass;
	bool checking = false;

	cout << "Enter username: ";
	cin >> user.username;
	cout << "Enter Password: ";
	cin >> user.password;

	if (inFile.fail()) {
		cout << "Unable to open user.txt!" << endl;
	}
	else {
		while ((checking == false) && (!inFile.eof())) {
			getline(inFile, temp_name, '|');
			getline(inFile, temp_pass, '|');

			if ((user.username == temp_name) && (user.password == temp_pass)) {
				checking = true;
				cout << "Successfully Login!" << endl;
				cout << endl;
				break;
			}

			inFile.ignore(256, '|');
			inFile.ignore(256, '\n');
		}

		if (checking == false) {
			cout << "Your username or password is incorrect!" << endl;
		}
	}

	inFile.close();
}