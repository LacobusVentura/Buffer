#include <iostream>

#include "Buffer.hpp"

int main( void )
{
	Buffer b;

	b.load_file( "/etc/hostname" );

	std::cout << b.base64() << std::endl;
	std::cout << b.hex() << std::endl;
	std::cout << b.base2() << std::endl;
	std::cout << b.dump() << std::endl;

	return 0;
}

// end-of-file
