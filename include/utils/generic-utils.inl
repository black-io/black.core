#pragma once


namespace Black
{
	template<>
	inline uint32_t GetPackedBytes<PlatformEndianness::LittleEndian>( const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4 )
	{
		const uint8_t bytes[] = { b1, b2, b3, b4 };
		return *reinterpret_cast<const uint32_t*>( bytes );
	}

	template<>
	inline uint32_t GetPackedBytes<PlatformEndianness::BigEndian>( const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4 )
	{
		const uint8_t bytes[] = { b4, b3, b2, b1 };
		return *reinterpret_cast<const uint32_t*>( bytes );
	}

	template<>
	inline uint64_t GetPackedBytes<PlatformEndianness::LittleEndian>(
		const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4,
		const uint8_t b5, const uint8_t b6, const uint8_t b7, const uint8_t b8
	)
	{
		const uint8_t bytes[] = { b1, b2, b3, b4, b5, b6, b7, b8 };
		return *reinterpret_cast<const uint64_t*>( bytes );
	}

	template<>
	inline uint64_t GetPackedBytes<PlatformEndianness::BigEndian>(
		const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4,
		const uint8_t b5, const uint8_t b6, const uint8_t b7, const uint8_t b8
	)
	{
		const uint8_t bytes[] = { b8, b7, b6, b5, b4, b3, b2, b1 };
		return *reinterpret_cast<const uint64_t*>( bytes );
	}

	template< PlatformEndianness ENDIANNESS, typename TValue >
	inline const TValue GetTransformedEndianness( const TValue value )
	{
		constexpr size_t value_length = sizeof( TValue );
		static_assert( Black::IS_INTEGER<TValue>, "The type of value have to be an integer." );
		static_assert( value_length > 1, "Size of value may not be less than 2 bytes." );

		CRET( ENDIANNESS == Black::BUILD_ENDIANNESS, value );

		TValue result;
		const uint8_t* bytes	= reinterpret_cast<const uint8_t*>( &value );
		uint8_t* result_bytes	= reinterpret_cast<const uint8_t*>( &result );

		for( size_t index = 0; index < value_length; ++index )
		{
			result_bytes[ value_length - 1 - index ] = bytes[ index ];
		}

		return result;
	}
}
