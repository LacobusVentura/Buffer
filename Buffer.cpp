#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstring>
#include <ostream>
#include <sstream>
#include <iterator>

#include "Buffer.hxx"


Buffer::Buffer( void ) :
	m_buffer()
{
}


Buffer::Buffer( const char * str ) :
	m_buffer( str, str + std::strlen(str) )
{
}


Buffer::Buffer( std::string str ) :
	m_buffer( str.begin(), str.end() )
{
}


Buffer::Buffer( char c )
{
	m_buffer.push_back(c);
}


Buffer::Buffer( const unsigned char * buf, size_t len ) :
	m_buffer( buf, buf + len )
{
}


Buffer::~Buffer( void )
{
}


void Buffer::append( const char * str )
{
	std::string s = str;
	std::copy(s.begin(), s.end(), std::back_inserter(m_buffer));
}


void Buffer::append( char c )
{
	m_buffer.push_back(c);
}


void Buffer::append( std::string s )
{
	std::copy(s.begin(), s.end(), std::back_inserter(m_buffer));
}


void Buffer::append( const unsigned char * buf, std::size_t len )
{
	m_buffer.insert( m_buffer.end(), buf, buf + len );
}


void Buffer::append( const Buffer& buf )
{
	m_buffer.insert( m_buffer.end(), buf.m_buffer.begin(), buf.m_buffer.end() );
}


std::size_t Buffer::length( void ) const
{
	return m_buffer.size();
}


std::string Buffer::ascii( void ) const
{
	std::vector<unsigned char>::const_iterator it;
	std::string str;

	for( it = m_buffer.begin(); it != m_buffer.end(); it++ )
		str += (std::isprint(*it)) ? *it : '.';

	return str;
}


std::string Buffer::hex( void ) const
{
	std::vector<unsigned char>::const_iterator it;
	static const char charset[] = "0123456789abcdef";
	std::string str;

	str.reserve( m_buffer.size() * 2 );

	for( it = m_buffer.begin(); it != m_buffer.end(); it++ )
	{
		str += charset[ *it / 16 ];
		str += charset[ *it % 16 ];
	}

	return str;
}


std::string Buffer::base64( void ) const
{
	static const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	static const unsigned long m1 = 63 << 18;
	static const unsigned long m2 = 63 << 12;
	static const unsigned long m3 = 63 << 6;
	unsigned long d = 0;
	unsigned long i = 0;
	unsigned long len = m_buffer.size();
	std::string s;

	while( len > 2 )
	{
		d = m_buffer[i] << 16;
		d |= m_buffer[i + 1] << 8;
		d |= m_buffer[i + 2];

		s.append( 1, charset[ (d & m1) >> 18 ] );
		s.append( 1, charset[ (d & m2) >> 12 ] );
		s.append( 1, charset[ (d & m3) >>  6 ] );
		s.append( 1, charset[ d & 63 ] );

		len -= 3;
		i += 3;
	}

	if( len == 2 )
	{
		d = m_buffer[i] << 16;
		d |= m_buffer[i + 1] << 8;

		s.append( 1, charset[ (d & m1) >> 18 ] );
		s.append( 1, charset[ (d & m2) >> 12 ] );
		s.append( 1, charset[ (d & m3) >>  6 ] );
		s.append( 1, '=' );

		i += 2;
	}
	else if( len == 1 )
	{
		d = m_buffer[i] << 16;

		s.append( 1, charset[ (d & m1) >> 18 ] );
		s.append( 1, charset[ (d & m2) >> 12 ] );
		s.append( "==", 2 );

		i++;
	}

	return s;
}


std::string Buffer::dump( void ) const
{
	std::stringstream ss;
	this->dump( ss );
	return ss.str();
}


void Buffer::dump( std::ostream& os ) const
{
	unsigned long i = 0L;
	unsigned long offset = 0L;
	unsigned long linelen = 16L;

	for( offset = 0; offset < m_buffer.size(); offset += linelen )
	{
		os << std::setfill('0')
		   << std::setw(4)
		   << std::hex
		   << offset;

		os << std::string( 4, ' ' );

		for( i = 0; i < linelen; i++ )
		{
			if( i + offset < m_buffer.size() )
				os << std::setfill('0')
				   << std::setw(2)
				   << std::hex
				   << static_cast<int>(m_buffer[i + offset])
				   << ' ';
			else
				os << std::string( 3, ' ' );

			if(!((i + 1) % 8))
				os << std::string( 4, ' ' );
		}

		for( i = 0; i < linelen; i++ )
		{
			if( i + offset < m_buffer.size() )
				if( std::isprint( m_buffer[ i + offset ] ) )
					os << m_buffer[ i + offset ];
				else
					os << '.';
			else
				os << ' ';

			if(!((i + 1) % 8))
				os << std::string( 2, ' ' );
		}

		os << std::endl;
	}
}


void Buffer::save( std::ostream &out ) const
{
	out.write( reinterpret_cast<const char*>(&m_buffer[0]), m_buffer.size() );
}


void Buffer::load( std::ifstream &in )
{
	m_buffer.insert( m_buffer.begin(), std::istream_iterator<unsigned char>(in), std::istream_iterator<unsigned char>() );
}


std::ostream& operator<<( std::ostream &os, const Buffer& buf )
{
	buf.dump( os );
	return os;
}

// end-of-file //
