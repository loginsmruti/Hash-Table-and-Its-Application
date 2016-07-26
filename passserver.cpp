/* Name: Xiangzhen Sun
   Project: #5
   Description: this is file implement the PassServer class adaptor that makes
   use of HashTable class as an adaptee.
*/

#include "passserver.h"
#include "hashtable.h"

using namespace std;
using namespace cop4530;

PassServer::PassServer( size_t size )  {
	htable.resizeTable( size );  // initialize HashTable obj;
}

PassServer::~PassServer()  {
	// clean the memory, delete all user data in htable
	htable.clear();
}

bool PassServer::load( const char* filename )  {
	return htable.load( filename );
}

bool PassServer::addUser( std::pair<string, string> & kv )  {
	// encrypt the password part first
	string encryptedstr = encrypt( kv.second );
	// create a pair cotaining username and encrypted password
	pair<string, string> encryptedPair( kv.first, encryptedstr );
	return htable.insert( encryptedPair );
}

bool PassServer::addUser( std::pair<string, string> && kv )  {
	// move the pair to copy it
	pair<string, string> uncryptedPair( std::move( kv ) );
	// call copy-version addUser
	return addUser( uncryptedPair );
}

bool PassServer::removeUser( const string & k )  {
	htable.remove( k );
}

bool PassServer::changePassword( const pair<string, string> & p, const string & newpassword )  {
	if( p.second == newpassword )
	// the newpassword is the same with oldpassword
		return false;
	else if( !htable.contains( p.first ) )
	// user was not found in htable
		return false;
	else  {
		// get the encrypted old-password and new-password first
		string oldPassword = encrypt( p.second );
		string newPassword = encrypt( newpassword );
		// create a new pair to test if match or not
		pair<string, string> oldPair( p.first, oldPassword );
		if( !htable.match( oldPair ) )
			return false;  // return false if the password does not match
		else  {
			pair<string, string> newPair( p.first, newPassword );
			htable.insert( newPair );
			// insert member function can also update password value
			return true;
		}
	}
}

bool PassServer::find( const string & user ) const  {
	return htable.contains( user );
}

void PassServer::dump() const  {
	htable.dump();
}

size_t PassServer::size() const  {
	htable.getSize();
}

bool PassServer::write_to_file( const char* filename ) const  {
	htable.write_to_file( filename );
}

string PassServer::encrypt( const string & str )  {
	// encrypt the password string
	char salt[] = "$1$########";
	string cryptedstr = crypt( str.c_str(), salt );
	// cut off the prefix ( first 12 characters )
	cryptedstr.replace( 0, 12, "" );
	return cryptedstr;
}
