#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <ctime>
#include <sstream>
using namespace std;

#define data_num 10

void exit();
void clear();
void header();
void gotoxy(short x, short y);
int read_record();
int edit_record();
int write_record();
int delete_record();
int search_record();
int menu (int &mchoice);
int new_record(char &repeat);

//usage of class function
class Accounts {
	private:
		string fname;
		string lname;
		int acctNumber;
		double balance;

	public:
		//getters
		string getFName();
		string getLName();
		int getAcctNumber();
		double getBalance();
		
		//setters
		void setFName(string);
		void setLName(string);
		void setAcctNumber(int);
		void generateAcctNumber();
		void setBalance(double);
		
};

string Accounts::getFName() {
	return fname;
};

string Accounts::getLName() {
	return lname;
};

int Accounts::getAcctNumber() {
	return acctNumber;
};

double Accounts::getBalance() {
	return balance;
};

void Accounts::setFName(string newFName) {
	fname = newFName;
};

void Accounts::setLName(string newLName) {
	lname = newLName;
};

void Accounts::setAcctNumber(int newAcctNumber) {
	acctNumber = newAcctNumber;
};

void Accounts::setBalance(double newBal) {
	balance = newBal;
};

void Accounts::generateAcctNumber() {
	//account number will be generated randomly by the system
	acctNumber = (rand() % 853895379) + 2;
};

//setting the maximum data up to 10 only
Accounts info[data_num] = {}; 
int storedData = 0;

int main ()
{
	system("title Lacbain_N01_Finals");
	int choice;
	
	menu(choice);
	
	system("pause");
	return 0;
}

int menu (int &mchoice) {
	header();
	
	gotoxy(56, 8);  cout << "This stores up to 10 records only\n";
	
	gotoxy(60, 10); cout << "[1] Write record\n";
	gotoxy(60, 11); cout << "[2] Read record\n";
	gotoxy(60, 12); cout << "[3] Search record\n";
	gotoxy(60, 13); cout << "[4] Edit record\n";
	gotoxy(60, 14); cout << "[5] Delete record\n";
	gotoxy(60, 15); cout << "[6] Exit\n";
	gotoxy(60, 16); cout << "Enter choice: ";
	cin >> mchoice;
	
	while(1) {
		switch (mchoice) {
			case 1:
				clear();
				header();
				write_record();
				break;
			case 2:
				clear();
				header();
				read_record();
				break;
			case 3:
				clear();
				header();
				search_record();
				break;
			case 4:
				clear();
				header();
				edit_record();
				break;
			case 5:
				clear();
				header();
				delete_record();
				break;
			case 6:
				clear();
				header();
				exit();
				break;
			default:
				cout << "Choice not valid.";
		}
	}
}

int write_record() {

	ofstream fileWriter;
	string fileName;
	char repeat;
	int value;
	
	while (1) {
		for (int i = storedData; i<10; i++) {

			Accounts account;

			string firstName, lastName;
			double balance;
			int acctNumber;
			
			gotoxy(52, 9); cout << " ------------------------------------- \n";
			gotoxy(52, 10);cout << "             WRITE RECORD              \n";
			gotoxy(52, 11);cout << " ------------------------------------- \n";
			
			gotoxy (52, 13); cout << "Enter first name: ";
			cin >> firstName;
			gotoxy (52, 14);cout << "Enter last name: ";
			cin >> lastName;
			gotoxy (52, 15);cout << "Enter balance: ";
			cin >> balance;

			gotoxy (52, 18); cout << "Recording...\n";
			account.setBalance(balance);
			account.setFName(firstName);
			account.setLName(lastName);
			
			Sleep(1000);
			gotoxy (52, 19);cout << "Generating account number...\n";
			srand(time(0));
			account.generateAcctNumber();
			Sleep(1000);
			gotoxy (52, 20);cout << "Writing to file...\n";
			
			/*putting the data into different txt files with their account numbers
			as their file name*/
			stringstream fileName;
			fileName << account.getAcctNumber() << ".txt";
			fileWriter.open(fileName.str(), ios::app);
			fileWriter << "Name: " << account.getFName() << " " << account.getLName() << endl;
			fileWriter << "Account number: " << account.getAcctNumber() << endl;
			fileWriter << "Account Balance: " << account.getBalance() << endl << endl;
			fileWriter.close();
			Sleep(1000);

			info[i] = account;
			storedData++;
			
			clear();
			header();
			//this displays the input info along with the generated account number
			gotoxy(52, 9); cout << " ------------------------------------- \n";
			gotoxy(52, 10);cout << "             WRITE RECORD              \n";
			gotoxy(52, 11);cout << " ------------------------------------- \n";
			
			gotoxy(52, 13); cout << "Name: " << account.getFName() << " " << account.getLName() << endl;
			gotoxy(52, 14); cout << "Account number: " << account.getAcctNumber() << endl;
			gotoxy(52, 15); cout << "Account balance: " << account.getBalance() << endl;
			
			new_record(repeat);
		}
	}
}

int new_record (char &repeat) {
	//asks if the user wants to write more records
	int choice, value;
	
	gotoxy(52, 17); cout << "Record another account? Y or N: ";
	cin >> repeat;
		if (repeat == 'Y' || repeat == 'y') {
			clear();
			header();
			write_record(); 
		} else {
			clear();
			menu(choice);
		}
		
	return repeat;
}

int read_record() {
	ifstream inFile;
	string open_file;
	string accountNumber;
	int counter=0, choice;
	
	gotoxy(52, 9); cout << " ------------------------------------- \n";
	gotoxy(52, 10);cout << "              READ RECORD              \n";
	gotoxy(52, 11);cout << " ------------------------------------- \n";
	
	//reads records using account numbers
	gotoxy(53, 13); cout << "Account to view: ";
	cin >> accountNumber;
	
		inFile.open(accountNumber + ".txt"); //file will open if the file exists
		if (!inFile) {
			gotoxy(53, 13); cout << "Account does not exist!\n";
		} else {
				while(!inFile.eof()) {
					gotoxy(53, 15 + counter); getline(inFile, open_file,'\n');
					cout << open_file << endl;//made a new var for storage of contents of the file
					counter++; //for the gotoxy function
		}
		inFile.close();
	}
	
	gotoxy (53, 20); system("pause");
	
	clear();
	menu(choice);
}

int search_record() {
	ifstream inFile;
	ofstream outFile;
	Accounts account;
	string accountNumber, open_file;
	int i, choice, counter = 0;
	char v_choice;
	
	gotoxy(52, 9); cout << " ------------------------------------- \n";
	gotoxy(52, 10);cout << "            SEARCH RECORD              \n";
	gotoxy(52, 11);cout << " ------------------------------------- \n";
	
	//searches using acount number
	gotoxy (53, 13); cout << "Account to search: ";
	cin >> accountNumber;
	
	inFile.open(accountNumber + ".txt");
	if (!inFile) {
		gotoxy (53, 15); cout << "Account does not exist!\n";
	} else {
		gotoxy (53, 15); cout << "Account exists!\n";//verifies that a file exists
		gotoxy (53, 16); cout << "Do you want to view? Y or N: "; //asks user if they want to view contents
		cin >> v_choice;
			if (v_choice == 'Y' || v_choice == 'y') {
				while(!inFile.eof()) {
					gotoxy (53, 18 + counter); getline(inFile, open_file,'\n');
					cout << open_file << endl;
					counter++;//for gotoxy function
				}
				inFile.close();
			} else {
			clear();
			header();
			menu (choice);
			}
	}
	
	gotoxy(53, 22); system("pause");
	
	clear(); 
	menu(choice);
}
	
int edit_record() {
	Accounts account;
	ifstream inFile;
	ofstream outFile;
	ofstream editFile;
	double balance;
	int acctNum, choice;
	string firstName, lastName;
	char edited;
	
	gotoxy(52, 9); cout << " ------------------------------------- \n";
	gotoxy(52, 10);cout << "              EDIT RECORD              \n";
	gotoxy(52, 11);cout << " ------------------------------------- \n";

	//edits record using account number
	gotoxy(53, 13); cout << "Account to edit: ";
	cin >> acctNum;
	
	//ios::trunc automatically truncates the file
	outFile.open(acctNum + ".txt", ios::trunc | ios::out);
		if (inFile) { //new info will be stored
			gotoxy(52, 15); cout << "Enter first name: ";
			cin >> firstName;
			gotoxy(52, 16);cout << "Enter last name: ";
			cin >> lastName;
			gotoxy(52, 17);cout << "Enter balance: ";
			cin >> balance;

			gotoxy(52, 19);cout << "Recording...\n";
			
			account.setBalance(balance);
			account.setFName(firstName);
			account.setLName(lastName);
			account.setAcctNumber(acctNum);
			Sleep(1000);
			gotoxy(52, 20);cout << "Editing file...\n";
			Sleep(1000);
			
			//asks the user if they want to view the edited record
			gotoxy(52, 22); cout << "Do you want to view edited record? Y or N: ";
			cin >> edited;
			if (edited == 'Y' || edited == 'y') {
				clear();
				header();
				gotoxy(52, 9); cout << " ------------------------------------- \n";
				gotoxy(52, 10);cout << "            EDITED RECORD              \n";
				gotoxy(52, 11);cout << " ------------------------------------- \n";
				
				gotoxy(52, 13); cout << "Name: " << account.getFName() << " " << account.getLName() << endl;
				gotoxy(52, 14); cout << "Account number: " << account.getAcctNumber() << endl;
				gotoxy(52, 15); cout << "Account balance: " << account.getBalance() << endl;
			} else {
				clear();
				menu(choice);
			}
			
			stringstream fileName;
			fileName << acctNum << ".txt";
			editFile.open(fileName.str(), ios::trunc | ios::out);
			editFile << "Name: " << account.getFName() << " " << account.getLName() << endl;
			editFile << "Account number: " << account.getAcctNumber() << endl;
			editFile << "Account Balance: " << account.getBalance() << endl << endl;
			editFile.close();
		outFile.close();
		} else {
			clear();
			gotoxy(53, 13);cout << "Account does not exist!\n";
	}
	outFile.close();
	
	gotoxy (53, 25); system("pause");
	
	clear();
	menu(choice);
}

int delete_record() {
	ifstream inFile;
	ofstream outFile;
	string open_file;
	string accountNumber;
	int counter=0, choice;
	char check;
	
	gotoxy(52, 9); cout << " ------------------------------------- \n";
	gotoxy(52, 10);cout << "            DELETE RECORD              \n";
	gotoxy(52, 11);cout << " ------------------------------------- \n";
	
	//deletes account using account number
	gotoxy(53, 13); cout << "Account to delete: ";
	cin >> accountNumber;
	
		outFile.open(accountNumber + ".txt", ios::trunc);
		if (!inFile) {
			gotoxy(53, 15); cout << "Account does not exist!\n";
		} else {
			//automatically deletes the contents of the file but not the file itself
			gotoxy(53, 15); cout << "Account record successfully deleted!\n";
			gotoxy(53, 16); cout << "Do you want to check? Y or N: "; //checking
			cin >> check;
			if (check == 'Y' || check == 'y') {
				clear();
				header();
				read_record();
			} else {
				clear();
				menu(choice);
			}
		}
		outFile.close();
	
	gotoxy(53, 20); system("pause");
	
	clear();
	menu(choice);
	
}

void exit() {
	gotoxy(52, 11); cout << " ------------------------------------- \n";
	gotoxy(52, 12); cout << "   THANK YOU FOR USING THE PROGRAM     \n";
	gotoxy(52, 13); cout << " ------------------------------------- \n";
	
	exit(1);
}

void clear() {
	system("cls");
}

void gotoxy (short x, short y) {
	COORD pos = {x,y};
	SetConsoleCursorPosition (GetStdHandle (STD_OUTPUT_HANDLE), pos);
}

void header () {
	gotoxy (40, 0);cout << " |******   |*****|  *******  *******  |******   |******  |*****|" << endl;
	gotoxy (40, 1);cout << " |*|  |**  |*****| /*****/  /*******\\ |*|  |**  |******* |*****|" << endl;
	gotoxy (40, 2);cout << " |*|  |**  |*|     |**|     |*|   |*| |*|  |**  |*|  |** |**|   " << endl;
	gotoxy (40, 3);cout << " |******   |****|  |**|     |*|   |*| |******   |*|  |** |**|   " << endl;
	gotoxy (40, 4);cout << " |*******  |****|  |**|     |*|   |*| |*******  |*|  |** |*****|" << endl;
	gotoxy (40, 5);cout << " |*|   |** |*|     |**|     |*|   |*| |*|   |** |*|  |**    |**|" << endl;
	gotoxy (40, 6);cout << " |*|   |** |*****| \\*****\\  \\*******/ |*|   |** |******* |*****|" << endl;
	gotoxy (40, 7);cout << " |*|   |** |*****|  *******  *******  |*|   |** |******  |*****|" << endl;
}


