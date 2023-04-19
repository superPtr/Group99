#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h> //decoration purpose - system
#include <stdio.h> //decoration purpose - printf
using namespace std;

const int Max_Size = 100;

struct User {
	string username;
	string password;
	string email;
};

struct Flight {
	string flight_id;
	string from_location;
	string to_location;
	string departure_day;
	string departure_time;
	string arrival_time;
	string flight_duration;
	string flight_price_eco;
	string numSeats_eco;
	string flight_price_bus;
	string numSeats_bus;
};

struct Record {
	string ticket_id;
	string class_id;
	Flight flightInfo;
	// string purchased_day
	string payment_status;
	string name;
	string contact_num;
	string email;
};

int main_menu(int& option);
void user_menu(User user);
void admin_menu();
void user_register();
void user_login();
bool isValidNameOrPass(string nameOrPass);
bool isValidEmail(const User& user);
bool avoidSame(string nameOrEmail, const User(&userLists)[Max_Size]);
void grabUser(User(&userLists)[Max_Size]);
void grabFlight(Flight (&flightLists)[Max_Size], string fileName, bool goPrint);
void grabRecord(Record (&recordLists)[Max_Size], string fileName, bool goPrint, string email);
string toLower(string keyword);
void user_search();
string minToHourMin(string duration);
// decorations
void loadingBar();

int main() {
	system("COLOR 0e");
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
			Flight flightLists[Max_Size];
			loadingBar();
			grabFlight(flightLists, "flight.txt", true);
		}
		else if (option == 4) {
			// Admin Login
		}
		else if (option == 5) {
			chkpoint = true;
		}
		else {
			cout << "Please try again!" << endl;
		}

	} while (chkpoint == false);


	return 0;
}

int main_menu(int& option) {
	cout << "Menu: " << endl;
	cout << "1. Non-User Register" << endl;
	cout << "2. User Login" << endl;
	cout << "3. View Flight Info" << endl;
	cout << "4. Admin Login" << endl;
	cout << "5. Exit" << endl;
	cout << "\nEnter your option: ";
	cin >> option;
	cout << endl;

	return option;
}

void user_menu(User user) {	// User user is current user's info
	int choice;
	bool chkpoint = false;
	User currUser;
	currUser.email = user.email;
	Flight flightLists[Max_Size];;
	Record recordLists[Max_Size]; 

	do{
		cout << "1. View Flight Info" << endl;
		cout << "2. Search Flight" << endl;
		cout << "3. Booking Flight" << endl;
		cout << "4. View Booking/Purchased History" << endl;
		cout << "5. Logout" << endl;
		cout << "\nEnter your option: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:		// View Flight
			loadingBar();
			grabFlight(flightLists, "flight.txt", true);
			break;
		case 2:		// Search
			user_search();
			break;
		case 3:		// Booking
			break;
		case 4:		// View History
			grabRecord(recordLists, "record.txt", false, currUser.email);
			break;
		case 5:
			chkpoint = true;
			break;
		default:
			cout << "Please Enter the Valid Choice." << endl;
			break;
		}
	}while (chkpoint == false);
	
}

void admin_menu() {
	int choice;
	bool chkpoint = false;
	Flight flightLists[Max_Size];
	Record recordLists[Max_Size];

	do {
		cout << "1. View Flight Info" << endl;
		cout << "2. View Purchased Flight Record" << endl;
		cout << "3. Search" << endl;
		cout << "4. Logout" << endl;
		cout << "\nEnter your option: ";
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 1:
			loadingBar();
			grabFlight(flightLists, "flight.txt", true);
			break;
		case 2:
			// View record
			grabRecord(recordLists, "record.txt", true, "0");
			break;
		case 3:
			// Search
			break;
		case 4:
			// logout
			chkpoint = true;
			break;
		default:
			cout << "Please Enter the Valid Choice." << endl;
			break;
		}

	} while (chkpoint == false);
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
		cout << "Registration Successful!" << endl;
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
			User currentUser;
			currentUser.username = userLists[i].username;
			currentUser.email = userLists[i].email;
			cout << "Successfuly Login!" << endl;
			cout << endl;
			user_menu(currentUser);
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

void grabFlight(Flight (&flightLists)[Max_Size], string fileName, bool goPrint) {
	ifstream inFile;
	inFile.open(fileName);

	int count = 0;

	if (inFile.fail()) {
		cout << "Unable to Read Data!" << endl;
	}
	else {
		while (!inFile.eof()) {
			getline(inFile, flightLists[count].flight_id, '|');
			getline(inFile, flightLists[count].from_location, '|');
			getline(inFile, flightLists[count].to_location, '|');
			getline(inFile, flightLists[count].departure_day, '|');
			getline(inFile, flightLists[count].departure_time, '|');
			getline(inFile, flightLists[count].arrival_time, '|');
			getline(inFile, flightLists[count].flight_duration, '|');
			getline(inFile, flightLists[count].flight_price_eco, '|');
			getline(inFile, flightLists[count].numSeats_eco, '|');
			getline(inFile, flightLists[count].flight_price_bus, '|');
			getline(inFile, flightLists[count].numSeats_bus, '|');

			inFile.ignore(256, '\n');

			count++;
		}
		if(goPrint == true){
			cout <<setw(10)<<left<< "FlightID ";		// flight id
			cout << left << "From ";		//from_location
			cout << left << "To ";		//to_location
			cout << left << "Depart_Day " ;		//departure_day
			cout << left << "Depart_Time " ;		//arrival_time
			cout << left << "Arria_Time " ;		//flight_duration
			cout << left << "Duration " ;		//flight_price_eco
			cout << left << "Price(Eco) " ;		//numSeats_eco
			cout << left << "Avai_Seats(Eco)" ;		//flight_price_bus
			cout << left << "Price(Bus)" ;		//numSeats_bus
			cout << left << "Avai_Seats(Bus)" << endl;
			cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
			for (int i = 0; i < (count - 1); i++) {
				cout << setw(8) << left << flightLists[i].flight_id;
				cout << setw(12) << left << flightLists[i].from_location;
				cout << setw(12) << left << flightLists[i].to_location;
				cout << setw(10) << left << flightLists[i].departure_day;
				cout << setw(6) << left << flightLists[i].departure_time;
				cout << setw(6) << left << flightLists[i].arrival_time;
				string duration = minToHourMin(flightLists[i].flight_duration);
				cout << setw(14) << left << duration;
				cout << setw(9) << left << flightLists[i].flight_price_eco;
				cout << setw(10) << left << flightLists[i].numSeats_eco;
				cout << setw(9) << left << flightLists[i].flight_price_bus;
				cout << setw(10) << left << flightLists[i].numSeats_bus << endl;
			}
		}
	}
	inFile.close();
}

void grabRecord(Record (&recordLists)[Max_Size], string fileName, bool goPrint, string email) {
	ifstream inFile;
	inFile.open(fileName);

	int count = 0;

	if (inFile.fail()) {
		cout << "Unable Read the Data!" << endl;
	}
	else {
		while (!inFile.eof()) {
			getline(inFile, recordLists[count].ticket_id, '|');
			getline(inFile, recordLists[count].flightInfo.flight_id, '|');
			getline(inFile, recordLists[count].class_id, '|');
			getline(inFile, recordLists[count].flightInfo.departure_time, ':');
			getline(inFile, recordLists[count].flightInfo.arrival_time, ':');
			getline(inFile, recordLists[count].flightInfo.flight_duration, '|');
			getline(inFile, recordLists[count].flightInfo.departure_day, '|');
			getline(inFile, recordLists[count].payment_status, '|');
			getline(inFile, recordLists[count].name, '|');
			getline(inFile, recordLists[count].contact_num, '|');
			getline(inFile, recordLists[count].email, '|');

			inFile.ignore(256, '\n');
			count++;
		}

		if (goPrint == true) {
			for (int i = 0; i < (count - 1); i++) {
				cout << setw(10) << left << recordLists[i].ticket_id;
				cout << setw(8) << left << recordLists[i].flightInfo.flight_id;
				cout << setw(4) << left << recordLists[i].class_id;
				cout << setw(10) << left << recordLists[i].flightInfo.departure_time;
				cout << setw(6) << left << recordLists[i].flightInfo.arrival_time;
				cout << setw(6) << left << recordLists[i].flightInfo.flight_duration;
				cout << setw(10) << left << recordLists[i].flightInfo.departure_day;
				cout << setw(20) << left << recordLists[i].name;
				cout << setw(12) << left << recordLists[i].contact_num;
				cout << setw(20) << left << recordLists[i].email << endl;

			}
		}
		else if ((goPrint == false) && (email != "0")) {
			bool chkEmpty = true;
			string searchByEmail = email;
			for (int j = 0; j < (count - 1); j++) {
				if (recordLists[j].email == searchByEmail) {
					cout << setw(10) << left << recordLists[j].ticket_id;
					cout << setw(8) << left << recordLists[j].flightInfo.flight_id;
					cout << setw(4) << left << recordLists[j].class_id;
					cout << setw(10) << left << recordLists[j].flightInfo.departure_time;
					cout << setw(6) << left << recordLists[j].flightInfo.arrival_time;
					cout << setw(6) << left << recordLists[j].flightInfo.flight_duration;
					cout << setw(10) << left << recordLists[j].flightInfo.departure_day;
					cout << setw(20) << left << recordLists[j].name;
					cout << setw(12) << left << recordLists[j].contact_num;
					cout << setw(20) << left << recordLists[j].email << endl;

					chkEmpty = false;
				}
			}
			if (chkEmpty == true) {
				cout << "Your purchased history is empty." << endl;
			}
		}
	}
	inFile.close();
}

string toLower(string keyword) {
	string words = keyword;

	for (int i = 0; i < words.length(); i++) {
		if ((words[i] >= 'A') && (words[i] <= 'Z')) {
			words[i] = words[i] - 'A' + 'a';
		}
	}

	return words;
}

void user_search() {
	Flight flightLists[Max_Size];
	grabFlight(flightLists, "flight.txt", false);

	string keyword;
	int option;

	cout << "Search for:" << endl;
	cout << "1. Departure Location" << endl;
	cout << "2. Arrival Loction" << endl;
	cout << "Enter option: ";
	cin >> option;

	if (option == 1) {
		cout << "Enter location: ";
		cin >> keyword;
		cout << endl;
		bool flag = false;
		for (int j = 0; j < Max_Size; j++) {
			if ((toLower(keyword)) == (toLower(flightLists[j].from_location))) {
				cout << setw(8) << left << flightLists[j].flight_id;
				cout << setw(12) << left << flightLists[j].from_location;
				cout << setw(12) << left << flightLists[j].to_location;
				cout << setw(10) << left << flightLists[j].departure_time;
				cout << setw(6) << left << flightLists[j].arrival_time;
				cout << setw(14) << left << flightLists[j].flight_duration;
				cout << setw(9) << left << flightLists[j].flight_price_eco;
				cout << setw(10) << left << flightLists[j].numSeats_eco;
				cout << setw(9) << left << flightLists[j].flight_price_bus;
				cout << setw(10) << left << flightLists[j].numSeats_bus << endl;

				flag = true;
			}
		}

		if (flag == false) {
			cout << "There is no such location provided by us!" << endl;
		}
	}
	else if (option == 2) {
		cout << "Enter location: ";
		cin >> keyword;
		cout << endl;
		bool flag = false;

		for (int j = 0; j < Max_Size; j++) {
			if ((toLower(keyword)) == (toLower(flightLists[j].to_location))) {
				cout << setw(8) << left << flightLists[j].flight_id;
				cout << setw(12) << left << flightLists[j].from_location;
				cout << setw(12) << left << flightLists[j].to_location;
				cout << setw(10) << left << flightLists[j].departure_time;
				cout << setw(6) << left << flightLists[j].arrival_time;
				cout << setw(14) << left << flightLists[j].flight_duration;
				cout << setw(9) << left << flightLists[j].flight_price_eco;
				cout << setw(10) << left << flightLists[j].numSeats_eco;
				cout << setw(9) << left << flightLists[j].flight_price_bus;
				cout << setw(10) << left << flightLists[j].numSeats_bus << endl;

				flag = true;
			}
		}

		if (flag == false) {
			cout << "There is no such location provided by us!" << endl;
		}
	}

}

string minToHourMin(string duration) {
	int hour, min, temp_min;
	string temp_duration = duration;
	string flight_duration;
	temp_min = stoi(duration);
	hour = temp_min / 60;
	min = temp_min % 60;
	flight_duration = to_string(hour) + "hour(s) " + to_string(min) + "min(s)";

	return flight_duration;
}

// decoration
void loadingBar() {
	system("COLOR 0e");
	system("cls");
	//printf("\e[?25l");

	//Set ASCII to print special character.
	//Code page 437
	SetConsoleCP(437);
	SetConsoleOutputCP(437);
	int bar1 = 177, bar2 = 219;

	cout << "\n\n\n\t\t\t\tLoading...";
	cout << "\n\n\n\t\t\t\t";

	for (int i = 0; i < 25; i++)
		cout << (char)bar1;

	cout << "\r";
	cout << "\t\t\t\t";
	for (int i = 0; i < 25; i++)
	{
		cout << (char)bar2;
		Sleep(150);
	}

	system("cls");
}