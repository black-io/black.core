#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
	template< typename TValue, size_t ARRAY_LENGTH >
	inline const hash32_t GetUnreliableHash( const TValue (&data)[ ARRAY_LENGTH ], const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data, ARRAY_LENGTH * sizeof( TValue ), seed );
	}

	template< typename TValue >
	inline const hash32_t GetUnreliableHash( Black::PlainView<TValue> data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.GetData(), data.GetUsedBytes(), seed );
	}

	template< typename TValue >
	inline const hash32_t GetUnreliableHash( Black::PlainView<const TValue> data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.GetData(), data.GetUsedBytes(), seed );
	}

	template< typename TValue >
	inline const hash32_t GetUnreliableHash( const Black::PlainVector<TValue>& data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.GetData(), data.GetUsedBytes(), seed );
	}

	template< typename TChar, typename TTraits >
	inline const hash32_t GetUnreliableHash( std::basic_string_view<TChar, TTraits> data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.data(), data.length() * sizeof( TChar ), seed );
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline const hash32_t GetUnreliableHash( const std::basic_string<TChar, TTraits, TAllocator>& data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.data(), data.length() * sizeof( TChar ), seed );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline const hash32_t GetUnreliableHash( const std::array<TValue, ARRAY_LENGTH>& data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.data(), ARRAY_LENGTH * sizeof( TValue ), seed );
	}

	template< typename TValue, typename TAllocator >
	inline const hash32_t GetUnreliableHash( const std::vector<TValue, TAllocator>& data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.data(), data.size() * sizeof( TValue ), seed );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline const hash64_t GetUnreliableHash64( const TValue (&data)[ ARRAY_LENGTH ], const uint64_t seed = 0 )
	{
		return GetUnreliableHash64( data, ARRAY_LENGTH * sizeof( TValue ), seed );
	}

	template< typename TValue >
	inline const hash64_t GetUnreliableHash64( Black::PlainView<TValue> data, const uint64_t seed = 0 )
	{
		return GetUnreliableHash64( data.GetData(), data.GetUsedBytes(), seed );
	}

	template< typename TValue >
	inline const hash64_t GetUnreliableHash64( Black::PlainView<const TValue> data, const uint64_t seed = 0 )
	{
		return GetUnreliableHash64( data.GetData(), data.GetUsedBytes(), seed );
	}

	template< typename TValue >
	inline const hash64_t GetUnreliableHash64( const Black::PlainVector<TValue>& data, const uint64_t seed = 0 )
	{
		return GetUnreliableHash64( data.GetData(), data.GetUsedBytes(), seed );
	}

	template< typename TChar, typename TTraits >
	inline const hash64_t GetUnreliableHash64( std::basic_string_view<TChar, TTraits> data, const uint64_t seed = 0 )
	{
		return GetUnreliableHash64( data.data(), data.length() * sizeof( TChar ), seed );
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline const hash64_t GetUnreliableHash64( const std::basic_string<TChar, TTraits, TAllocator>& data, const uint64_t seed = 0 )
	{
		return GetUnreliableHash64( data.data(), data.length() * sizeof( TChar ), seed );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline const hash64_t GetUnreliableHash64( const std::array<TValue, ARRAY_LENGTH>& data, const uint64_t seed = 0 )
	{
		return GetUnreliableHash64( data.data(), ARRAY_LENGTH * sizeof( TValue ), seed );
	}

	template< typename TValue, typename TAllocator >
	inline const hash64_t GetUnreliableHash64( const std::vector<TValue, TAllocator>& data, const uint64_t seed = 0 )
	{
		return GetUnreliableHash64( data.data(), data.size() * sizeof( TValue ), seed );
	}

	inline const hash32_t GetUnreliableHash( const void* const memory, const size_t length, const uint32_t seed )
	{
		// Chosen implementation may be reviewed using next link.
		// http://vak.ru/doku.php/proj/hash/sources#ly_hash_function

		constexpr uint32_t salt1 = 1664525UL;
		constexpr uint32_t salt2 = 1013904223UL;

		uint32_t result = seed;

		const uint8_t* const data = reinterpret_cast<const uint8_t* const>( memory );
		for( size_t index = 0; index < length; ++index )
		{
			result = ( result * salt1 ) + data[ index ] + salt2;
		}

		return hash32_t{ result };
	}

	inline const hash64_t GetUnreliableHash64( const void* const memory, const size_t length, const uint64_t seed )
	{
		// Chosen implementation may be reviewed using next link.
		// https://en.wikipedia.org/wiki/Linear_congruential_generator#Parameters_in_common_use

		constexpr uint64_t salt1 = 6364136223846793005ULL;
		constexpr uint64_t salt2 = 1442695040888963407ULL;

		uint64_t result = seed;

		const uint8_t* const data = reinterpret_cast<const uint8_t* const>( memory );
		for( size_t index = 0; index < length; ++index )
		{
			result = ( result * salt1 ) + data[ index ] + salt2;
		}

		return hash64_t{ result };
	}
}
}
}
