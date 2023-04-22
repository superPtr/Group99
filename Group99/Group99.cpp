#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <Windows.h> //decoration purpose 
#include <stdio.h> //decoration purpose 
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
	string ticNum;
	string payment_status;
	string totalBill;
	string name;
	string contact_num;
	string email;
};

string generateID(string to_location, string from_location, int selection);
int main_menu(int& option);
void user_menu(User user);
void booking_menu(string email, int selection);
void admin_menu();
int adminMenu_flight();
void user_register();
void user_login(bool chkAdmin);
void user_booking(int selection, string email);
bool payment(int totalBill);
void seatDeduction(string flightID, int tickNum, int classID);
bool isValidCreditCard(char creditCard[], int size);
bool isValidNameOrPass(string nameOrPass);
bool isValidEmail(const User& user);
bool avoidSame(string nameOrEmail, const User(&userLists)[Max_Size]);
void grabUser(User(&userLists)[Max_Size]);
void grabFlight(Flight(&flightLists)[Max_Size], string fileName, bool goPrint);
void grabRecord(Record(&recordLists)[Max_Size], string fileName, bool goPrint, string email, string viewBooking);
string convertClassID(int classID);
string convertPaymentStatus(int status);
string toLower(string keyword);
void user_search();
void admin_search(int option);
string minToHourMin(string duration);
void adminMenu_Drop();
int adminSearchMenu();
int adminUpdateMenu();
void admin_update(int section);
int countLine(string file_name);
void drop(int selection);
void addFlight();
// decorations
void loadingBar();
void endMenu();

int main() {
	/*Decoration Start*/
	// Get the console output handle
	HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	// Get the current console font info
	CONSOLE_FONT_INFOEX font_info = { sizeof(font_info) };
	GetCurrentConsoleFontEx(console_handle, FALSE, &font_info);
	// Set the font family and font weight
	font_info.FontFamily = FF_DONTCARE;
	font_info.FontWeight = FW_NORMAL;
	// Set the font size to 12 points
	font_info.dwFontSize.X = 0;
	font_info.dwFontSize.Y = 16;
	// Set the console font to the new font size
	SetCurrentConsoleFontEx(console_handle, FALSE, &font_info);
	//// Set the console window size to 80 columns by 30 rows
	SMALL_RECT window_size = { 0, 0, 239, 30 };
	SetConsoleWindowInfo(console_handle, TRUE, &window_size);
	system("COLOR 0e");
	/*Decoration End*/

	int option = 0;
	bool chkpoint = false;

	do {
		system("cls");
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
			system("pause");
		}
		else if (option == 4) {
			user_login(true);
		}
		else if (option == 5) {
			system("cls");
			endMenu();
			chkpoint = true;
		}
		else {
			cout << "Please try again!" << endl;
			Sleep(500);
		}

	} while (chkpoint == false);


	return 0;
}

/* Functions for Validation or Convertion of Data*/
string convertClassID(int classID) {
	// convert class id to its relevant meaning (from int to string) [classID is 1 -> Economy Class, classID is 2 ->Business Class]
	// parameter: classID is the class id of the relevant record
	string className;

	if (classID == 1) {
		className = "Eco";
	}
	else {
		className = "Bus";
	}

	return className;
}

string convertPaymentStatus(int status) {
	// convert payment status to its relevant meaning (from int to string) [0=Unpaid, 1=Paid]
	// parameter: status is the payment status of the specific record
	string payStatus;

	if (status == 0) {
		payStatus = "Unpaid";
	}
	else {
		payStatus = "Paid";
	}

	return payStatus;
}

string toLower(string keyword) {
	// let the string be lowercase, based on subtraction of ASCII codes in specific range 
	// parameter: keyword is the string that gonna to be lowercase
	string words = keyword;

	for (int i = 0; i < words.length(); i++) {
		if ((words[i] >= 'A') && (words[i] <= 'Z')) {
			words[i] = words[i] - 'A' + 'a';
		}
	}

	return words;
}

string generateID(string from_location, string to_location, int selection) {
	// generate a random id based on condition given
	// parameter: from_location & to_location are the conditions
	// parameter: selection is also consider as condition to use which method for generating id 
	srand(time(0));
	string temp, temp2, temp3, id;
	int randNum = rand() % 900 + 100;	// generate 3-digit numbers
	int randNum2 = 0;

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
		else if (toLower(from_location) == "vietnam") {
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
	else {
		randNum2 = rand() % 6 + 1;	// generate a 1 digit random num in range of 1 to 6
		// temp
		if (randNum2 == 1) {
			temp = "ABX";
			temp2 = "GHF";
		}
		else if (randNum2 == 2) {
			temp = "CBA";
			temp2 = "NML";
		}
		else if (randNum2 == 3) {
			temp = "POT";
			temp2 = "WWE";
		}
		else if (randNum2 == 4) {
			temp = "JBL";
			temp2 = "CBA";
		}
		else if (randNum2 == 5) {
			temp = "WGH";
			temp2 = "FWR";
		}
		else if (randNum2 == 6) {
			temp = "DPC";
			temp2 = "IGH";
		}
		else {
			temp = "XXX";
			temp2 = "XXX";
		}

		temp3 = to_string(randNum);
		id = temp + temp3 + temp2;
	}

	return id;
}

bool isValidCreditCard(char creditCard[], int size) {
	// a validation for checking credit card numbers is all 11 digits
	// parameter: creditCard[] is the char array included 11 digits of credit card num
	// parameter: size is size of char array which also the element that used to exclude '\0' of c-string
	for (int i = 0; i < size - 1; i++) {
		if (!isdigit(creditCard[i])) {
			return false;
		}
	}

	return true;
}

int countLine(string file_name) {
	// to count how many lines of records in the relevant file
	// parameter: file_name is the specific file to be counted
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
	// to check the validation of the username or password is whether meets the requirement
	// parameter: nameOrPass is the string of username or password in this case
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
	// to check input is a email or not by validatin ghether has symbol of '@' and '.'
	// parameter: user is based on struct datatype -  User (reference)
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
	// a validation to avoid the confliction of haveing same username or email within the database
	// parameter with reference on userLists and nameOrEmail (username or email)
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

string minToHourMin(string duration) {
	// convert mins to hours and mins
	// parameters duration is the variable stored with mins
	int hour, min, temp_min;
	string temp_duration = duration;
	string flight_duration;
	temp_min = stoi(duration);	// convert string to int
	hour = temp_min / 60;
	min = temp_min % 60;
	flight_duration = to_string(hour) + "h" + to_string(min) + "m";		// concatenate

	return flight_duration;
}

/*Function for Menu*/
int main_menu(int& option) {
	cout << R"(
  /$$$$$$   /$$$$$$   /$$$$$$ 
 /$$__  $$ /$$__  $$ /$$__  $$	__  _
| $$  \__/| $$  \ $$| $$  \ $$	\ `/ |
| $$ /$$$$|  $$$$$$$|  $$$$$$$	 \__`!
| $$|_  $$ \____  $$ \____  $$	 / ,' `-.__________________
| $$  \ $$ /$$  \ $$ /$$  \ $$	'-'\_____                LI`-.
|  $$$$$$/|  $$$$$$/|  $$$$$$/	   <____()-=O=O=O=O=O=[]====--)
 \______/  \______/  \______/	     `.___ ,-----,_______...-'
					  /    .'
G99 Airline                              /   .'
  Best Airline 		                /  .'
    in Southeast Asia	                `-' 
)" << endl;
	cout << "\n\n\t\t\tMenu " << endl;
	cout << "\t\t--------------------" << endl;
	cout << "\t\t1. Non-User Register" << endl;
	cout << "\t\t2. User Login" << endl;
	cout << "\t\t3. View Flight Info" << endl;
	cout << "\t\t4. Admin Login" << endl;
	cout << "\t\t5. Exit" << endl;
	cout << "\nEnter your option: ";
	cin >> option;
	cout << endl;

	return option;
}

void endMenu() {
	cout << R"(                            .''.       
       .''.      .        *''*    :_\/_:     . 
      :_\/_:   _\(/_  .:.*_\/_*   : /\ :  .'.:.'.
  .''.: /\ :   ./)\   ':'* /\ * :  '..'.  -=:o:=-
 :_\/_:'.:::.    ' *''*    * '.\'/.' _\(/_'.':'.'
 : /\ : :::::     *_\/_*     -= o =-  /)\    '  *
  '..'  ':::'     * /\ *     .'/.\'.   '
      *            *..*         :
        *     THANK YOU!
        *)" << endl;
	system("pause");
}

void user_menu(User user) {	// User user is current user's info
	int choice;
	bool chkpoint = false;
	User currUser;
	currUser.email = user.email;
	Flight flightLists[Max_Size];;
	Record recordLists[Max_Size];

	do {
		cout << R"(      
                       --====|====--
                             |  
              G99 Airline Reservation System
                         .-"""""-. 
                       .'_________'. 
                      /_/_|__|__|_\_\
                     ;'-._       _.-';
,--------------------|    `-. .-'    |--------------------,
 ``""--..__    ___   ;       '       ;   ___    __..--""``
           `"-// \\.._\             /_..// \\-"`
              \\_//    '._       _.'    \\_//
               `"`        ``---``        `"`)" << endl;
		cout << "\n\n" << endl;
		cout << "\t\t\tUser Menu" << endl;
		cout << "\t\t-------------------------" << endl;
		cout << "\t\t1. View Flight Info" << endl;
		cout << "\t\t2. Search Flight" << endl;
		cout << "\t\t3. View Booking Record" << endl;
		cout << "\t\t4. View Purchased History" << endl;
		cout << "\t\t5. Logout" << endl;
		cout << "\nEnter your option: ";
		cin >> choice;
		cout << endl;

		switch (choice)
		{
		case 1:		// View Flight
			loadingBar();
			grabFlight(flightLists, "flight.txt", true);
			cout << "\n\n";
			booking_menu(user.email, 1);
			system("cls");
			break;
		case 2:		// Search
			user_search();
			cout << "\n\n\n";
			system("pause");
			system("cls");
			break;
		case 3:		// View Booking Record (not paid yet)
			system("cls");
			grabRecord(recordLists, "record.txt", false, currUser.email, "1");
			booking_menu(user.email, 2);
			system("cls");
			break;
		case 4:		// View Purchased History (paid)
			system("cls");
			grabRecord(recordLists, "record.txt", false, currUser.email, "2");
			cout << "\n\n" << endl;
			system("pause");
			system("cls");
			break;
		case 5:		// logout
			chkpoint = true;
			break;
		default:
			cout << "\n\n\t\tPlease Enter the Valid Choice." << endl;
			Sleep(800);
			system("cls");
			break;
		}
	} while (chkpoint == false);

}

void booking_menu(string email, int option) {	
	// parameter option - 1 for booking&pay, 2 only pay for unpaid
	int selection1, selection2;

	if (option == 1) {
		cout << endl;
		cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		cout << setw(50) << "Welcome to flight reservation system." << endl;
		cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		cout << "PRESS 1-------BOOKING" << endl;
		cout << "PRESS ANY NUMBER BACK TO MENU EXCEPT 1" << endl;
		cout << "\n\t->Enter Selection: ";
		cin >> selection1;

		if (selection1 == 1) {
			user_booking(1, email);
		}
	}
	else {
		cout << endl;
		cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		cout << setw(50) << "Welcome to flight reservation system." << endl;
		cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
		cout << "PRESS 1-------Pay" << endl;
		cout << "PRESS 2-------Cancel Booking" << endl;
		cout << "PRESS ANY NUMBER BACK TO MENU EXCEPT 1&2" << endl;
		cout << "\n\t->Enter Selection: ";
		cin >> selection2;

		if (selection2 == 1) {
			user_booking(2, email);
		}
		else if (selection2 == 2) {
			drop(2);
			system("pause");
		}
	}


}

void admin_menu() {
	int choice, action = 0, section, section2;
	bool chkpoint = false;
	Flight flightLists[Max_Size];
	Record recordLists[Max_Size];

	do {
		cout << "\t\t\t";
		cout << R"(      __|__
			*---o--(_)--o---*)" << endl;
		cout << "\n\n\n\t\t\tAdmin Menu" << endl;
		cout << "\t\t--------------------------" << endl;
		cout << "\t\t1. Flight Info" << endl;
		cout << "\t\t2. View Purchased Flight Record" << endl;
		cout << "\t\t3. Search Record" << endl;
		cout << "\t\t4. Logout" << endl;
		cout << "\n\t\t->Enter your option: ";
		cin >> choice;
		cout << endl;

		switch (choice) {
		case 1:		// View Flight Info and able to do add & update & drop
			loadingBar();
			grabFlight(flightLists, "flight.txt", true);
			section = adminMenu_flight();
			if (section == 1) {
				section2 = adminUpdateMenu();
				admin_update(section2);
			}
			else if (section == 2) {
				drop(1);
			}
			else if (section == 3) {
				addFlight();
			}
			cout << "\n\n\t\t";
			system("pause");
			system("cls");
			break;
		case 2:
			// View Purchased record and able to do drop
			system("cls");
			grabRecord(recordLists, "record.txt", true, "0", "0");
			adminMenu_Drop();
			cout << "\n\n\t\t";
			system("pause");
			system("cls");
			break;
		case 3:
			// Search by keyword - flight id, ticket id & location
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
			cout << "\n\n" << endl;
			system("pause");
			system("cls");
			break;
		case 4:
			// logout
			chkpoint = true;
			break;
		default:
			cout << "\n\n\t\tPlease Enter the Valid Choice." << endl;
			Sleep(800);
			system("cls");
			break;
		}

	} while (chkpoint == false);
}

void adminMenu_Drop() {
	int selection = 0;

	cout << endl;
	cout << "\t\t::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
	cout << setw(50) << "\t\t\t\tG99 Flight Reservation System." << endl;
	cout << "\t\t::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n";
	cout << "\t\tPRESS 1-------Delete Record" << endl;
	cout << "\t\tPRESS ANY NUMBER BACK TO MENU EXCEPT 1" << endl;
	cout << "\n\t\t->Enter Selection: ";
	cin >> selection;

	if (selection == 1) {
		drop(2);
	}
}

int adminMenu_flight() {
	int action2;

	cout << endl;
	cout << "\tPRESS 1 to Update Specific Record" << endl;
	cout << "\tPRESS 2 to Delete Specific Record" << endl;
	cout << "\tPRESS 3 to Add New Record" << endl;
	cout << "\tPRESS ANY NUMBER BACK TO MENU EXCEPT 1 & 2 & 3" << endl;
	cout << "\n\t\t->Enter option: ";
	cin >> action2;

	return action2;
}

int adminSearchMenu() {
	int option;
	cout << "\n\t\tSearch by: " << endl;
	cout << "\t\t1. Flight ID" << endl;
	cout << "\t\t2. Ticket ID" << endl;
	cout << "\t\t3. Location" << endl;
	cout << "\t\t->Enter option: ";
	cin >> option;

	return option;
}

int adminUpdateMenu() {
	int section;
	cout << "\t\t1. Departure Location" << endl;
	cout << "\t\t2. Arriaval Location" << endl;
	cout << "\t\t3. Departure Day" << endl;
	cout << "\t\t4. Departure Time" << endl;
	cout << "\t\t5. Arrival Time" << endl;
	cout << "\t\t6. Flight Duration" << endl;
	cout << "\t\t7. Price(Eco)" << endl;
	cout << "\t\t8. Available Seats(Eco)" << endl;
	cout << "\t\t9. Price(Bus)" << endl;
	cout << "\t\t10. Available Seats(Bus)" << endl;
	cout << "\t\t->Enter which part of the record that want to update: ";
	cin >> section;
	cout << endl;

	return section;
}

/*Functions to Do Specific Purpose*/
void grabUser(User(&userLists)[Max_Size]) {
	// to grab the records from user.txt
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
	// to grab the records from flight.txt
	// parameter for fileName is about flight.txt and goPrint is to whether print or not [goPrint is false means not to print, while goPrint is true means to print the relevant records
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
			cout << setw(9) << left << "ID";		// flight id
			cout << setw(13) << left << "From";		//from_location
			cout << setw(13) << left << "To";		//to_location
			cout << setw(11) << left << "DepartDay";		//departure_day
			cout << setw(7) << right << "DepTime";		//arrival_time
			cout << setw(9) << right << "ArrTime";		//flight_duration
			cout << setw(10) << right << "Duration";		//flight_price_eco
			cout << setw(11) << right << "Price-Eco";		//numSeats_eco
			cout << setw(10) << right << "Seat-Eco";		//flight_price_bus
			cout << setw(11) << right << "Price-Bus";		//numSeats_bus
			cout << setw(10) << right << "Seat-Bus" << endl;
			cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
			for (int i = 0; i < (count - 1); i++) {
				if (flightLists[i].flight_id != "000000") {
					cout << setw(9) << left << flightLists[i].flight_id;
					cout << setw(13) << left << flightLists[i].from_location;
					cout << setw(13) << left << flightLists[i].to_location;
					cout << setw(11) << left << flightLists[i].departure_day;
					cout << setw(7) << right << flightLists[i].departure_time;
					cout << setw(9) << right << flightLists[i].arrival_time;
					string duration = minToHourMin(flightLists[i].flight_duration);		// convert mins to hours&min
					cout << setw(10) << right << duration;
					cout << setw(11) << right << flightLists[i].flight_price_eco;
					cout << setw(10) << right << flightLists[i].numSeats_eco;
					cout << setw(11) << right << flightLists[i].flight_price_bus;
					cout << setw(10) << right << flightLists[i].numSeats_bus << endl;
				}
			}
		}
	}
	inFile.close();
}

void grabRecord(Record(&recordLists)[Max_Size], string fileName, bool goPrint, string email, string viewBooking) {
	// to grab all the records from record.txt
	// parameterL fileName is about record.txt, goPrint is whether print or not(true to print, false to not print)
	// parameter: email is the current user's email(which will used for filtering the record), if no email then email = "0"
	// parameter: viewBooking can be "0", "1", "2" which used to filter the record (0 means no filtering with payment status, 1 means payment status is unpaid, 2 means payment status is paid)
	ifstream inFile;
	inFile.open(fileName);

	int count = 0;
	string duration, className, payStatus;

	if (inFile.fail()) {
		cout << "Unable Read the Data!" << endl;
	}
	else {
		while (!inFile.eof()) {
			getline(inFile, recordLists[count].ticket_id, '|');
			getline(inFile, recordLists[count].flightInfo.flight_id, '|');
			getline(inFile, recordLists[count].class_id, '|');
			getline(inFile, recordLists[count].flightInfo.departure_day, '|');
			getline(inFile, recordLists[count].flightInfo.departure_time, ':');
			getline(inFile, recordLists[count].flightInfo.arrival_time, ':');
			getline(inFile, recordLists[count].flightInfo.flight_duration, '|');
			getline(inFile, recordLists[count].ticNum, '|');
			getline(inFile, recordLists[count].payment_status, '|');
			getline(inFile, recordLists[count].totalBill, '|');
			getline(inFile, recordLists[count].name, '|');
			getline(inFile, recordLists[count].contact_num, '|');
			getline(inFile, recordLists[count].email, '|');

			inFile.ignore(256, '\n');
			count++;
		}

		if (goPrint == true) {
			cout << setw(11) << left << "ID";
			cout << setw(9) << left << "FlightID";
			cout << setw(7) << left << "Class";
			cout << setw(11) << left << "DepartDay";
			cout << setw(9) << left << "DepTime";
			cout << setw(9) << left << "ArrTime";
			cout << setw(10) << left << "Duration";
			cout << setw(8) << left << "ticNum";
			cout << setw(9) << left << "Status";
			cout << setw(8) << left << "Bill";
			cout << setw(20) << left << "Name";
			cout << setw(13) << left << "Contact";
			cout << setw(20) << left << "Email" << endl;
			cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
			for (int i = 0; i < (count - 1); i++) {
				if (recordLists[i].ticket_id != "000000") {
					cout << setw(11) << left << recordLists[i].ticket_id;
					cout << setw(9) << left << recordLists[i].flightInfo.flight_id;
					className = convertClassID(stoi(recordLists[i].class_id));
					cout << setw(7) << left << className;
					cout << setw(11) << left << recordLists[i].flightInfo.departure_day;
					cout << setw(9) << left << recordLists[i].flightInfo.departure_time;
					cout << setw(9) << left << recordLists[i].flightInfo.arrival_time;
					duration = minToHourMin(recordLists[i].flightInfo.flight_duration);
					cout << setw(10) << left << duration;
					cout << setw(8) << left << recordLists[i].ticNum;
					payStatus = convertPaymentStatus(stoi(recordLists[i].payment_status));
					cout << setw(9) << left << payStatus;
					cout << setw(8) << left << recordLists[i].totalBill;
					cout << setw(20) << left << recordLists[i].name;
					cout << setw(13) << left << recordLists[i].contact_num;
					cout << setw(20) << left << recordLists[i].email << endl;
				}
			}
		}
		else if ((goPrint == false) && (email != "0") && (viewBooking == "1")) {	// viewBooking = 1 means unpaid records (filtering) & filtering by email
			bool chkEmpty = true;
			string searchByEmail = email;
			cout << setw(11) << left << "ID";
			cout << setw(9) << left << "FlightID";
			cout << setw(7) << left << "Class";
			cout << setw(11) << left << "DepartDay";
			cout << setw(9) << left << "DepTime";
			cout << setw(9) << left << "ArrTime";
			cout << setw(10) << left << "Duration";
			cout << setw(8) << left << "ticNum";
			cout << setw(9) << left << "Status";
			cout << setw(8) << left << "Bill" << endl;
			cout << "----------------------------------------------------------------------------------------------" << endl;
			for (int j = 0; j < (count - 1); j++) {
				if ((recordLists[j].email == searchByEmail) && (recordLists[j].ticket_id != "000000") && (recordLists[j].payment_status == "0")) {
					cout << setw(11) << left << recordLists[j].ticket_id;
					cout << setw(9) << left << recordLists[j].flightInfo.flight_id;
					className = convertClassID(stoi(recordLists[j].class_id));
					cout << setw(7) << left << className;
					cout << setw(11) << left << recordLists[j].flightInfo.departure_day;
					cout << setw(9) << left << recordLists[j].flightInfo.departure_time;
					cout << setw(9) << left << recordLists[j].flightInfo.arrival_time;
					duration = minToHourMin(recordLists[j].flightInfo.flight_duration);
					cout << setw(10) << left << duration;
					cout << setw(8) << left << recordLists[j].ticNum;
					payStatus = convertPaymentStatus(stoi(recordLists[j].payment_status));
					cout << setw(9) << left << payStatus;
					cout << setw(8) << left << recordLists[j].totalBill << endl;

					chkEmpty = false;
				}
			}
			if (chkEmpty == true) {
				cout << "\t\t\tYour Booking History is empty." << endl;
			}
		}
		else if ((goPrint == false) && (email != "0") && (viewBooking == "2")) {		// viewBooking = 2 means paid records (filtering) & filtering by email
			bool chkEmpty = true;
			string searchByEmail = email;
			cout << setw(11) << left << "ID";
			cout << setw(9) << left << "FlightID";
			cout << setw(7) << left << "Class";
			cout << setw(11) << left << "DepartDay";
			cout << setw(9) << left << "DepTime";
			cout << setw(9) << left << "ArrTime";
			cout << setw(10) << left << "Duration";
			cout << setw(8) << left << "Bill";
			cout << setw(20) << left << "Name";
			cout << setw(13) << left << "Contact" << endl;
			cout << "----------------------------------------------------------------------------------------------" << endl;
			for (int j = 0; j < (count - 1); j++) {
				if ((recordLists[j].email == searchByEmail) && (recordLists[j].ticket_id != "000000") && (recordLists[j].payment_status == "1")) {
					cout << setw(11) << left << recordLists[j].ticket_id;
					cout << setw(9) << left << recordLists[j].flightInfo.flight_id;
					className = convertClassID(stoi(recordLists[j].class_id));
					cout << setw(7) << left << className;
					cout << setw(11) << left << recordLists[j].flightInfo.departure_day;
					cout << setw(9) << left << recordLists[j].flightInfo.departure_time;
					cout << setw(9) << left << recordLists[j].flightInfo.arrival_time;
					duration = minToHourMin(recordLists[j].flightInfo.flight_duration);
					cout << setw(10) << left << duration;
					cout << setw(8) << left << recordLists[j].totalBill;
					cout << setw(20) << left << recordLists[j].name;
					cout << setw(13) << left << recordLists[j].contact_num << endl;

					chkEmpty = false;
				}
			}
			if (chkEmpty == true) {
				cout << "\t\t\tYour Purchased History is empty." << endl;
			}
		}
	}
	inFile.close();
}

bool payment(int totalBill) {
	//  a process of payment, by checking the validation of credit card no and total amount
	// parameter: totalBill means the total amount that need to pay by user
	char creditCard[12];
	int amount;

	cin.ignore(256, '\n');
	cout << "\n\t->Enter Card No(11 digits):";
	cin.getline(creditCard, 12);
	cout << endl;

	if (isValidCreditCard(creditCard, 12)) {
		cout << "\tTotal Price: ";
		cout << totalBill;
		cout << "\n\t->Enter amount to pay: ";
		cin >> amount;
		cout << endl;
		if (amount >= totalBill) {
			return true;
		}
	}

	return false;
}

void seatDeduction(string flightID, int tickNum, int classID) {
	// this function is used to deduct the numbers of available seats based on class once the booking is done
	// parameter: flightID is the id for the records in flight,txt, tickNum is ticket number bought by user, classID is the id for class(Eco or Bus)
	Flight flightLists[Max_Size];
	grabFlight(flightLists, "flight.txt", false);
	Record recordLists[Max_Size];
	grabRecord(recordLists, "record.txt", false, "0", "0");
	int count, count2, temp;
	count = countLine("flight.txt");
	count2 = countLine("record.txt");

	for (int i = 0; i < count; i++) {
		if (flightID == flightLists[i].flight_id) {
			if (classID == 1) {
				temp = stoi(flightLists[i].numSeats_eco);
				temp = temp - tickNum;
				flightLists[i].numSeats_eco = to_string(temp);
			}
			else if (classID == 2) {
				temp = stoi(flightLists[i].numSeats_bus);
				temp = temp - tickNum;
				flightLists[i].numSeats_bus = to_string(temp);
			}
		}
	}

	ofstream outFile;
	outFile.open("flight.txt");
	for (int j = 0; j < count; j++) {
		outFile << flightLists[j].flight_id << "|" << flightLists[j].from_location << "|" << flightLists[j].to_location << "|" << flightLists[j].departure_day << "|"
			<< flightLists[j].departure_time << "|" << flightLists[j].arrival_time << "|" << flightLists[j].flight_duration << "|" << flightLists[j].flight_price_eco
			<< "|" << flightLists[j].numSeats_eco << "|" << flightLists[j].flight_price_bus << "|" << flightLists[j].numSeats_bus << "|" << endl;
	}

	outFile.close();
}

void drop(int selection) {
	// this function used to delete the record
	// Note : if the id of record is "000000" is considered as deleted, which won't show to user or admin in this case (data is priceless)
	// parameters is the conditon for choosing which specific process
	// if selection is 1 means flight record will be deleted and all the relevant purchased ticket records is consider as invalid
	// if selection is 2 means specific ticket record will be deleted and the number of available seat based on class(Eco or Bus) will +1
	int count, count2;
	count = countLine("flight.txt");
	count2 = countLine("record.txt");
	string id, temp;
	bool flag = false;

	if (selection == 1) {
		cout << "\n\tEnter Flight ID: ";
		cin >> id;
		cout << endl;

		Flight flightLists[Max_Size];
		grabFlight(flightLists, "flight.txt", false);
		Record recordLists[Max_Size];
		grabRecord(recordLists, "record.txt", false, "0", "0");

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
				outFile2 << recordLists[k].ticket_id << "|" << recordLists[k].flightInfo.flight_id << "|" << recordLists[k].class_id << "|" << recordLists[k].flightInfo.departure_day << "|"
					<< recordLists[k].flightInfo.departure_time << ":" << recordLists[k].flightInfo.arrival_time << ":" << recordLists[k].flightInfo.flight_duration << "|" << recordLists[k].ticNum << "|" << recordLists[k].payment_status
					<< "|" << recordLists[k].totalBill << "|" << recordLists[k].name << "|" << recordLists[k].contact_num << "|" << recordLists[k].email << "|" << endl;
			}
			cout << "\t\tSuccessfully Deleted!" << endl;
			outFile.close();
			outFile2.close();
		}
	}
	else if (selection == 2) {
		string temp2, temp4;
		int temp3;
		cout << "\n\t\t->Enter Ticket ID: ";
		cin >> id;
		cout << endl;

		Record recordLists[Max_Size];
		grabRecord(recordLists, "record.txt", false, "0", "0");
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
							temp3 = stoi(flightLists[j].numSeats_eco);
							temp3 += stoi(recordLists[i].ticNum);
							temp4 = to_string(temp3);
							flightLists[j].numSeats_eco = temp4;
						}
						else if (stoi(temp2) == 2) { // bus
							temp3 = stoi(flightLists[j].numSeats_bus);
							temp3 += stoi(recordLists[i].ticNum);
							temp4 = to_string(temp3);
							flightLists[j].numSeats_bus = temp4;
						}
					}
				}
				flag = true;
			}
		}

		if (flag == false) {
			cout << "\t\tTicket ID is invalid!" << endl;
		}
		else {
			ofstream outFile, outFile2;
			outFile.open("record.txt");
			outFile2.open("flight.txt");

			for (int k = 0; k < count2; k++) {
				outFile << recordLists[k].ticket_id << "|" << recordLists[k].flightInfo.flight_id << "|" << recordLists[k].class_id << "|" << recordLists[k].flightInfo.departure_day << "|"
					<< recordLists[k].flightInfo.departure_time << ":" << recordLists[k].flightInfo.arrival_time << ":" << recordLists[k].flightInfo.flight_duration << "|" << recordLists[k].ticNum << "|" << recordLists[k].payment_status
					<< "|" << recordLists[k].totalBill << "|" << recordLists[k].name << "|" << recordLists[k].contact_num << "|" << recordLists[k].email << "|" << endl;
			}

			for (int l = 0; l < count; l++) {
				outFile2 << flightLists[l].flight_id << "|" << flightLists[l].from_location << "|" << flightLists[l].to_location << "|" << flightLists[l].departure_day << "|"
					<< flightLists[l].departure_time << "|" << flightLists[l].arrival_time << "|" << flightLists[l].flight_duration << "|" << flightLists[l].flight_price_eco
					<< "|" << flightLists[l].numSeats_eco << "|" << flightLists[l].flight_price_bus << "|" << flightLists[l].numSeats_bus << "|" << endl;
			}

			cout << "\t\tSuccessfully Deleted!" << endl;
			outFile.close();
		}
	}
}

void addFlight() {
	// this function is used to add a new flight record

	Flight newFlight;
	string tempID;
	ofstream outFile;
	outFile.open("flight.txt", ios::app);

	cout << setw(30) << "\n\n\t\t\tSchedule A Flight" << endl;
	cout << "\t\t*********************************" << endl;

	if (!outFile.fail()) {
		cin.ignore(256, '\n');
		cout << "\n\t\t->Enter Departure Location: ";
		getline(cin, newFlight.from_location, '\n');
		cout << "\n\t\t->Enter Arrival Location: ";
		getline(cin, newFlight.to_location, '\n');
		cout << "\n\t\t->Enter Day of Departure (Days): ";
		getline(cin, newFlight.departure_day, '\n');
		cout << "\n\t\t->Enter Departure Time (24hr) : ";
		getline(cin, newFlight.departure_time, '\n');
		cout << "\n\t\t->Enter Arrival Time (24hr) : ";
		getline(cin, newFlight.arrival_time, '\n');
		cout << "\n\t\t->Enter Duration of Flight (mins): ";
		getline(cin, newFlight.flight_duration, '\n');
		cout << "\n\t\t->Enter Price (Class: Economy): ";
		getline(cin, newFlight.flight_price_eco, '\n');
		cout << "\n\t\t->Enter Number of Seats (Class: Economy): ";
		getline(cin, newFlight.numSeats_eco, '\n');
		cout << "\n\t\t->Enter Price (Class: Business): ";
		getline(cin, newFlight.flight_price_bus, '\n');
		cout << "\n\t\t->Enter NUmber of Seats (Class: Business: ";
		getline(cin, newFlight.numSeats_bus, '\n');
		cout << endl;

		tempID = generateID(newFlight.from_location, newFlight.to_location, 1);
		newFlight.flight_id = tempID;

		outFile << newFlight.flight_id << "|" << newFlight.from_location << "|" << newFlight.to_location << "|" << newFlight.departure_day << "|"
			<< newFlight.departure_time << "|" << newFlight.arrival_time << "|" << newFlight.flight_duration << "|" << newFlight.flight_price_eco
			<< "|" << newFlight.numSeats_eco << "|" << newFlight.flight_price_bus << "|" << newFlight.numSeats_bus << "|" << endl;


		cout << "\t\t****************************************" << endl;
		cout << "\t\t*Flight information has been updated. *" << endl;
		cout << "\t\t****************************************" << endl;
	}
	else {
		cout << "\n\n\t\tUnable To Add Record!\n\n" << endl;
	}
	outFile.close();
}

void user_register() {
	// function to let non-user to register as a user
	User userLists[Max_Size];
	grabUser(userLists);

	int listLength = sizeof(userLists) / sizeof(userLists[0]);
	bool toWrite = false;

	ofstream outFile;
	outFile.open("user.txt", ios::app);

	User user;
	cout << "## Username is not > 12 characters, must included at least 1 alphabet & 1 number!(no space) ##" << endl;
	cout << "Enter your username: ";
	cin >> user.username;
	cin.ignore(256, '\n');
	cout << "## Password is not > 12 characters, must included at least 1 alphabet & 1 number!(no space) ##" << endl;
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
		Sleep(1000);
	}
	else {
		cout << "Username or Password is invalid, please try again!" << endl;
		Sleep(1000);
	}

	outFile.close();
}

void user_login(bool chkAdmin) {
	// fucntion to access specific menu by login 
	// parameter: chkAdmin is a bool , used to clarified is user login or admin login
	// if chkAdmin is false means is user login, if chkAdmin is true means is admin login
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
				Sleep(800);
				system("cls");
				user_menu(currentUser);
			}
		}
	}
	else {
		for (int i = 0; i < 3; i++) {
			if ((loginCred.username == userLists[i].username) && (loginCred.password == userLists[i].password)) {
				chkLog = true;
				cout << "Welcome, Admin." << endl;
				Sleep(1000);
				system("cls");
				admin_menu();
			}
		}
	}

	if (chkLog == false) {
		cout << "Username or Password is incorrect, please try again!" << endl;
		Sleep(800);
	}


}

void user_booking(int selection, string email) {
	// function to let user booking
	// parameter: selection is the conditions for choosing which booking process
	// selction is 1 means able to booking and pay, while selection is 2 means only allow to do a payment for unpaid payment/record
	Flight flightLists[Max_Size];
	grabFlight(flightLists, "flight.txt", false);
	Record bookingRecord;
	string temp_id, temp_name, temp_contact;
	bool flag = false;
	char pay;
	int count;
	int classID, ticketNum, totalPrice;
	count = countLine("flight.txt");

	if (selection == 1) {
		cout << "\n\t->Enter Flight ID: ";
		cin >> temp_id;

		for (int i = 0; i < count; i++) {
			if (temp_id == flightLists[i].flight_id) {
				cout << "\n\tSelect Class: Economy or Business" << endl;
				cout << "\t1. Economy\t2. Business" << endl;
				cout << "\t->Enter 1 or 2: ";
				cin >> classID;
				cin.ignore(256, '\n');
				cout << "\n\t->Enter Full Name: ";
				getline(cin, temp_name, '\n');
				cout << "\n\t->Enter Contact Number: ";
				getline(cin, temp_contact, '\n');
				cout << "\n\t->Enter amount of ticket(s): ";
				cin >> ticketNum;
				cin.ignore(256, '\n');

				bookingRecord.ticket_id = generateID("no", "no", 2);
				bookingRecord.flightInfo.flight_id = temp_id;
				bookingRecord.flightInfo.departure_time = flightLists[i].departure_time;
				bookingRecord.flightInfo.arrival_time = flightLists[i].arrival_time;
				bookingRecord.flightInfo.flight_duration = flightLists[i].flight_duration;
				bookingRecord.flightInfo.departure_day = flightLists[i].departure_day;
				bookingRecord.name = temp_name;
				bookingRecord.contact_num = temp_contact;
				bookingRecord.email = email;
				if (classID == 1) {		// eco
					bookingRecord.class_id = "1";
					totalPrice = ticketNum * stoi(flightLists[i].flight_price_eco);
					cout << "\n\t->Do you want to do payment now? [y/n]: ";
					cin >> pay;
					if ((pay == 'y') || (pay == 'Y')) {
						if (payment(totalPrice)) {
							cout << "\t\t********************************" << endl;
							cout << "\t\t*    Transaction Successful    *" << endl;
							cout << "\t\t********************************" << endl;
							bookingRecord.payment_status = "1";
						}
						else {
							cout << "\tFailed to Pay! Please Try to Pay Later." << endl;
							bookingRecord.payment_status = "0";
						}
					}
					else {
						bookingRecord.payment_status = "0";
					}

					flag = true;
				}
				else if (classID == 2) {	// bus
					bookingRecord.class_id = "2";
					totalPrice = ticketNum * stoi(flightLists[i].flight_price_bus);
					cout << "\n\t->Do you want to do payment now? [y/n]: ";
					cin >> pay;
					if ((pay == 'y') || (pay == 'Y')) {
						if (payment(totalPrice)) {
							cout << "\t\t********************************" << endl;
							cout << "\t\t*    Transaction Successful    *" << endl;
							cout << "\t\t********************************" << endl;
							bookingRecord.payment_status = "1";
						}
						else {
							cout << "\tFailed to Pay! Please Try to Pay Later." << endl;
							bookingRecord.payment_status = "0";
						}
					}
					else {
						bookingRecord.payment_status = "0";
					}
					flag = true;
				}
			}
		}
		if (flag == true) {
			seatDeduction(temp_id, ticketNum, classID);

			Record recordLists[Max_Size];
			grabRecord(recordLists, "record.txt", false, "0", "0");
			ofstream outFile;
			outFile.open("record.txt", ios::app);
			if (!outFile.fail()) {
				outFile << bookingRecord.ticket_id << "|" << bookingRecord.flightInfo.flight_id << "|" << bookingRecord.class_id << "|" << bookingRecord.flightInfo.departure_day << "|"
					<< bookingRecord.flightInfo.departure_time << ":" << bookingRecord.flightInfo.arrival_time << ":" << bookingRecord.flightInfo.flight_duration << "|" << ticketNum << "|" << bookingRecord.payment_status
					<< "|" << totalPrice << "|" << bookingRecord.name << "|" << bookingRecord.contact_num << "|" << bookingRecord.email << "|" << endl;
			}
			cout << "\n\tSuccessfully Booking!" << endl;
			system("pause");
		}
		else {
			cout << "\n\n\tFalied to Booking, Please Try Again!\n\n" << endl;
			system("pause");
		}

	}
	else if (selection == 2) {
		string tempTicket;
		bool chkflag = false;
		int count = countLine("record.txt"), totalPrice;
		Record recordLists[Max_Size];
		grabRecord(recordLists, "record.txt", false, "0", "0");

		cout << "\n\t->Enter Ticket ID: ";
		cin >> tempTicket;
		for (int i = 0; i < count; i++) {
			if (tempTicket == recordLists[i].ticket_id) {
				totalPrice = stoi(recordLists[i].totalBill);
				if (payment(totalPrice)) {
					cout << "\t\t********************************" << endl;
					cout << "\t\t*    Transaction Successful    *" << endl;
					cout << "\t\t********************************" << endl;
					recordLists[i].payment_status = "1";
					chkflag = true;
				}
			}
		}
		if (chkflag == true) {
			ofstream outFile;
			outFile.open("record.txt");
			for (int j = 0; j < count; j++) {
				outFile << recordLists[j].ticket_id << "|" << recordLists[j].flightInfo.flight_id << "|" << recordLists[j].class_id << "|" << recordLists[j].flightInfo.departure_day << "|"
					<< recordLists[j].flightInfo.departure_time << ":" << recordLists[j].flightInfo.arrival_time << ":" << recordLists[j].flightInfo.flight_duration << "|" << recordLists[j].ticNum << "|" << recordLists[j].payment_status
					<< "|" << totalPrice << "|" << recordLists[j].name << "|" << recordLists[j].contact_num << "|" << recordLists[j].email << "|" << endl;
			}
		}
		else {
			cout << "\n\n\t\tFailed to Pay! Please Try Again Later.\n\n" << endl;
		}
		cout << "\n\n\t\t";
		system("pause");
	}
}

void user_search() {
	// this function allow user to search some flight record by entering keyword such as departion location and arrival location
	// will print the filtering records based on which keyword selected
	Flight flightLists[Max_Size];
	grabFlight(flightLists, "flight.txt", false);

	string keyword;
	int option;

	cout << "\t\tSearch for:" << endl;
	cout << "\t\tPRESS 1 -------- Departure Location" << endl;
	cout << "\t\tPRESS 2 -------- Arrival Loction" << endl;
	cout << "\t\tPRESS ANY NUMBER BACK TO MENU EXCEPT 1 & 2" << endl;
	cout << "\n\t\t->Enter option: ";
	cin >> option;

	if (option == 1) {
		cout << "\n\t\t->Enter location: ";
		cin >> keyword;
		cout << endl;
		bool flag = false;
		system("cls");

		cout << setw(9) << left << "ID";
		cout << setw(13) << left << "From";
		cout << setw(13) << left << "To";
		cout << setw(11) << left << "DepartDay";
		cout << setw(7) << right << "DepTime";
		cout << setw(9) << right << "ArrTime";
		cout << setw(10) << right << "Duration";
		cout << setw(11) << right << "Price-Eco";
		cout << setw(10) << right << "Seat-Eco";
		cout << setw(11) << right << "Price-Bus";
		cout << setw(10) << right << "Seat-Bus" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
		for (int j = 0; j < Max_Size; j++) {
			if ((toLower(keyword)) == (toLower(flightLists[j].from_location))) {
				cout << setw(9) << left << flightLists[j].flight_id;
				cout << setw(13) << left << flightLists[j].from_location;
				cout << setw(13) << left << flightLists[j].to_location;
				cout << setw(11) << left << flightLists[j].departure_day;
				cout << setw(7) << right << flightLists[j].departure_time;
				cout << setw(9) << right << flightLists[j].arrival_time;
				cout << setw(10) << right << flightLists[j].flight_duration;
				cout << setw(11) << right << flightLists[j].flight_price_eco;
				cout << setw(10) << right << flightLists[j].numSeats_eco;
				cout << setw(11) << right << flightLists[j].flight_price_bus;
				cout << setw(10) << right << flightLists[j].numSeats_bus << endl;

				flag = true;
			}
		}

		if (flag == false) {
			cout << "\t\t\t\tThere is no such location provided by us!" << endl;
		}
	}
	else if (option == 2) {
		cout << "\n\t\t->Enter location: ";
		cin >> keyword;
		cout << endl;
		bool flag = false;
		system("cls");

		cout << setw(9) << left << "ID";
		cout << setw(13) << left << "From";
		cout << setw(13) << left << "To";
		cout << setw(11) << left << "DepartDay";
		cout << setw(7) << right << "DepTime";
		cout << setw(9) << right << "ArrTime";
		cout << setw(10) << right << "Duration";
		cout << setw(11) << right << "Price-Eco";
		cout << setw(10) << right << "Seat-Eco";
		cout << setw(11) << right << "Price-Bus";
		cout << setw(10) << right << "Seat-Bus" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;

		for (int j = 0; j < Max_Size; j++) {
			if ((toLower(keyword)) == (toLower(flightLists[j].to_location))) {
				cout << setw(9) << left << flightLists[j].flight_id;
				cout << setw(13) << left << flightLists[j].from_location;
				cout << setw(13) << left << flightLists[j].to_location;
				cout << setw(11) << left << flightLists[j].departure_day;
				cout << setw(7) << right << flightLists[j].departure_time;
				cout << setw(9) << right << flightLists[j].arrival_time;
				cout << setw(10) << right << flightLists[j].flight_duration;
				cout << setw(11) << right << flightLists[j].flight_price_eco;
				cout << setw(10) << right << flightLists[j].numSeats_eco;
				cout << setw(11) << right << flightLists[j].flight_price_bus;
				cout << setw(10) << right << flightLists[j].numSeats_bus << endl;

				flag = true;
			}
		}

		if (flag == false) {
			cout << "\t\t\t\tThere is no such location provided by us!" << endl;
		}
	}

}

void admin_search(int option) {
	// this function allow admin to search some flight record by entering keyword such as ticket id, flight id, departion location and arrival location
	// will print the filtering records based on which keyword selected
	string keyword;
	bool flag = false;

	if (option == 1) {
		// flight id
		Flight flightLists[Max_Size];
		grabFlight(flightLists, "flight.txt", false);

		cout << "\n\t\t->Enter Flight ID: ";
		cin >> keyword;
		cout << endl;
		system("cls");
		cout << setw(9) << left << "ID";		// flight id
		cout << setw(13) << left << "From";		//from_location
		cout << setw(13) << left << "To";		//to_location
		cout << setw(11) << left << "DepartDay";		//departure_day
		cout << setw(7) << right << "DepTime";		//arrival_time
		cout << setw(9) << right << "ArrTime";		//flight_duration
		cout << setw(10) << right << "Duration";		//flight_price_eco
		cout << setw(11) << right << "Price-Eco";		//numSeats_eco
		cout << setw(10) << right << "Seat-Eco";		//flight_price_bus
		cout << setw(11) << right << "Price-Bus";		//numSeats_bus
		cout << setw(10) << right << "Seat-Bus" << endl;
		cout << "-------------------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < Max_Size; i++) {
			if (keyword == flightLists[i].flight_id) {
				cout << setw(9) << left << flightLists[i].flight_id;
				cout << setw(13) << left << flightLists[i].from_location;
				cout << setw(13) << left << flightLists[i].to_location;
				cout << setw(11) << left << flightLists[i].departure_day;
				cout << setw(7) << left << flightLists[i].departure_time;
				cout << setw(9) << right << flightLists[i].arrival_time;
				cout << setw(10) << right << flightLists[i].flight_duration;
				cout << setw(11) << right << flightLists[i].flight_price_eco;
				cout << setw(10) << right << flightLists[i].numSeats_eco;
				cout << setw(11) << right << flightLists[i].flight_price_bus;
				cout << setw(10) << right << flightLists[i].numSeats_bus << endl;

				flag = true;
			}
		}

		if (flag == false) {
			cout << "There is no such Flight ID in the record!" << endl;
		}

	}
	else {
		// ticket id
		string className, duration, payStatus;
		Record recordLists[Max_Size];
		grabRecord(recordLists, "record.txt", false, "0", "0");

		cout << "\n\t\tEnter Ticket ID: ";
		cin >> keyword;
		cout << endl;
		system("cls");
		cout << setw(11) << left << "ID";
		cout << setw(9) << left << "FlightID";
		cout << setw(7) << left << "Class";
		cout << setw(11) << left << "DepartDay";
		cout << setw(9) << left << "DepTime";
		cout << setw(9) << left << "ArrTime";
		cout << setw(10) << left << "Duration";
		cout << setw(8) << left << "ticNum";
		cout << setw(9) << left << "Status";
		cout << setw(8) << left << "Bill";
		cout << setw(20) << left << "Name";
		cout << setw(13) << left << "Contact";
		cout << setw(20) << left << "Email" << endl;
		cout << "---------------------------------------------------------------------------------------------------------------------------------" << endl;
		for (int j = 0; j < Max_Size; j++) {
			if (keyword == recordLists[j].ticket_id) {
				cout << setw(11) << left << recordLists[j].ticket_id;
				cout << setw(9) << left << recordLists[j].flightInfo.flight_id;
				className = convertClassID(stoi(recordLists[j].class_id));
				cout << setw(7) << left << className;
				cout << setw(11) << left << recordLists[j].flightInfo.departure_day;
				cout << setw(9) << left << recordLists[j].flightInfo.departure_time;
				cout << setw(9) << left << recordLists[j].flightInfo.arrival_time;
				duration = minToHourMin(recordLists[j].flightInfo.flight_duration);
				cout << setw(10) << left << duration;
				cout << setw(8) << left << recordLists[j].ticNum;
				payStatus = convertPaymentStatus(stoi(recordLists[j].payment_status));
				cout << setw(9) << left << payStatus;
				cout << setw(8) << left << recordLists[j].totalBill;
				cout << setw(20) << left << recordLists[j].name;
				cout << setw(13) << left << recordLists[j].contact_num;
				cout << setw(20) << left << recordLists[j].email << endl;

				flag = true;
			}
		}

		if (flag == false) {
			cout << "There is no such Ticket ID in the record!" << endl;
		}
	}

}

void admin_update(int section) {
	// this fucntion to let admin to update the specifc flight record by the category selected
	// category: departure location, arrival location, departure time, price, class and etc
	string flightID, temp;
	bool flag = false;
	int count;
	string fileName = "flight.txt";
	count = countLine(fileName);
	Flight flightLists[Max_Size];

	grabFlight(flightLists, fileName, false);

	cout << "\n\t\t->Enter Flight ID of the record: ";
	cin >> flightID;
	cout << endl;

	for (int i = 0; i < Max_Size; i++) {
		if (flightID == flightLists[i].flight_id) {
			flag = true;
			cout << "\t\t->Enter data: ";
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
				cout << "\t\tUnable to Update!" << endl;
			}
		}

	}

	if (flag == false) {
		cout << "\n\n\t\t\tFlight ID is invalid!" << endl;
	}
	else {
		ofstream outFile;
		outFile.open("flight.txt", ios::out);
		if (outFile.fail()) {
			cout << "\t\tUnable to Update!" << endl;
		}
		else {
			for (int j = 0; j < count; j++) {
				outFile << flightLists[j].flight_id << "|" << flightLists[j].from_location << "|" << flightLists[j].to_location << "|" << flightLists[j].departure_day << "|"
					<< flightLists[j].departure_time << "|" << flightLists[j].arrival_time << "|" << flightLists[j].flight_duration << "|" << flightLists[j].flight_price_eco
					<< "|" << flightLists[j].numSeats_eco << "|" << flightLists[j].flight_price_bus << "|" << flightLists[j].numSeats_bus << "|" << endl;
			}
			cout << "\n\n\t\t\tSuccessfully Updated!" << endl;
			outFile.close();
		}

	}

}

/* Function for Decoration Purpose*/
void loadingBar() {
	// decoration only: loading bar
	system("COLOR 0e");	// change color to yellow
	system("cls");

	//Set ASCII to print special character. in this case is the bar(?) chart
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
		Sleep(80);
	}

	system("cls");
}