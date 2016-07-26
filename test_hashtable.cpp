#include<string>
#include<cstring>
#include<utility>
#include"hashtable.h"

using namespace std;
using namespace cop4530;

int main() {
	// constructor test:
	HashTable<string, string> h_table(7);
	// construct a hash_table of size 17

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
 
	// insert ( copy ) function test:
	h_table.insert( p1 );
	h_table.insert( p2 );
	h_table.insert( p3 );

	// insert( move ) function test:
	h_table.insert( std::make_pair( "i_am-Aperfect", "progRammer" ) );

	// dump function test:
	cout<< "\nBelow is the current content of the hash table:\n";
	h_table.dump();
	cout << endl;

	// insert to update password:
	pair<string, string> p2_1( "xiangzhen_sun", "880920Lord" );
	h_table.insert( p2_1 );
	cout << "\nBelow is the updated content of the hash table:\n";
	h_table.dump();
	cout << endl;

	// contains function test:
	cout << "\nIs user: lin_li, in the table?\n";
	h_table.contains( str1 )? cout << "Yes, she is.\n" : cout << "No, she isn't\n";
	cout << "\nIs user: Xiangzhen_Sun, in the table?\n";
	string temp = "Xiangzhen_Sun";
	h_table.contains( temp )? cout << "Yes, he is.\n" : cout << "No, he isn't\n";

	// match function test:
	cout << "\nDoes user appleTV4 have password: A4sldgwsr ?\n";
	h_table.match( p3 )? cout << "Yes, it does.\n" : cout << "No, it doesn't.\n";

	// test the rehash function, myhash function, setPrime, and prim_below functions:
	string str[10];
	string cod[10];
	for( int i = 0; i < 10; i++ )  {
		cout << "please input the key to insert: ";
		getline( cin, str[i] );
		cout << "please input the password: ";
		getline( cin,  cod[i] );
		pair<string, string> temp( str[i], cod[i] );
		h_table.insert( temp );
	}
	cout << "\n the Rehashed table is as the following:\n";
	h_table.dump();

	// test remove function:
	cout << "\nI'm going to delete user lin_li's info:\n";
	const string str11 = "lin_li";
	if( h_table.remove( str11 ) )
		cout << "user lin_li was successfully removed.\n";
	h_table.dump();

	// test write_to_file:
	char outfile[256];
	cout << "\nPlease indicate the name of ouput file: ";
	cin.getline( outfile, 256 );
	h_table.write_to_file( outfile );

	// test load function:
	cout << "Please put in the name of file to be loaded:\n";
	char infile[256];
	cin.getline( infile, 256 );
	h_table.load( infile );
	h_table.dump();

	// test clear(), makeEmpty()
	cout << "\nNow clear the hash table:\n";
	h_table.clear();
	h_table.dump();

	cout << "\n****end of the test****\n";
	return 0;
}
