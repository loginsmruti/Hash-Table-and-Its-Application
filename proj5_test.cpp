#include<iostream>
#include "passserver.h"
#include "hashtable.h"

using namespace std;
/*
void Menu()
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
*/

int main() {
	// test constructor
	PassServer psd( 7 );
	string str1 = "lin_li";
        string code1 = "1990512a";
        string str2 = "xiangzhen_sun";
        string code2 = "19881030Lord";
        string str3 = "appleTV4";
        string code3 = "A4sldgwpr";

        pair<string, string> p1;
        pair<string, string> p2;
        pair<string, string> p3;
        p1.first = str1; p1.second = code1;
        p2.first = str2; p2.second = code2;
        p3.first = str3; p3.second = code3;
 
        // addUser ( copy ) function test:
        psd.addUser( p1 );
        psd.addUser( p2 );
        psd.addUser( p3 );

	// addUser( move ) function test:
        psd.addUser( std::make_pair( "i_am-Aperfect", "progRammer" ) );

        // dump function test:
        cout<< "\nBelow is the current content of the hash table:\n";
        psd.dump();
        cout << endl;

        // changePassword test:
        string newpassword = "880920Lord";
        if( psd.changePassword( p2, newpassword ) )
		cout <<"the Password was changed successfully!\n";

        cout << "\nBelow is the updated content of the hash table:\n";
        psd.dump();
        cout << endl;                  

        // find function test:      
        cout << "\nIs user: lin_li, in the table?\n";       
        psd.find( str1 )? cout << "Yes, she is.\n" : cout << "No, she isn't\n";
        cout << "\nIs user: Xiangzhen_Sun, in the table?\n";
        string temp = "Xiangzhen_Sun";
        psd.find( temp )? cout << "Yes, he is.\n" : cout << "No, he isn't\n";

	// test the rehash function, myhash function, setPrime, and prim_below functions:
        string str[10];
        string cod[10];
        for( int i = 0; i < 10; i++ )  {
                cout << "please input the key to insert: ";
                getline( cin, str[i] );
                cout << "please input the password: ";
                getline( cin,  cod[i] );
                pair<string, string> temp( str[i], cod[i] );
                psd.addUser( temp );
        }
        cout << "\n the Rehashed table is as the following:\n";
        psd.dump();

        // test removeUser function:
        cout << "\nI'm going to delete user lin_li's info:\n";
        const string str11 = "lin_li";
        if( psd.removeUser( str11 ) )
                cout << "user lin_li was successfully removed.\n";
        psd.dump();

        // test write_to_file:
        char outfile[256];
        cout << "\nPlease indicate the name of ouput file: ";
        cin.getline( outfile, 256 );
        psd.write_to_file( outfile );

	// test size() member function
	cout <<"\nNow the size of the table is: " << psd.size() << '\n';

	// test load function:
        cout << "Please put in the name of file to be loaded:\n";
        char infile[256];
        cin.getline( infile, 256 );
        psd.load( infile );
        psd.dump();

        cout << "\n****end of the test****\n";

	return 0;
}
