#pragma once


namespace Black
{
inline namespace Core
{
inline namespace HashUtils
{
	inline const uint32_t GetUnreliableHash( Black::PlainView<const uint8_t> data, const uint32_t seed )
	{
		// Chosen implementation may be reviewed using next link.
		// http://vak.ru/doku.php/proj/hash/sources#ly_hash_function

		constexpr uint32_t salt1	= 1664525UL;
		constexpr uint32_t salt2	= 1013904223UL;

		uint32_t result = seed;
		for( const uint8_t part : data )
		{
			result = ( result * salt1 ) + part + salt2;
		}

		return result;
	}

	// @TEMP: Temporary decision until the `PlainView::As` will be available.
	template< typename TValue >
	inline const uint32_t GetUnreliableHash( const TValue* data, const size_t data_length, const uint32_t seed = 0 )
	{
		return GetUnreliableHash( Black::PlainView<const uint8_t>{ reinterpret_cast<const uint8_t*>( data ), data_length * sizeof( TValue ) }, seed );
	}
}
}
}
