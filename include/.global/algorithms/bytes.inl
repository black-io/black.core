#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Algorithms
{
	template<>
	inline uint16_t GetPackedBytes<Black::PlatformEndianness::LittleEndian>( const uint8_t b1, const uint8_t b2 )
	{
		const uint8_t bytes[] = { b1, b2 };
		return *reinterpret_cast<const uint16_t*>( bytes );
	}

	template<>
	inline uint16_t GetPackedBytes<Black::PlatformEndianness::BigEndian>( const uint8_t b1, const uint8_t b2 )
	{
		const uint8_t bytes[] = { b2, b1 };
		return *reinterpret_cast<const uint16_t*>( bytes );
	}

	template<>
	inline uint32_t GetPackedBytes<Black::PlatformEndianness::LittleEndian>( const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4 )
	{
		const uint8_t bytes[] = { b1, b2, b3, b4 };
		return *reinterpret_cast<const uint32_t*>( bytes );
	}

	template<>
	inline uint32_t GetPackedBytes<Black::PlatformEndianness::BigEndian>( const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4 )
	{
		const uint8_t bytes[] = { b4, b3, b2, b1 };
		return *reinterpret_cast<const uint32_t*>( bytes );
	}

	template<>
	inline uint64_t GetPackedBytes<Black::PlatformEndianness::LittleEndian>(
		const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4,
		const uint8_t b5, const uint8_t b6, const uint8_t b7, const uint8_t b8
	)
	{
		const uint8_t bytes[] = { b1, b2, b3, b4, b5, b6, b7, b8 };
		return *reinterpret_cast<const uint64_t*>( bytes );
	}

	template<>
	inline uint64_t GetPackedBytes<Black::PlatformEndianness::BigEndian>(
		const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4,
		const uint8_t b5, const uint8_t b6, const uint8_t b7, const uint8_t b8
	)
	{
		const uint8_t bytes[] = { b8, b7, b6, b5, b4, b3, b2, b1 };
		return *reinterpret_cast<const uint64_t*>( bytes );
	}

	template< PlatformEndianness ENDIANNESS, Black::PlatformEndianness VALUE_ENDIANNESS, typename TValue >
	inline const TValue GetTransformedEndianness( const TValue value )
	{
		constexpr size_t value_length = sizeof( TValue );

		static_assert( std::is_integral_v<TValue>, "The type of value have to be an integer." );
		static_assert( value_length > 1, "Size of value may not be less than 2 bytes." );

		CRET( ENDIANNESS == VALUE_ENDIANNESS, value );

		TValue result;

		std::byte bytes[ value_length ];
		std::memcpy( bytes, &value, value_length );

		for( size_t index = 0; index < ( value_length / 2 ); ++index )
		{
			std::swap( bytes[ index ], bytes[ value_length - 1 - index ] );
		}

		std::memcpy( &result, bytes, value_length );
		return result;
	}
}
}
}
}
