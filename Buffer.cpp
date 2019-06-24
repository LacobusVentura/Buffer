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

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <ostream>
#include <sstream>
#include <iterator>
#include <bitset>
#include <stdexcept>

#include "Buffer.hpp"


Buffer::Buffer( void ) :
	m_buffer()
{
}


Buffer::Buffer( std::size_t size ) :
	m_buffer( size )
{
}


Buffer::Buffer( const char * pstr ) :
	m_buffer( pstr, pstr + std::strlen(pstr) )
{
}


Buffer::Buffer( const std::string& str ) :
	m_buffer( str.begin(), str.end() )
{
}


Buffer::Buffer( const unsigned char * pbuf, std::size_t len ) :
	m_buffer( pbuf, pbuf + len )
{
}


Buffer::Buffer( const Buffer& buf ) :
	m_buffer( buf.m_buffer )
{
}


Buffer::~Buffer( void )
{
}


void Buffer::swap( Buffer& buf ) throw()
{
	std::swap( m_buffer, buf.m_buffer );
}


Buffer& Buffer::operator=( const std::string& str )
{
	return assign(str);
}


Buffer& Buffer::operator=( const char* pstr )
{
	return assign(pstr);
}


Buffer& Buffer::operator=( char c )
{
	return assign(c);
}

Buffer& Buffer::operator=( const Buffer& buf )
{
	Buffer tmp(buf);
	tmp.swap(*this);
	return *this;
}


Buffer& Buffer::operator+=( const Buffer& buf )
{
	return append(buf);
}


Buffer& Buffer::operator+=( const std::string& str )
{
	return append(str);
}


Buffer& Buffer::operator+=( const char* pstr )
{
	return append(pstr);
}


Buffer& Buffer::operator+=( char c )
{
	return append(c);
}


Buffer& Buffer::clear( void )
{
	m_buffer.clear();
	return(*this);
}


Buffer& Buffer::resize( std::size_t n )
{
	m_buffer.resize( n );
	return(*this);
}


Buffer& Buffer::assign( const char* pstr )
{
	m_buffer.insert( m_buffer.end(), pstr, pstr + std::strlen(pstr) );
	return(*this);
}


Buffer& Buffer::assign( char c )
{
	m_buffer.clear();
	m_buffer.push_back(c);
	return(*this);
}


Buffer& Buffer::assign( const std::string& str )
{
	m_buffer.insert( m_buffer.begin(), str.begin(), str.end() );
	return(*this);
}


Buffer& Buffer::assign( const unsigned char * buf, std::size_t len )
{
	m_buffer.insert( m_buffer.begin(), buf, buf + len );
	return(*this);
}


Buffer& Buffer::assign( const Buffer& buf )
{
	m_buffer.insert( m_buffer.begin(), buf.m_buffer.begin(), buf.m_buffer.end() );
	return(*this);
}


Buffer& Buffer::prepend( const char * pstr )
{
	m_buffer.insert( m_buffer.begin(), pstr, pstr + std::strlen(pstr) );
	return(*this);
}


Buffer& Buffer::prepend( char c )
{
	m_buffer.insert( m_buffer.begin(), c );
	return(*this);
}


Buffer& Buffer::prepend( const std::string& str )
{
	m_buffer.insert( m_buffer.begin(), str.begin(), str.end() );
	return(*this);
}


Buffer& Buffer::prepend( const unsigned char * buf, std::size_t len )
{
	m_buffer.insert( m_buffer.begin(), buf, buf + len );
	return(*this);
}


Buffer& Buffer::prepend( const Buffer& buf )
{
	m_buffer.insert( m_buffer.begin(), buf.m_buffer.begin(), buf.m_buffer.end() );
	return(*this);
}


Buffer& Buffer::append( const char * pstr )
{
	m_buffer.insert( m_buffer.end(), pstr, pstr + std::strlen(pstr) );
	return(*this);
}


Buffer& Buffer::append( char c )
{
	m_buffer.insert( m_buffer.end(), c );
	return(*this);
}


Buffer& Buffer::append( const std::string& str )
{
	m_buffer.insert( m_buffer.end(), str.begin(), str.end() );
	return(*this);
}


Buffer& Buffer::append( const unsigned char * buf, std::size_t len )
{
	m_buffer.insert( m_buffer.end(), buf, buf + len );
	return(*this);
}


Buffer& Buffer::append( const Buffer& buf )
{
	m_buffer.insert( m_buffer.end(), buf.m_buffer.begin(), buf.m_buffer.end() );
	return(*this);
}


Buffer& Buffer::insert( std::size_t pos, const char* pstr )
{
	if( pos >= m_buffer.size() )
		throw std::out_of_range("position out of range");

	m_buffer.insert( m_buffer.begin() + pos, pstr, pstr + std::strlen(pstr) );
	return(*this);
}


Buffer& Buffer::insert( std::size_t pos, char c )
{
	if( pos >= m_buffer.size() )
		throw std::out_of_range("position out of range");

	m_buffer.insert( m_buffer.begin() + pos, 1, c );
	return(*this);
}


Buffer& Buffer::insert( std::size_t pos, const std::string& str )
{
	if( pos >= m_buffer.size() )
		throw std::out_of_range("position out of range");

	m_buffer.insert( m_buffer.begin() + pos, str.begin(), str.end() );
	return(*this);
}


Buffer& Buffer::insert( std::size_t pos, const unsigned char * buf, std::size_t len )
{
	if( pos >= m_buffer.size() )
		throw std::out_of_range("position out of range");

	m_buffer.insert( m_buffer.begin() + pos, buf, buf + len );
	return(*this);
}


Buffer& Buffer::insert( std::size_t pos, const Buffer& buf )
{
	if( pos >= m_buffer.size() )
		throw std::out_of_range("position out of range");

	m_buffer.insert( m_buffer.begin() + pos, buf.m_buffer.begin(), buf.m_buffer.end() );
	return(*this);
}


Buffer Buffer::sub( std::size_t start, std::size_t len ) const
{
	if( start >= m_buffer.size() )
		throw std::out_of_range("start position out of range");

	if( start + len > m_buffer.size() )
		throw std::out_of_range("sub buffer out of range");

	return Buffer( &m_buffer[start], len );
}


std::size_t Buffer::size( void ) const
{
	return m_buffer.size();
}


const unsigned char * Buffer::buffer( void ) const
{
	return &m_buffer[0];
}


void Buffer::ascii( std::ostream &os, bool full_decode ) const
{
	std::size_t buflen = m_buffer.size();
	unsigned long i = 0L;

	if( full_decode )
	{
		static const char * decode[32] = { "NUL","SOH","STX","ETX","EOT","ENQ","ACK","BEL",
		                                   "BS", "HT", "LF", "VT","FF", "CR", "SO", "SI",
		                                   "DLE","DCL","DC2","DC3","DC4","NAK","SYN","ETB",
		                                   "CAN", "EM","SUB","ESC","FS", "GS", "RS", "US" };
		for( i = 0; i < buflen; i++ )
		{
			if( std::isprint(m_buffer[i]) )
				os << static_cast<char>(m_buffer[i]);
			else if( m_buffer[i] < 32 )
				os << '<' << decode[m_buffer[i]] << '>';
			else if( m_buffer[i] == 127 )
				os << "<DEL>";
			else
				os << "<0x"
				   << std::setfill('0')
				   << std::setw(2)
				   << std::hex
				   << static_cast<int>(m_buffer[i])
				   <<  '>';
		}
	}
	else
	{
		for( i = 0; i < buflen; i++ )
			os << static_cast<char>( (std::isprint(m_buffer[i])) ? m_buffer[i] : '.' );
	}
}


void Buffer::escape( std::ostream &os ) const
{
	unsigned long i = 0L;
	std::size_t buflen = m_buffer.size();

	for( i = 0; i < buflen; i++ )
		os << "\\x"
		   << std::setfill('0')
		   << std::setw(2)
		   << std::hex
		   << static_cast<int>(m_buffer[i]);
}


void Buffer::base2( std::ostream &os ) const
{
	unsigned long i = 0L;
	std::size_t buflen = m_buffer.size();

	for( i = 0; i < buflen; i++ )
		os << std::bitset<8>(m_buffer[i]).to_string();
}


void Buffer::hex( std::ostream &os ) const
{
	unsigned long i = 0L;
	std::size_t buflen = m_buffer.size();

	for( i = 0; i < buflen; i++ )
		os << std::setfill('0')
		   << std::setw(2)
		   << std::hex
		   << static_cast<int>(m_buffer[i]);
}


void Buffer::base64( std::ostream &os ) const
{
	static const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	static const unsigned long m1 = 63 << 18;
	static const unsigned long m2 = 63 << 12;
	static const unsigned long m3 = 63 << 6;
	unsigned long d = 0;
	unsigned long i = 0;
	unsigned long len = m_buffer.size();

	while( len > 2 )
	{
		d = m_buffer[i] << 16;
		d |= m_buffer[i + 1] << 8;
		d |= m_buffer[i + 2];

		os << charset[ (d & m1) >> 18 ];
		os << charset[ (d & m2) >> 12 ];
		os << charset[ (d & m3) >>  6 ];
		os << charset[ d & 63 ];

		len -= 3;
		i += 3;
	}

	if( len == 2 )
	{
		d = m_buffer[i] << 16;
		d |= m_buffer[i + 1] << 8;

		os << charset[ (d & m1) >> 18 ];
		os << charset[ (d & m2) >> 12 ];
		os << charset[ (d & m3) >>  6 ];
		os << '=';

		i += 2;
	}
	else if( len == 1 )
	{
		d = m_buffer[i] << 16;

		os << charset[ (d & m1) >> 18 ];
		os << charset[ (d & m2) >> 12 ];
		os << "==";

		i++;
	}
}


void Buffer::dump( std::ostream &os, unsigned int bytes_per_line, unsigned int group_bytes, bool hex_upper ) const
{
	unsigned long i = 0L;
	unsigned long offset = 0L;

	if( hex_upper )
		os << std::uppercase;

	for( offset = 0; offset < m_buffer.size(); offset += bytes_per_line )
	{
		os << std::setfill('0')
		   << std::setw(8)
		   << std::hex
		   << offset
		   << ": ";

		for( i = 0; i < bytes_per_line; i++ )
		{
			if( i + offset < m_buffer.size() )
				os << std::setfill('0')
				   << std::setw(2)
				   << std::hex
				   << static_cast<int>(m_buffer[i + offset]);
			else
				os << "  ";

			if(!((i + 1) % group_bytes))
				os << ' ';
		}

		for( i = 0; i < bytes_per_line; i++ )
		{
			if( i + offset < m_buffer.size() )
				if( std::isprint( m_buffer[ i + offset ] ) )
					os << m_buffer[ i + offset ];
				else
					os << '.';
			else
				os << ' ';
		}

		os << std::endl;
	}
}


std::string Buffer::ascii( bool full_decode ) const
{
	std::stringstream ss;
	ascii( ss, full_decode );
	return ss.str();
}


std::string Buffer::escape( void ) const
{
	std::stringstream ss;
	escape( ss );
	return ss.str();
}


std::string Buffer::base2( void ) const
{
	std::stringstream ss;
	base2( ss );
	return ss.str();
}


std::string Buffer::hex( void ) const
{
	std::stringstream ss;
	hex( ss );
	return ss.str();
}


std::string Buffer::base64( void ) const
{
	std::stringstream ss;
	base64( ss );
	return ss.str();
}


std::string Buffer::dump( void ) const
{
	std::stringstream ss;
	dump( ss, 16, 2, false );
	return ss.str();
}


std::string Buffer::dump( unsigned int bytes_per_line, unsigned int group_bytes, bool hex_upper ) const
{
	std::stringstream ss;
	dump( ss, bytes_per_line, group_bytes, hex_upper );
	return ss.str();
}


void Buffer::save_file( const std::string& filename ) const
{
	std::ofstream f;
	f.open( filename.c_str(), std::ios::binary | std::ios::out );

	if( !f.is_open() )
		throw std::runtime_error("can't open file for writing");

	f.write( reinterpret_cast<const char*>(&m_buffer[0]), m_buffer.size() );
	f.close();
}


Buffer& Buffer::load_file( const std::string& filename, bool append )
{
	std::ifstream f;

	f.open( filename.c_str(), std::ios::binary );

	if( !f.is_open() )
		throw std::runtime_error("can't open file for reading");

	f.unsetf( std::ios::skipws );

	if( append == false )
		m_buffer.clear();

	m_buffer.insert( m_buffer.end(),
	                 std::istream_iterator<unsigned char>(f),
	                 std::istream_iterator<unsigned char>() );

	return(*this);
}


Buffer& Buffer::append_file( const std::string& filename )
{
	return load_file( filename, true );
}


unsigned char& Buffer::operator[]( unsigned long index )
{
	if( index >= m_buffer.size() )
		throw std::out_of_range("buffer index out of range");

	return m_buffer[ index ];
}


const unsigned char& Buffer::operator[]( unsigned long index ) const
{
	if( index >= m_buffer.size() )
		throw std::out_of_range("buffer index out of range");

	return m_buffer[ index ];
}


bool Buffer::equal( const Buffer& other ) const
{
	return( other.m_buffer == m_buffer );
}


bool Buffer::operator==( const Buffer& other ) const
{
	return equal( other );
}


bool Buffer::operator!=( const Buffer& other ) const
{
	return !equal( other );
}


Buffer Buffer::operator+(const Buffer& buf) const
{
	Buffer aux(*this);
	aux.append(buf);
	return aux;
}


std::ostream& operator<<( std::ostream &os, const Buffer& buf )
{
	buf.dump( os, 16, 2, false );
	return os;
}

// end-of-file //
