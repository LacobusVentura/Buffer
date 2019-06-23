#include <iostream>

#include "Buffer.hpp"

int main( void )
{
	Buffer a, b;

	a.load_file( "/bin/bash" );

	b = a.sub( 1024, 256 );

	std::cout << b.escape() << std::endl;
	std::cout << b.ascii() << std::endl;
	std::cout << b.ascii(false) << std::endl;
	std::cout << b.dump() << std::endl;

	return 0;
}

// end-of-file
