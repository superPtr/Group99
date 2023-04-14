#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int Max_Size = 100;

struct User {
	string username;
	string password;
	string email;
};

int main_menu(int& option);
void user_register();
void user_login();
bool isValidNameOrPass(string nameOrPass);
bool isValidEmail(const User& user);
bool avoidSame(string nameOrEmail, const User(&userLists)[Max_Size]);
void grabUser(User(&userLists)[Max_Size]);

int main() {
	int option = 0;
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

	if (option == 1) {
		user_register();
	}
	else if (option == 2) {
		user_login();
	}

	return 0;
}

int main_menu(int& option) {
	cout << "Menu: " << endl;
	cout << "1. Register" << endl;
	cout << "2. Login" << endl;
	cout << "3. Exit" << endl;
	cout << "\nEnter your option: ";
	cin >> option;
	cout << endl;

	return option;
}

void user_register() {
	User userLists[Max_Size];
	grabUser(userLists);

	int listLength = sizeof(userLists) / sizeof(userLists[0]);
	bool toWrite = false;

	ofstream outFile;
	outFile.open("user.txt", ios::app);

	User user;
	cout << "**Length for Username is not more than 12 characters, must included at least 1 alphabet and 1 number!(no space)**" << endl;
	cout << "Enter your username: ";
	cin >> user.username;
	cin.ignore(256, '\n');
	cout << "**Length for Password is not more than 12 characters, must included at least 1 alphabet and 1 number!**" << endl;
	cout << "Enter new password: ";
	getline(cin, user.password);
	cout << "Enter your email : ";
	getline(cin, user.email);
	cout << endl;


	if ((user.username.length() < 13) && (user.password.length() < 13)) {
		if ((isValidNameOrPass(user.username)) && (avoidSame(user.username, userLists)) && (isValidNameOrPass(user.password)) && (isValidEmail(user)) && (avoidSame(user.email, userLists))) {
			toWrite = true;
		}
	}

	if (toWrite == true) {
		outFile << user.username << "|" << user.password << "|" << user.email << "|" << endl;
		cout << "\nRegistration Successful!" << endl;
	}
	else {
		cout << "Username or Password is invalid, please try again!" << endl;
	}

	outFile.close();
}

void user_login() {
	User userLists[Max_Size];
	grabUser(userLists);
	int listLength = sizeof(userLists) / sizeof(userLists[0]);
	User loginCred;
	string temp_name, temp_pass;
	bool chkLog = false;

	cout << "Enter username: ";
	cin >> loginCred.username;
	cin.ignore(256, '\n');
	cout << "Enter password: ";
	getline(cin, loginCred.password);

	for (int i = 0; i < listLength; i++) {
		if ((loginCred.username == userLists[i].username) && (loginCred.password == userLists[i].password)) {
			chkLog = true;
			cout << "Successfuly Login!" << endl;
			break;
		}
	}

	if (chkLog == false) {
		cout << "Username or Password is incorrect, please try again!" << endl;
	}
}

bool isValidNameOrPass(string nameOrPass) {
	bool chkAlpha = false;
	bool chkNum = false;
	bool chkSpace = true;

	for (int i = 0; i < nameOrPass.length(); i++) {
		if (isalpha(nameOrPass[i])) {
			chkAlpha = true;
		}
		else if (isdigit(nameOrPass[i])) {
			chkNum = true;
		}
		else if (isspace(nameOrPass[i])) {
			chkSpace = false;
		}
	}

	return (chkAlpha && chkNum && chkSpace);
}

bool isValidEmail(const User& user) {
	bool chk = isValidNameOrPass(user.email);
	bool chk2 = false;
	bool chk3 = false;
	for (int i = 0; i < user.email.length(); i++) {
		if (user.email[i] == '@') {
			chk2 = true;
		}
		if (user.email[i] == '.') {
			chk3 = true;
		}
	}

	return (chk && chk2 && chk3);
}

bool avoidSame(string nameOrEmail, const User(&userLists)[Max_Size]) {
	bool chk = true;
	bool chk2 = true;

	int listLength = sizeof(userLists) / sizeof(userLists[0]);

	for (int i = 0; i < listLength; i++) {
		if (nameOrEmail == userLists[i].username) {
			chk = false;
		}
		if (nameOrEmail == userLists[i].email) {
			chk2 = false;
		}
	}

	return (chk && chk2);
}

void grabUser(User(&userLists)[Max_Size]) {
	int count = 0;

	ifstream inFile;
	inFile.open("user.txt");

	while (!inFile.eof()) {
		getline(inFile, userLists[count].username, '|');
		getline(inFile, userLists[count].password, '|');
		getline(inFile, userLists[count].email, '|');

		inFile.ignore(256, '\n');
		count++;
	}

	inFile.close();
}
