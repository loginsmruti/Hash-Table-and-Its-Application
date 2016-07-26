/* Name: Xiangzhen Sun
   Project: #5
   Description: this is a driver program that allows user to 
   operate there information in a hash table. Operations includes
   load, add, remove, change password, find, display, return size
   write to file. This Driver program does not conceal password while
   putting in.
*/

#include<iostream>
#include "passserver.h"
#include "hashtable.h"
#include<utility>

using namespace std;

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
			string usrName;
			string psd;
			cout << "Enter user name: ";
			skipSpace();
			getline( cin, usrName );
			cout << "Enter password: ";
			skipSpace();
			getline( cin, psd );
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
			string usrName;
			string oldpsd;
			string newpsd;
			cout << "Enter username: ";
			skipSpace();
			getline( cin, usrName );
			cout << "Enter password: ";
			skipSpace();
			getline( cin, oldpsd );
			cout << "Enter new password: ";
			skipSpace();
			getline( cin, newpsd );
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
