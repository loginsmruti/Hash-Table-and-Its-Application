/*  Name: Xiangzhen Sun
    Project: #5
    Description: this is a headfile of PassServer class adaptor. It includes
    the declarations of many useful functions that are to be used in operate
    a table containing user information
*/

#ifndef PASSSERVER_H
#define PASSSERVER_H

#include "hashtable.h"
#include<iostream>
#include<string>
#include<cstring>
#include<crypt.h>
#include<utility>
#include<unistd.h>
#include<stdlib.h>

using namespace std;
using namespace cop4530;

class PassServer  {
	public:
		PassServer( size_t size = 101 );
		~PassServer();
		bool load( const char* filename );
		bool addUser( std::pair<string, string> & kv );
		bool addUser( std::pair<string, string> && kv );
		bool removeUser( const string & k );
		bool changePassword( const pair<string, string> & p, const string & newpassword );
		bool find( const string & user ) const;
		void dump() const;
		size_t size() const;
		bool write_to_file( const char* filename ) const;
	private:
		HashTable<string, string> htable;
		string encrypt( const string & str );
};
#endif
