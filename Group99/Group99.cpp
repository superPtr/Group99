#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h> //decoration purpose - system
#include <stdio.h> //decoration purpose - printf
#include <cstdlib> 
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

string generateID(string to_location, string from_location, int selection);
int main_menu(int& option);
void user_menu(User user);
void admin_menu();
int adminMenu_flight();
void user_register();
void user_login(bool chkAdmin);
bool isValidNameOrPass(string nameOrPass);
bool isValidEmail(const User& user);
bool avoidSame(string nameOrEmail, const User(&userLists)[Max_Size]);
void grabUser(User(&userLists)[Max_Size]);
void grabFlight(Flight(&flightLists)[Max_Size], string fileName, bool goPrint);
void grabRecord(Record(&recordLists)[Max_Size], string fileName, bool goPrint, string email);
string toLower(string keyword);
void user_search();
void admin_search(int option);
string minToHourMin(string duration);
int adminSearchMenu();
int adminUpdateMenu();
void admin_update(int section);
int countLine(string file_name);
void drop(bool chkAdm, int selection);
void addFlight();
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
			user_login(false);
		}
		else if (option == 3) {
			Flight flightLists[Max_Size];
			loadingBar();
			grabFlight(flightLists, "flight.txt", true);
		}
		else if (option == 4) {
			user_login(true);
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

	do {
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
	} while (chkpoint == false);

}

void admin_menu() {
	int choice, action = 0, section, section2;
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
			section = adminMenu_flight();
			if (section == 1) {
				section2 = adminUpdateMenu();
				admin_update(section2);
			}
			else if (section == 2) {
				drop(true, 1);
			}
			else if (section == 3) {
				addFlight();
			}
			else {
				cout << "Invalid!" << endl;
			}
			break;
		case 2:
			// View record
			grabRecord(recordLists, "record.txt", true, "0");
			break;
		case 3:
			// Search
			action = adminSearchMenu();
			if (action == 1) {
				//flight id
				admin_search(1);
			}
			else if (action == 2) {
				//ticket id
				admin_search(2);
			}
			else if (action == 3) {
				// location
				user_search();
			}
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

int adminMenu_flight() {
	int action2;

	cout << endl;
	cout << "Press 1 to Update Specific Record" << endl;
	cout << "Press 2 to Delete Specific Record" << endl;
	cout << "Press 3 to Add New Record" << endl;
	cout << "Press any character to return back except 1 & 2 & 3." << endl;
	cout << "Enter option: ";
	cin >> action2;

	return action2;
}

string generateID(string from_location, string to_location, int selection) {
	string temp, temp2, temp3, id;
	int randNum = rand() % 900 + 100;	// generate 3-digit numbers
	
	if (selection == 1) {
		//temp
		if (toLower(from_location) == "brunei") {
			temp = "BN";
		}
		else if (toLower(from_location) == "comboida") {
			temp = "KH";
		}
		else if (toLower(from_location) == "east timor") {
			temp = "TL";
		}
		else if (toLower(from_location) == "indonesia") {
			temp = "ID";
		}
		else if (toLower(from_location) == "laos") {
			temp = "LA";
		}
		else if (toLower(from_location) == "malaysia") {
			temp = "MY";
		}
		else if (toLower(from_location) == "myanmar") {
			temp = "MM";
		}
		else if (toLower(from_location) == "philippines") {
			temp = "PH";
		}
		else if (toLower(from_location) == "singapore") {
			temp = "SG";
		}
		else if (toLower(from_location) == "thailand") {
			temp = "TH";
		}
		else if (toLower(from_location) == "vietam") {
			temp = "VN";
		}
		else {
			temp = "XX";
		}
		// temp2
		if (toLower(to_location) == "brunei") {
			temp2 = "BN";
		}
		else if (toLower(to_location) == "comboida") {
			temp2 = "KH";
		}
		else if (toLower(to_location) == "east timor") {
			temp2 = "TL";
		}
		else if (toLower(to_location) == "indonesia") {
			temp2 = "ID";
		}
		else if (toLower(to_location) == "laos") {
			temp2 = "LA";
		}
		else if (toLower(to_location) == "malaysia") {
			temp2 = "MY";
		}
		else if (toLower(to_location) == "myanmar") {
			temp2 = "MM";
		}
		else if (toLower(to_location) == "philippines") {
			temp2 = "PH";
		}
		else if (toLower(to_location) == "singapore") {
			temp2 = "SG";
		}
		else if (toLower(to_location) == "thailand") {
			temp2 = "TH";
		}
		else if (toLower(to_location) == "vietam") {
			temp2 = "VN";
		}
		else {
			temp2 = "XX";
		}

		temp3 = to_string(randNum);
		id = temp + temp3 + temp2;
	}
	
	return id;
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

void user_login(bool chkAdmin) {
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

	if (chkAdmin != true) {
		for (int j = 3; j < listLength; j++) {
			if ((loginCred.username == userLists[j].username) && (loginCred.password == userLists[j].password)) {
				chkLog = true;
				User currentUser;
				currentUser.username = userLists[j].username;
				currentUser.email = userLists[j].email;
				cout << "Successfuly Login!" << endl;
				cout << endl;
				user_menu(currentUser);
			}
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			if ((loginCred.username == userLists[i].username) && (loginCred.password == userLists[i].password)) {
				chkLog = true;
				cout << "Welcome, Admin." << endl;
				cout << endl;
				admin_menu();
			}
		}
	}

	if (chkLog == false) {
		cout << "Username or Password is incorrect, please try again!" << endl;
	}


}

int countLine(string file_name) {
	int count = 0;
	string line;
	ifstream readFile;
	readFile.open(file_name);

	while (getline(readFile, line)) {
		count++;
	}

	readFile.close();

	return count;
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

void grabFlight(Flight(&flightLists)[Max_Size], string fileName, bool goPrint) {
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
		if (goPrint == true) {
			cout << setw(10) << left << "FlightID ";		// flight id
			cout << left << "From ";		//from_location
			cout << left << "To ";		//to_location
			cout << left << "Depart_Day ";		//departure_day
			cout << left << "Depart_Time ";		//arrival_time
			cout << left << "Arria_Time ";		//flight_duration
			cout << left << "Duration ";		//flight_price_eco
			cout << left << "Price(Eco) ";		//numSeats_eco
			cout << left << "Avai_Seats(Eco)";		//flight_price_bus
			cout << left << "Price(Bus)";		//numSeats_bus
			cout << left << "Avai_Seats(Bus)" << endl;
			cout << "-----------------------------------------------------------------------------------------------------------------" << endl;
			for (int i = 0; i < (count - 1); i++) {
				if (flightLists[i].flight_id != "000000") {
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
	}
	inFile.close();
}

void grabRecord(Record(&recordLists)[Max_Size], string fileName, bool goPrint, string email) {
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
				if (recordLists[i].ticket_id != "000000") {
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
		}
		else if ((goPrint == false) && (email != "0")) {
			bool chkEmpty = true;
			string searchByEmail = email;
			for (int j = 0; j < (count - 1); j++) {
				if ((recordLists[j].email == searchByEmail) && (recordLists[j].ticket_id != "000000")) {
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

void admin_search(int option) {
	string keyword;
	bool flag = false;

	if (option == 1) {
		// flight id
		Flight flightLists[Max_Size];
		grabFlight(flightLists, "flight.txt", false);

		cout << "Enter Flight ID: ";
		cin >> keyword;
		cout << endl;
		for (int i = 0; i < Max_Size; i++) {
			if (keyword == flightLists[i].flight_id) {
				cout << setw(8) << left << flightLists[i].flight_id;
				cout << setw(12) << left << flightLists[i].from_location;
				cout << setw(12) << left << flightLists[i].to_location;
				cout << setw(10) << left << flightLists[i].departure_time;
				cout << setw(6) << left << flightLists[i].arrival_time;
				cout << setw(14) << left << flightLists[i].flight_duration;
				cout << setw(9) << left << flightLists[i].flight_price_eco;
				cout << setw(10) << left << flightLists[i].numSeats_eco;
				cout << setw(9) << left << flightLists[i].flight_price_bus;
				cout << setw(10) << left << flightLists[i].numSeats_bus << endl;

				flag = true;
			}
		}

		if (flag == false) {
			cout << "There is no such Flight ID in the record!" << endl;
		}

	}
	else {
		// ticket id
		Record recordLists[Max_Size];
		grabRecord(recordLists, "record.txt", false, "0");

		cout << "Enter Ticket ID: ";
		cin >> keyword;
		cout << endl;

		for (int j = 0; j < Max_Size; j++) {
			if (keyword == recordLists[j].ticket_id) {
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

				flag = true;
			}
		}

		if (flag == false) {
			cout << "There is no such Ticket ID in the record!" << endl;
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

int adminSearchMenu() {
	int option;
	cout << "Search by: " << endl;
	cout << "1. Flight ID" << endl;
	cout << "2. Ticket ID" << endl;
	cout << "3. Location" << endl;
	cout << "Enter option: ";
	cin >> option;

	return option;
}

int adminUpdateMenu() {
	int section;
	cout << "1. Departure Location" << endl;
	cout << "2. Arriaval Location" << endl;
	cout << "3. Departure Day" << endl;
	cout << "4. Departure Time" << endl;
	cout << "5. Arrival Time" << endl;
	cout << "6. Flight Duration" << endl;
	cout << "7. Price(Eco)" << endl;
	cout << "8. Available Seats(Eco)" << endl;
	cout << "9. Price(Bus)" << endl;
	cout << "10. Available Seats(Bus)" << endl;
	cout << "Enter which part of the record that want to update: ";
	cin >> section;
	cout << endl;

	return section;
}

void admin_update(int section) {
	string flightID, temp;
	bool flag = false;
	int count;
	string fileName = "flight.txt";
	count = countLine(fileName);
	Flight flightLists[Max_Size];

	grabFlight(flightLists, fileName, false);

	cout << "Enter Flight ID of the record: ";
	cin >> flightID;
	cout << endl;

	for (int i = 0; i < Max_Size; i++) {
		if (flightID == flightLists[i].flight_id) {
			flag = true;
			cout << "Enter data: ";
			cin >> temp;
			if ((section - 1) == 0) {
				flightLists[i].from_location = temp;
			}
			else if ((section - 1) == 1) {
				flightLists[i].to_location = temp;
			}
			else if ((section - 1) == 2) {
				flightLists[i].departure_day = temp;
			}
			else if ((section - 1) == 3) {
				flightLists[i].departure_time = temp;
			}
			else if ((section - 1) == 4) {
				flightLists[i].arrival_time = temp;
			}
			else if ((section - 1) == 5) {
				flightLists[i].flight_duration = temp;
			}
			else if ((section - 1) == 6) {
				flightLists[i].flight_price_eco = temp;
			}
			else if ((section - 1) == 7) {
				flightLists[i].numSeats_eco = temp;
			}
			else if ((section - 1) == 8) {
				flightLists[i].flight_price_bus = temp;
			}
			else if ((section - 1) == 9) {
				flightLists[i].numSeats_bus = temp;
			}
			else {
				cout << "Unable to Update!" << endl;
			}
		}

	}

	if (flag == false) {
		cout << "Flight ID is invalid!" << endl;
	}
	else {
		ofstream outFile;
		outFile.open("flight.txt", ios::out);
		if (outFile.fail()) {
			cout << "Unable to Update!" << endl;
		}
		else {
			for (int j = 0; j < count; j++) {
				outFile << flightLists[j].flight_id << "|" << flightLists[j].from_location << "|" << flightLists[j].to_location << "|" << flightLists[j].departure_day << "|"
					<< flightLists[j].departure_time << "|" << flightLists[j].arrival_time << "|" << flightLists[j].flight_duration << "|" << flightLists[j].flight_price_eco
					<< "|" << flightLists[j].numSeats_eco << "|" << flightLists[j].flight_price_bus << "|" << flightLists[j].numSeats_bus << "|" << endl;
			}
			cout << "Successfully Updated!" << endl;
			outFile.close();
		}
		
	}

}

void drop(bool chkAdm, int selection) {
	int count, count2;
	count = countLine("flight.txt");
	count2 = countLine("record.txt");
	string id, temp;
	bool flag = false;

	if (chkAdm == true) {
		// admin
		// selection
		/*cout << "Select which record to delete: " << endl;
		cout << "1. Flight Record" << endl;
		cout << "2. Purchased Record" << endl;
		cout << "--Enter Any Character to Return Back except 1 & 2--" << endl;
		cout << "Enter selection: " << endl;
		cin >> selection;
		cout << endl;*/

		if (selection == 1) {
			cout << "Enter Flight ID: ";
			cin >> id;
			cout << endl;

			Flight flightLists[Max_Size];
			grabFlight(flightLists, "flight.txt", false);
			Record recordLists[Max_Size];
			grabRecord(recordLists, "record.txt", false, "0");

			for (int i = 0; i < count; i++) {
				if (id == flightLists[i].flight_id) {
					temp = flightLists[i].flight_id;
					flightLists[i].flight_id = "000000";
					for (int a = 0; a < count2; a++) {
						if (temp == recordLists[a].flightInfo.flight_id) {
							recordLists[a].ticket_id = "000000";
						}
					}
					flag = true;
				}
			}

			if (flag = false) {
				cout << "Flight ID is invalid!" << endl;
			}
			else {
				ofstream outFile;
				ofstream outFile2;
				outFile.open("flight.txt");
				outFile2.open("record.txt");
				for (int j = 0; j < count; j++) {
					outFile << flightLists[j].flight_id << "|" << flightLists[j].from_location << "|" << flightLists[j].to_location << "|" << flightLists[j].departure_day << "|"
						<< flightLists[j].departure_time << "|" << flightLists[j].arrival_time << "|" << flightLists[j].flight_duration << "|" << flightLists[j].flight_price_eco
						<< "|" << flightLists[j].numSeats_eco << "|" << flightLists[j].flight_price_bus << "|" << flightLists[j].numSeats_bus << "|" << endl;
				}
				for (int k = 0; k < count2; k++) {
					outFile2 << recordLists[k].ticket_id << "|" << recordLists[k].flightInfo.flight_id << "|" << recordLists[k].class_id << "|" << recordLists[k].flightInfo.departure_time << ":"
						<< recordLists[k].flightInfo.arrival_time << ":" << recordLists[k].flightInfo.flight_duration << "|" << recordLists[k].flightInfo.departure_day << "|" << recordLists[k].payment_status
						<< "|" << recordLists[k].name << "|" << recordLists[k].contact_num << "|" << recordLists[k].email << "|" << endl;
				}
				cout << "Successfully Deleted!" << endl;
				outFile.close();
				outFile2.close();
			}
		}
		else if (selection == 2) {
			string temp2, temp4;
			int temp3;
			cout << "Enter Ticket ID: ";
			cin >> id;
			cout << endl;

			Record recordLists[Max_Size];
			grabRecord(recordLists, "record.txt", false, "0");
			Flight flightLists[Max_Size];
			grabFlight(flightLists, "flight.txt", false);

			for (int i = 0; i < count2; i++) {
				if (id == recordLists[i].ticket_id) {
					temp = recordLists[i].flightInfo.flight_id;
					temp2 = recordLists[i].class_id;
					recordLists[i].ticket_id = "000000";
					for (int j = 0; j < count; j++) {
						if (temp == flightLists[j].flight_id) {
							if (stoi(temp2) == 1) {	// eco
								temp3 = stoi(flightLists[i].numSeats_eco);
								++temp3;
								temp4 = to_string(temp3);
								flightLists[j].numSeats_eco = temp4;
							}
							else if (stoi(temp2) == 2) { // bus
								temp3 = stoi(flightLists[i].numSeats_bus);
								++temp3;
								temp4 = to_string(temp3);
								flightLists[j].numSeats_bus = temp4;
							}
						}
					}
					flag = true;
				}
			}
			
			if (flag == false) {
				cout << "Ticket ID is invalid!" << endl;
			}
			else {
				ofstream outFile;
				outFile.open("record.txt");
				ofstream outFile2;
				outFile2.open("flight.txt");

				for (int k = 0; k < count2; k++) {
					outFile2 << recordLists[k].ticket_id << "|" << recordLists[k].flightInfo.flight_id << "|" << recordLists[k].class_id << "|" << recordLists[k].flightInfo.departure_time << ":"
						<< recordLists[k].flightInfo.arrival_time << ":" << recordLists[k].flightInfo.flight_duration << "|" << recordLists[k].flightInfo.departure_day << "|" << recordLists[k].payment_status
						<< "|" << recordLists[k].name << "|" << recordLists[k].contact_num << "|" << recordLists[k].email << "|" << endl;
				}
				for (int l = 0; l < count; l++) {
					outFile2 << flightLists[l].flight_id << "|" << flightLists[l].from_location << "|" << flightLists[l].to_location << "|" << flightLists[l].departure_day << "|"
						<< flightLists[l].departure_time << "|" << flightLists[l].arrival_time << "|" << flightLists[l].flight_duration << "|" << flightLists[l].flight_price_eco
						<< "|" << flightLists[l].numSeats_eco << "|" << flightLists[l].flight_price_bus << "|" << flightLists[l].numSeats_bus << "|" << endl;
				}
				cout << "Successfully Deleted!" << endl;
				outFile.close();
				outFile2.close();
			}
		}
	}
	else {
		//user
	}
}

void addFlight() {
	Flight newFlight;
	string tempID;
	ofstream outFile;
	outFile.open("flight.txt", ios::app);

	cout << setw(30) << "Schedule A Flight" << endl;
	cout << "*****************************************" << endl;
	cout << endl;

	if (!outFile.fail()) {
		cin.ignore(256, '\n');
		cout << "Enter Departure Location: ";
		getline(cin, newFlight.from_location, '\n');
		cout << "\nEnter Arrival Location: ";
		getline(cin, newFlight.to_location, '\n');
		cout << "\nEnter Day of Departure: ";
		getline(cin, newFlight.departure_day, '\n');
		cout << "\nEnter Departure Time: ";
		getline(cin, newFlight.departure_time, '\n');
		cout << "\nEnter Arrival Time: ";
		getline(cin, newFlight.arrival_time, '\n');
		cout << "\nEnter Duration of Flight: ";
		getline(cin, newFlight.flight_duration, '\n');
		cout << "\nEnter Price (Class: Economy): ";
		getline(cin, newFlight.flight_price_eco, '\n');
		cout << "\nEnter Number of Seats (Class: Economy): ";
		getline(cin, newFlight.numSeats_eco, '\n');
		cout << "\nEnter Price (Class: Business): ";
		getline(cin, newFlight.flight_price_bus, '\n');
		cout << "\nEnter NUmber of Seats (Class: Business: ";
		getline(cin, newFlight.numSeats_bus, '\n');
		cout << endl;

		tempID = generateID(newFlight.from_location, newFlight.to_location, 1);
		newFlight.flight_id = tempID;

		outFile << newFlight.flight_id << "|" << newFlight.from_location << "|" << newFlight.to_location << "|" << newFlight.departure_day << "|"
			<< newFlight.departure_time << "|" << newFlight.arrival_time << "|" << newFlight.flight_duration << "|" << newFlight.flight_price_eco
			<< "|" << newFlight.numSeats_eco << "|" << newFlight.flight_price_bus << "|" << newFlight.numSeats_bus << "|" << endl;


		cout << "****************************************" << endl;
		cout << "*Flight information has been updated. *" << endl;
		cout << "****************************************" << endl;
	}
	else {
		cout << "Unable To Add Record!" << endl;
	}
	outFile.close();
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

