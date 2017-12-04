#pragma once


namespace Black
{
inline namespace Core
{
inline namespace HashUtils
{
	template< typename TValue, size_t ARRAY_LENGTH >
	inline const uint32_t GetUnreliableHash( const TValue (&data)[ ARRAY_LENGTH ], const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data, ARRAY_LENGTH * sizeof( TValue ), seed );
	}

	template< typename TValue >
	inline const uint32_t GetUnreliableHash( Black::PlainView<TValue> data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.GetData(), data.GetUsedBytes(), seed );
	}

	template< typename TValue >
	inline const uint32_t GetUnreliableHash( Black::PlainView<const TValue> data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.GetData(), data.GetUsedBytes(), seed );
	}

	template< typename TChar, typename TTraits >
	inline const uint32_t GetUnreliableHash( Black::RegularStringView<TChar, TTraits> data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.data(), data.length() * sizeof( TChar ), seed );
	}

	template< typename TValue >
	inline const uint32_t GetUnreliableHash( const Black::PlainVector<TValue>& data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.GetData(), data.GetUsedBytes(), seed );
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline const uint32_t GetUnreliableHash( const std::basic_string<TChar, TTraits, TAllocator>& data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.data(), data.length() * sizeof( TChar ), seed );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline const uint32_t GetUnreliableHash( const std::array<TValue, ARRAY_LENGTH>& data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.data(), ARRAY_LENGTH * sizeof( TValue ), seed );
	}

	template< typename TValue, typename TAllocator >
	inline const uint32_t GetUnreliableHash( const std::vector<TValue, TAllocator>& data, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( data.data(), data.size() * sizeof( TValue ), seed );
	}

	inline const uint32_t GetUnreliableHash( const void* const memory, const size_t length, const uint32_t seed )
	{
		// Chosen implementation may be reviewed using next link.
		// http://vak.ru/doku.php/proj/hash/sources#ly_hash_function

		constexpr uint32_t salt1	= 1664525UL;
		constexpr uint32_t salt2	= 1013904223UL;

		uint32_t result				= seed;
		const uint8_t* const data	= reinterpret_cast<const uint8_t* const>( memory );
		for( size_t index = 0; index < length; ++index )
		{
			result = ( result * salt1 ) + data[ index ] + salt2;
		}

		return result;
	}
}
}
}
