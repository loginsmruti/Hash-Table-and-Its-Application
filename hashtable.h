/* Name: Xiangzhen Sun
   Project: #5
   Description: this is a headfile of HashTable class adaptee. It includes
   all sorts of normal operational functions such as insert, remove, contains
   match, getSize, rehash, myhash, etc. The implementation file .hpp is also
   included in the namespace cop4530 for convenience in compiling.
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<vector>
#include<list>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<functional>
#include<cctype>

namespace cop4530 {
template<typename K, typename V>
class HashTable {
	public:
		// constructor, create a hash table where the size of the vector
		// is set to prime_below( size )
		explicit HashTable( size_t size = 101 );

		// destructor, deletes all elements in the hash table
		~HashTable();

		// change the size of hash table object
		void resizeTable( size_t size );

		// return the size of hash table
		int getSize() const;

		// check if key k of type K is in the hashtable
		bool contains( const K & k ) const;

		// check if key-value pair is in the hash table
		bool match( const std::pair<K,V> & kv ) const;

		// add the key-value pair kv into the hash table
		// don't add if kv is already in hash table
		// update the value if key of kv is in the hashtable, but different value
		// return true if inserted or updated, return false otherwise
		bool insert( const std::pair<K,V> & kv );

		// move version of insert operation
		bool insert( std::pair<K,V> && kv );

		// delete the key k and its value if found in hashtable, return true
		// if removed, return false otherwise
		bool remove( const K & k );

		// delete all elements in the hash table
		void clear();

		// load the content of the file "filename" into the hashtable,
		// in "filename", each line contains a pair <K,V>, separated by space
		// return true if loaded successfullly
		bool load( const char* filename );

		// display all entries in the hash table
		void dump() const;

		// write all elements in hashtable to "filename", format is similar to load
		bool write_to_file( const char* filename ) const;
	private:
		// the array of linked-list, each elements of linked-list is a pair<K,V>
		std::vector< std::list< std::pair<K,V> > > theList;

		// stores the number of pairs in the current hash table
		int currentSize;

		// clears the hash table
		void makeEmpty();

		// resize the hash table. called when the number of elements in the
		// hash table is greater than the size of the vector
		void rehash();

		// return the index of the vector entry where k should be stored
		size_t myhash( const K & k ) const;

		// determine the proper underlying vector size
		unsigned long prime_below( unsigned long );

		// set the calculated size the current hashtable
		void setPrimes( std::vector<unsigned long> & );

		// max_prime is used by the helpful functions provided
		// to you.
		static const unsigned int max_prime = 1301081;
		// the default_capacity is used if the initial capacity 
		// of the underlying vector of the hash table is zero. 
		static const unsigned int default_capacity = 11;
};

#include "hashtable.hpp"
}  // end of cop4530 namespace
#endif
