#ifndef __CBUFFER_HXX__
#define __CBUFFER_HXX__

#include <string>
#include <vector>
#include <ostream>

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

		bool operator==( const Buffer& buf ) const;
		bool operator!=( const Buffer& buf ) const;

		bool equal( const Buffer& buf ) const;

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
