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
}
}
}
