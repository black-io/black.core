#pragma once


namespace Black
{
	// Regular time type, in seconds.
	using Time			= float;

	// Regular time duration specification.
	using TimeDuration	= std::chrono::duration<Time>;

	// Regular 32-bit size specification.
	using size32_t		= uint32_t;

	// Regular 64-bit size specification. Always may be separated to high and low part, as well as be casted to `size_t`.
	union size64_t
	{
		int64_t			value	= 0;	// Total size, 8 bytes length.

		struct
		{
			size32_t	lo;				// Lower 4-byte part of total size.
			int32_t		hi;				// Upper 4-byte part of total size.
		};

		size64_t() {};
		size64_t( const int64_t value ) : value{ value } {};
		size64_t( const size32_t lo_part, const int32_t hi_part )
		{
			lo = lo_part;
			hi = hi_part;
		}

		inline size_t& operator * ()				{ return reinterpret_cast<size_t&>( value ); };
		inline const size_t& operator * () const	{ return reinterpret_cast<const size_t&>( value ); };

		inline operator int64_t& ()					{ return value; };
		inline operator const int64_t () const		{ return value; };
	};

	// Implementation for hashing object for enumeration types, which may be used with `std` containers.
	class EnumHash
	{
	public:
		// Hashing function. Uses `GetEnumValue` to produce the hash.
		template< typename TEnumeration >
		inline const size_t operator () ( const TEnumeration& value ) const
		{
			return static_cast<const size_t>( GetEnumValue( value ) );
		}
	};
}
