#ifndef __CBUFFER_HXX__
#define __CBUFFER_HXX__

#include <string>
#include <vector>
#include <ostream>
#include <istream>

class Buffer
{
	friend std::ostream& operator<<( std::ostream &out, const Buffer& buf );

	public:
		Buffer( void );
		Buffer( const Buffer& buf );
		Buffer( const char * pstr );
		Buffer( char c );
		Buffer( const std::string& str );
		Buffer( const unsigned char * pbuf, std::size_t len );
		virtual ~Buffer( void );

		void clear( void );

		void assign( const char* str );
		void assign( char c );
		void assign( const std::string& str );
		void assign( const unsigned char * buf, std::size_t len );
		void assign( const Buffer& buf );

		Buffer& operator=( const char* pstr );
		Buffer& operator=( char c );
		Buffer& operator=( const std::string& str );
		Buffer& operator=( const Buffer& buf );

		void append( const char* str );
		void append( char c );
		void append( const std::string& str );
		void append( const unsigned char * buf, std::size_t len );
		void append( const Buffer& buf );

		Buffer& operator+=( const char* pstr );
		Buffer& operator+=( char c );
		Buffer& operator+=( const Buffer& buf );
		Buffer& operator+=( const std::string& str );

		Buffer sub( std::size_t start, std::size_t len );

		std::size_t length( void ) const;
		const unsigned char * buffer( void ) const;

		std::string ascii( void ) const;
		std::string hex( void ) const;
		std::string base64( void ) const;
		std::string dump( void ) const;

		void ascii( std::ostream &os ) const;
		void hex( std::ostream &os ) const;
		void base64( std::ostream &os ) const;
		void dump( std::ostream &os ) const;

		void save_file( std::string filename ) const;
		void load_file( std::string filename );
		void append_file( std::string filename );

	private:
		std::vector<unsigned char> m_buffer;
		void swap( Buffer& buf ) throw();
};

#endif

// end-of-file
