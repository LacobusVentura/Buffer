/*

MIT License

Copyright (c) 2019 Tiago Ventura

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef __CBUFFER_HPP__
#define __CBUFFER_HPP__

#include <string>
#include <vector>
#include <ostream>

class Buffer
{
	friend std::ostream& operator<<( std::ostream &out, const Buffer& buf );

	public:
		Buffer( void );
		Buffer( const Buffer& buf );
		Buffer( const char* pstr );
		Buffer( char c );
		Buffer( const std::string& str );
		Buffer( const unsigned char* pbuf, std::size_t len );
		virtual ~Buffer( void );

		void clear( void );

		void assign( const char* str );
		void assign( char c );
		void assign( const std::string& str );
		void assign( const unsigned char* buf, std::size_t len );
		void assign( const Buffer& buf );

		void append( const char* str );
		void append( char c );
		void append( const std::string& str );
		void append( const unsigned char * buf, std::size_t len );
		void append( const Buffer& buf );

		Buffer& operator=( const char* pstr );
		Buffer& operator=( char c );
		Buffer& operator=( const std::string& str );
		Buffer& operator=( const Buffer& buf );

		Buffer& operator+=( const char* pstr );
		Buffer& operator+=( char c );
		Buffer& operator+=( const Buffer& buf );
		Buffer& operator+=( const std::string& str );

		unsigned char& operator[]( unsigned long index );
		const unsigned char& operator[]( unsigned long index ) const;

		Buffer operator+(const Buffer& buf) const;

		bool operator==( const Buffer& other ) const;
		bool operator!=( const Buffer& other ) const;

		bool equal( const Buffer& other ) const;

		Buffer sub( std::size_t start, std::size_t len );

		std::size_t length( void ) const;
		const unsigned char * buffer( void ) const;

		std::string base2( void ) const;
		std::string hex( void ) const;
		std::string base64( void ) const;
		std::string escape( void ) const;
		std::string ascii( bool full_decode = true ) const;
		std::string dump( void ) const;
		std::string dump( unsigned int bytes_per_line, unsigned int group_bytes, bool hex_upper ) const;

		void base2( std::ostream &os ) const;
		void hex( std::ostream &os ) const;
		void base64( std::ostream &os ) const;
		void escape( std::ostream &os ) const;
		void ascii( std::ostream &os, bool full_decode ) const;
		void dump( std::ostream &os, unsigned int bytes_per_line, unsigned int group_bytes, bool hex_upper ) const;

		void save_file( const std::string& filename ) const;
		void load_file( const std::string& filename, bool append = false );
		void append_file( const std::string& filename );

	private:
		std::vector<unsigned char> m_buffer;
		void swap( Buffer& buf ) throw();
};

#endif

// end-of-file
