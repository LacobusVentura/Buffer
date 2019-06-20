#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "Buffer.hpp"

int main( void )
{
	std::vector<unsigned char> v;

	std::srand(std::time(NULL));

	for( int i = 0; i < 128; i++ )
		v.push_back( std::rand() % 256 );

	Buffer buf( reinterpret_cast<const unsigned char*>(&v[0]), v.size() );

	Buffer buf2( buf );

	Buffer b;

	b = buf2;

	std::cout << b << std::endl;
	std::cout << buf << std::endl;

	return 0;
}

// end-of-file
