#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <ostream>
#include <sstream>
#include <iterator>

#include "Buffer.hpp"


Buffer::Buffer( void ) :
	m_buffer()
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


Buffer::Buffer( char c ) :
	m_buffer()
{
	m_buffer.push_back(c);
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
	std::swap( this->m_buffer, buf.m_buffer );
}


Buffer& Buffer::operator=( const std::string& str )
{
	assign(str);
	return *this;
}


Buffer& Buffer::operator=( const char* pstr )
{
	assign(pstr);
	return *this;
}


Buffer& Buffer::operator=( char c )
{
	assign(c);
	return *this;
}

Buffer & Buffer::operator=( const Buffer& buf )
{
	Buffer tmp(buf);
	tmp.swap(*this);
	return *this;
}


Buffer& Buffer::operator+=( const Buffer& buf )
{
	this->append(buf);
	return *this;
}


Buffer& Buffer::operator+=( const std::string& str )
{
	this->append(str);
	return *this;
}


Buffer& Buffer::operator+=( const char* pstr )
{
	this->append(pstr);
	return *this;
}


Buffer& Buffer::operator+=( char c )
{
	this->append(c);
	return *this;
}


void Buffer::clear( void )
{
	m_buffer.clear();
}


void Buffer::assign( const char* pstr )
{
	m_buffer.clear();
	append(pstr);
}


void Buffer::assign( char c )
{
	m_buffer.clear();
	append(c);
}


void Buffer::assign( const std::string& str )
{
	m_buffer.clear();
	append(str);
}


void Buffer::assign( const unsigned char * buf, std::size_t len )
{
	m_buffer.clear();
	append( buf, len );
}


void Buffer::assign( const Buffer& buf )
{
	m_buffer = buf.m_buffer;
}


void Buffer::append( const char * pstr )
{
	std::string s = pstr;
	std::copy(s.begin(), s.end(), std::back_inserter(m_buffer));
}


void Buffer::append( char c )
{
	m_buffer.push_back(c);
}


void Buffer::append( const std::string& str )
{
	std::copy(str.begin(), str.end(), std::back_inserter(m_buffer));
}


void Buffer::append( const unsigned char * buf, std::size_t len )
{
	m_buffer.insert( m_buffer.end(), buf, buf + len );
}


void Buffer::append( const Buffer& buf )
{
	m_buffer.insert( m_buffer.end(), buf.m_buffer.begin(), buf.m_buffer.end() );
}


Buffer Buffer::sub( std::size_t start, std::size_t len )
{
	return Buffer( &m_buffer[start], len );
}


std::size_t Buffer::length( void ) const
{
	return m_buffer.size();
}


const unsigned char * Buffer::buffer( void ) const
{
	return reinterpret_cast<const unsigned char*>(&m_buffer[0]);
}


void Buffer::ascii( std::ostream &os ) const
{
	for( unsigned long i = 0; i < m_buffer.size(); i++ )
		os << static_cast<char>( std::isprint(m_buffer[i]) ? m_buffer[i] : '.' );
}


void Buffer::hex( std::ostream &os ) const
{
	for( unsigned long i = 0; i < m_buffer.size(); i++ )
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


void Buffer::dump( std::ostream &os ) const
{
	unsigned long i = 0L;
	unsigned long offset = 0L;

	unsigned int bytes_per_line = 16;
	unsigned int group_bytes = 2;
	bool hex_upper = false;

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


std::string Buffer::ascii( void ) const
{
	std::stringstream ss;
	ascii( ss );
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
	dump( ss );
	return ss.str();
}


void Buffer::save_file( std::string filename ) const
{
	std::ofstream f;

	f.open( filename.c_str(), std::ios::binary | std::ios::out );

	f.write( reinterpret_cast<const char*>(&m_buffer[0]),
	         m_buffer.size() );

	f.close();
}


void Buffer::load_file( std::string filename )
{
	std::ifstream f;
	std::streampos fsize;

	f.open( filename.c_str(), std::ios::binary );

	f.unsetf( std::ios::skipws );

	f.seekg( 0, std::ios::end );
	fsize = f.tellg();
	f.seekg( 0, std::ios::beg );

	m_buffer.clear();
	m_buffer.reserve( fsize );

	m_buffer.insert( m_buffer.begin(),
	                 std::istream_iterator<unsigned char>(f),
	                 std::istream_iterator<unsigned char>());
}


std::ostream& operator<<( std::ostream &os, const Buffer& buf )
{
	buf.dump( os );
	return os;
}

// end-of-file //
