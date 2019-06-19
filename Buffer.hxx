#ifndef __CBUFFER_HXX__
#define __CBUFFER_HXX__

#include <string>
#include <vector>
#include <ostream>
#include <istream>

class Buffer
{
	public:
		Buffer( void );
		Buffer( const char * str );
		Buffer( char c );
		Buffer( std::string str );
		Buffer( const Buffer& buf );
		Buffer( const unsigned char * buf, std::size_t len );
		virtual ~Buffer( void );

		void append( const char * str );
		void append( char c );
		void append( std::string );
		void append( const unsigned char * buf, std::size_t len );
		void append( const Buffer& buf );

		std::size_t length( void ) const;
		const unsigned char * buffer( void ) const;
		std::string ascii( void ) const;
		std::string hex( void ) const;
		std::string base64( void ) const;
		std::string dump( void ) const;
		void dump( std::ostream& os ) const;

		void save( std::ostream &out ) const;
		void load( std::ifstream &in );

	private:
		std::vector<unsigned char> m_buffer;
		friend std::ostream& operator<<( std::ostream &out, const Buffer& buf );
};

#endif

// end-of-file
