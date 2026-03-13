#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace GenericFunctions
{
	/**
		@brief	Allow to check whether the value has only one significant bit.
		It also means that the value is one of power-of-two values.

		@param	value	The value to check.
		@tparam	TValue	Type of value to check. Should be one of integral types: int, char, bool e.t.c.
		@return			The value returned represents whether the value consists of single bit or not.
	*/
	template< typename TValue >
	inline constexpr bool IsSingleBitValue( const TValue value );

	/**
		@brief	Get the smallest PoT value, that is not less then given `value`.

		PoT (Power of Two) value are that ones, where only one bit is set. Such value may be obtained by shifting left the `1` by number of bits.
		This function produces the nearest PoT value, that is equal or greater the given `value`.

		@tparam	TValue	Type of given value and result as well. Should be one of integral types: int, char, bool e.t.c.
		@param	value	The value to be round up.
		@return			The value returned is PoT value that fits the given `value`.
		@retval	value	In case the given `value` already PoT.
	*/
	template< typename TValue >
	inline constexpr TValue CeilPowerOfTwo( const TValue value );

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
		@param	value				The value to be transformed.
		@tparam	TValue				Type of value to transform.
		@tparam	ENDIANNESS			The requested endianness.
		@tparam	VALUE_ENDIANNESS	The source endianness of `value`. By default it considered as `Black::BUILD_ENDIANNESS`.
		return						The value returned is an transformed representation of input value.
	*/
	template< Black::PlatformEndianness ENDIANNESS, Black::PlatformEndianness VALUE_ENDIANNESS = Black::BUILD_ENDIANNESS, typename TValue >
	inline const TValue GetTransformedEndianness( const TValue value );
}
}
}
}
