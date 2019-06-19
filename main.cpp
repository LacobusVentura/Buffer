#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#include "Buffer.hxx"

int main( void )
{
	Buffer buf;
	Buffer aux("1234567890");

	buf.append('A');
	buf.append('B');
	buf.append('C');
	buf.append('\0');
	buf.append('\t');
	buf.append('\r');
	buf.append('\n');
	buf.append('\f');
	buf.append("Palavra");
	buf.append(std::string("string"));
	buf.append((const unsigned char*)"1qaz2w\x0\x0\x0sx3edc4rfv", 16 );

	buf.append( aux );

	std::cout << buf.hex() << std::endl;
	std::cout << buf.ascii() << std::endl;
	std::cout << buf.dump() << std::endl;
	std::cout << aux.base64() << std::endl;
	std::cout << buf.length() << std::endl;


	std::cout << buf;

	return 0;
}

// end-of-file
