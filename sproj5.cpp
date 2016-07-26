/*  Name: Xiangzhen Sun
    Project: #5
    Description: This driver program is very similar to
    proj5.cpp. The only difference is, this driver program
    hide the user's input while user is inputting password.
*/

#include<iostream>
#include "passserver.h"
#include "hashtable.h"
#include<termios.h>
#include<unistd.h>
#include<stdio.h>

using namespace std;

// declare and define a getch() function that can
// read in one char each a time while not displaying it
int getch()  {
	int ch;
	struct termios t_old, t_new;

	tcgetattr(STDIN_FILENO, &t_old);
	t_new = t_old;
	t_new.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &t_new);
	ch = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
	return ch;
}

void Menu()  // a menu function to be implemented
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

void skipSpace()
{
	char wspace;
	while( isspace( cin.peek() ) && !cin.eof() )  {
		cin.get( wspace );
	}
}

int main() {
	// capacity has the size of hash table
	int capacity;
	// usr choice
	char choice;

	cout << "Enter prefered hash table capacity: ";
	cin >> capacity;
	if( capacity <= 0 )  { 
		cout << "**Input too large for prime_below()\nSet to default capacity\n11\n";
		capacity = 11;
	}

	// initialize the PassServer obj
	PassServer spass( capacity );

	do  {
		Menu();
		cin >> choice;

		// load from file
		if( choice == 'l' )  {
			string filename;
			cout << "Enter password file name to load from: ";
			skipSpace();
			getline( cin, filename );
			if( !spass.load( filename.c_str() ) )
				cout << "Cannot open file " << filename << '\n';
		}

		// add user
		else if( choice == 'a' )  {
			const char RETURN = 10;
			string usrName;
			string psd;
			char ch;
			cout << "Enter user name: ";
			skipSpace();
			getline( cin, usrName );
			cout << "Enter password: ";
			//skipSpace();
			while( ( ch = getch() ) != RETURN )  {
				psd += ch;
			}
			pair<string, string> newPair( usrName, psd );
			if( spass.addUser( newPair ) )
				cout << "User " << usrName << " added.\n";
			else
				cout << "*****Error: User already exists. Could not add user.\n";
		}

		// remove user
		else if( choice == 'r' )  {
			string usrName;
			cout << "Enter username: ";
			skipSpace();
			getline( cin, usrName );
			if( spass.removeUser( usrName ) )
				cout << "User " << usrName << " deleted.\n";
			else
				cout << "*****Error: User not found. Could not delete user.\n";
		}

		// change password
		else if( choice == 'c' )  {
			const char RETURN = 10;
			char ch;
			char ch1;
			string usrName;
			string oldpsd;
			string newpsd;
			cout << "Enter username: ";
			skipSpace();
			getline( cin, usrName );
			cout << "Enter password: ";
			//skipSpace();
			while( ( ch = getch() ) != RETURN )  {
				oldpsd += ch;
			}
			cout << "Enter new password: ";
			//skipSpace();
			while( ( ch1 = getch() ) != RETURN )  {
				newpsd += ch1;
			}
			pair<string, string> oldPair( usrName, oldpsd );
			if( spass.changePassword( oldPair, newpsd ) )
				cout << "Password changed for user " << usrName << '\n';
			else
				cout << "*****Error: Could not change user password.\n";
		}

		// find user
		else if( choice == 'f' )  {
			string usrName;
			cout << "Enter username: ";
			skipSpace();
			getline( cin, usrName );
			if( spass.find( usrName ) )
				cout << "User " << "'" << usrName << "'" << " found.\n";
			else
				cout << "User " << "'" << usrName << "'" << " not found.\n";
		}

		// dump hash table
		else if( choice == 'd' )  {
			spass.dump();
		}

		// hash table size
		else if( choice == 's' )  {
			cout << "Size of hashtable: " << spass.size() << '\n';
		}

		// write to password file
		else if( choice == 'w' )  {
			string psdFilename;
			cout << "Enter password file name to write to: ";
			skipSpace();
			getline( cin, psdFilename );
			spass.write_to_file( psdFilename.c_str() );
		}

		// exit
		else if( choice == 'x' )  {}
		
		else
			cout << "*****Error: Invalid entry.  Try again.";

	} while( choice != 'x' );

	return 0;
}
