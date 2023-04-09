#include <iostream>
#include <fstream>
using namespace std;

int main_menu(int &option);
void user_register();
void user_login();

int main() {
	int option = 0;

	main_menu(option);

	if (option == 1) {
		user_register();
	}

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
	}

	outFile.close();
}

int main_menu(int &option) {
	cout << "Menu: " << endl;
	cout << "1. Register" << endl;
	cout << "2. Login" << endl;
	cout << "\nEnter your option: ";
	cin >> option;

	return option;
}

void user_login() {

}