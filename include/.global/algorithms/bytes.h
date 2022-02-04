#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Algorithms
{
	/**
		@brief	Allow to check whether the value has only one significant bit.
		It also means that the value is one of power-of-two values.

		@param	value	The value to check.
		@tparam	TValue	Type of value to check. Should be one of integral types: int, char, bool e.t.c.
		@return			The value returned represents whether the value consists of single bit or not.
	*/
	template< typename TValue >
	inline constexpr auto IsSingleBitValue( const TValue value )
	{
		static_assert( std::is_integral_v<TValue>, "Type of value should be one of integral types." );
		return value == ( value & ~( value - 1 ) );
	}

	/**
		@brief	Packs 2 bytes into single 2-byte value.
		The value returned will be formed in endianness given through the template argument `ENDIANNESS`.
		@tparam	ENDIANNESS	The requested endianness.
		@return				Returns endian-dependent 4-byte unsigned integer value.
	*/
	template< Black::PlatformEndianness ENDIANNESS = Black::BUILD_ENDIANNESS >
	inline uint16_t GetPackedBytes( const uint8_t b1, const uint8_t b2 );

	/**
		@brief	Packs 4 bytes into single 4-byte value.
		The value returned will be formed in endianness given through the template argument `ENDIANNESS`.
		@tparam	ENDIANNESS	The requested endianness.
		@return				Returns endian-dependent 4-byte unsigned integer value.
	*/
	template< Black::PlatformEndianness ENDIANNESS = Black::BUILD_ENDIANNESS >
	inline uint32_t GetPackedBytes( const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4 );

	/**
		@brief	Packs 4 bytes into single 4-byte value.
		The value returned will be formed in endianness given through the template argument `ENDIANNESS`.
		@tparam	ENDIANNESS	The requested endianness.
		@return				Returns endian-dependent 4-byte unsigned integer value.
	*/
	template< Black::PlatformEndianness ENDIANNESS = Black::BUILD_ENDIANNESS >
	inline uint64_t GetPackedBytes(
		const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4,
		const uint8_t b5, const uint8_t b6, const uint8_t b7, const uint8_t b8
	);

	/**
		@brief	Transform the byte-order of value from native to requested.
		This function does nothing if native byte-order is same as requested.
		@param	value		The value to be transformed.
		@tparam	TValue		Type of value to transform.
		@tparam	ENDIANNESS	The requested endianness.
		return				The value returned is an transformed representation of input value.
	*/
	template< Black::PlatformEndianness ENDIANNESS, typename TValue >
	inline const TValue GetTransformedEndianness( const TValue value );
}
}
}
}
