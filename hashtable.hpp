/* Name: Xiangzhen Sun
   Project: #5
   Description: this .hpp file includes all the definatons of member functions
   declared in headfile.
*/

template<typename K, typename V>
// constructor, create a hash table where the size of the vector
// is set to prime_below( size )
HashTable<K,V>::HashTable( size_t size )  {
	theList.resize( prime_below( size ) );
	// resize the vector of list to a prime number by calling prime_below
	currentSize = 0;
}

template<typename K, typename V>
// destructor, deletes all elements in the hash table
HashTable<K,V>::~HashTable()  {
	clear();  // deletes all elements in the hashtable by calling clear memberfunction
}

template<typename K, typename V>
// change the size of hashtable object
void HashTable<K,V>::resizeTable( size_t size )  {
	if( getSize() != size )  {
		theList.resize( prime_below( size ) );
		currentSize = 0;
	}
}

template<typename K, typename V>
// return the size of hash table
int HashTable<K,V>::getSize() const  {
	return currentSize;
}

template<typename K, typename V>
// check if key k of type K is in the hashtable
bool HashTable<K,V>::contains( const K & k ) const  {
	for( auto itr = theList[ myhash(k) ].begin(); itr != theList[ myhash(k) ].end(); ++itr )
	{  // search through the linked list at index myhash(k)
		if( itr->first == k )
			return true;  // return true only if the key is exactly same
	}
	return false;
}

template<typename K, typename V>
// check if key-value pair is in the hash table
bool HashTable<K,V>::match( const std::pair<K,V> & kv ) const  {
	// locate the linked list that might have pair kv first
	auto & whichList = theList[ myhash(kv.first) ];

	// std::find is included in <algorithm>
	return std::find( whichList.begin(), whichList.end(), kv ) != whichList.end();
}

template<typename K, typename V>
// add the key-value pair kv into the hash table
// don't add if kv is already in hash table
// update the value if key of kv is in the hashtable, but different value
// return true if inserted or updated, return false otherwise
bool HashTable<K,V>::insert( const std::pair<K,V> & kv )  {
	if( match( kv ) )  {
	// return false if pair kv already existed
		return false;
	}
	else if( contains( kv.first ) )  {
	// if key is found, while its value is different from kv's value
		auto & whichList = theList[ myhash( kv.first ) ];
		// now whichList is a reference to the linked list that kv.first belongs to
		for( auto itr = whichList.begin(); itr != whichList.end(); ++itr )  {
		// find where the key is and replace it by: erase and then insert the new kv pair
			if( itr->first == kv.first )  {
				auto iter = whichList.erase( itr );
				whichList.insert( iter, kv );
			}
		}
		return true;
	}
	else  {
		theList[ myhash( kv.first ) ].push_back( kv );
		// rehash if the current space is not enough
		if( ++currentSize > theList.size() )
			rehash();

		return true;
	}	
}

template<typename K, typename V>
// move version of insert operation
bool HashTable<K,V>::insert( std::pair<K,V> && kv )  {
	const std::pair<K,V> kvpair = std::move( kv );
	return insert( kvpair );  // call the copy version here
}

template<typename K, typename V>
// delete the key k and its value if found in hashtable, return true
// if removed, return false otherwise
bool HashTable<K,V>::remove( const K & k )  {
	bool flag = false;
	auto & whichList = theList[ myhash(k) ];
	for( auto itr = whichList.begin(); itr != whichList.end(); ++itr )
	{  // search through the linked list to find the node containing key: k
		if( itr->first == k )  {
			itr = whichList.erase( itr );  // if found, delete the whole node
			// don't forget to reassign itr, otherwise segementaton fault;
			--currentSize;
			flag = true;
		}
	}
	return flag;
}

template<typename K, typename V>
// delete all elements in the hash table
void HashTable<K,V>::clear()  {
	makeEmpty();  // call private function
}

template<typename K, typename V>
// load the content of the file "filename" into the hashtable,
// in "filename", each line contains a pair <K,V>, separated by space
// return true if loaded successfullly
bool HashTable<K,V>::load( const char* filename )  {
	std::pair<K,V> kvpair;
	std::ifstream fin;
	fin.open( filename, std::ifstream::in );

	if( !fin )
		return false;

	char wspace;
	while( fin )  {
	// keep reading in kv pairs until reaching the end of file
		std::getline( fin, kvpair.first, ' ' );

		while( isspace( fin.peek() ) )
			fin.get( wspace );
		std::getline( fin, kvpair.second, '\n' );

		while( isspace( fin.peek() ) )
			fin.get( wspace );

		insert( kvpair );
	}

	fin.close();
	return true;
}

template<typename K, typename V>
// display all entries in the hash table
void HashTable<K,V>::dump() const  {
	for( int i = 0; i < theList.size(); i++ )  {
		std::cout << "v[" << i << "]:";

		for( auto itr = theList[i].begin(); itr != theList[i].end(); ++itr )
		{
			if( itr != theList[i].begin() )
				std::cout << ':';
			// use semicolon to separate only if mutiple kv pairs appear in a single array-entry

			std::cout << itr->first << ' ' << itr->second;
		}
		std::cout << '\n';
	}
}

template<typename K, typename V>
// write all elements in hashtable to "filename", format is similar to load
bool HashTable<K,V>::write_to_file( const char* filename ) const  {
	std::ofstream fout;
	fout.open( filename );

	if( !fout )
		return false;

	for( int i = 0; i < theList.size(); i++ )  {
		for( auto itr = theList[i].begin(); itr != theList[i].end(); ++itr )  {
			fout << itr->first << ' ' << itr->second << '\n';
		}
	}
	fout.close();
	return true;
}

template<typename K, typename V>
// clears the hash table
void HashTable<K,V>::makeEmpty()  {
	for( auto & thislist : theList )  {
		theList.clear(); // call std::list member function clear()
	// to remove all contents in an nonempty linked list
	}
	currentSize = 0;
}

template<typename K, typename V>
// resize the hash table. called when the number of elements in the
// hash table is greater than the size of the vector
void HashTable<K,V>::rehash()  {
	// make a copy of the current hash table
	auto oldList = theList;
	// resize the current hash table so that the new size is a prime number
	// that is adjacent to 2 times of the current size;
	theList.resize( prime_below( 2 * theList.size() ) );

	for( auto & thisList : theList )
		thisList.clear();	// empty the current hash table

	// copy the hash table over
	currentSize = 0;
	for( auto & thisList : oldList )  {
		for( auto & kvpair : thisList )
			insert( std::move( kvpair ) );
	}
}

template<typename K, typename V>
// return the index of the vector entry where k should be stored
size_t HashTable<K,V>::myhash( const K & k ) const  {
	std::hash<K> hfunc;  // using the hash class defined in std
	return hfunc( k ) % theList.size();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K,V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
      std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
        return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K,V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}
