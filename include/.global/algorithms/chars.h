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
		@brief	Whether the candidate character is one of alphabetic or numeric characters.

		The valid alpha-numeric values are next:
		- digits (0123456789)
		- uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
		- lowercase letters (abcdefghijklmnopqrstuvwxyz)

		@param	candidate	The character to check condition.
		@return				`true` for valid alphabetic or numeric characters. `false` in other cases.
	*/
	template< typename TChar >
	inline const bool IsAlphaNumeric( const TChar candidate );

	/**
		@brief	Whether the candidate character is one of alphabetic characters.

		The valid alphabetic values are next:
		- uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
		- lowercase letters (abcdefghijklmnopqrstuvwxyz)

		@param	candidate	The character to check condition.
		@return				`true` for valid alphabetic characters. `false` in other cases.
	*/
	template< typename TChar >
	inline const bool IsAlphabetic( const TChar candidate );

	/**
		@brief	Whether the candidate character is one of lower-case alphabetic characters.

		The valid lower-case alphabetic values are next:
		- lowercase letters (abcdefghijklmnopqrstuvwxyz)

		@param	candidate	The character to check condition.
		@return				`true` for valid lower-case alphabetic characters. `false` in other cases.
	*/
	template< typename TChar >
	inline const bool IsLowerCase( const TChar candidate );

	/**
		@brief	Whether the candidate character is one of upper-case alphabetic characters.

		The valid upper-case alphabetic values are next:
		- uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ)

		@param	candidate	The character to check condition.
		@return				`true` for valid upper-case alphabetic characters. `false` in other cases.
	*/
	template< typename TChar >
	inline const bool IsUpperCase( const TChar candidate );

	/**
		@brief	Whether the candidate is one of numeric characters.

		The valid numeric values are next:
		- digits (0123456789)

		@param	candidate	The character to check condition.
		@return				`true` for valid numeric characters. `false` in other cases.
	*/
	template< typename TChar >
	inline const bool IsNumeric( const TChar candidate );

	/**
		@brief	Whether the candidate is one of hexadecimal numeric characters.

		The valid hexadecimal numeric values are next:
		- digits (0123456789)
		- uppercase letters (ABCDEF)
		- lowercase letters (abcdef)

		@param	candidate	The character to check condition.
		@return				`true` for valid hexadecimal characters. `false` in other cases.
	*/
	template< typename TChar >
	inline const bool IsHexadecimal( const TChar candidate );

	/**
		@brief	Whether the candidate is one of control characters.

		The valid control values are next:
		- 0x00-0x1F and 0x7F

		@param	candidate	The character to check condition.
		@return				`true` for valid control characters. `false` in other cases.
	*/
	template< typename TChar >
	inline const bool IsControl( const TChar candidate );

	/**
		@brief	Whether the candidate is one of graphical characters.

		The valid graphical values are next:
		- digits (0123456789)
		- uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
		- lowercase letters (abcdefghijklmnopqrstuvwxyz)
		- punctuation characters (!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)

		@param	candidate	The character to check condition.
		@return				`true` for valid graphical characters. `false` in other cases.
	*/
	template< typename TChar >
	inline const bool IsGraphical( const TChar candidate );

	/**
		@brief	Whether the candidate is one of whitespace characters.

		The valid whitespace values are next:
		- space (0x20, ' ')
		- form feed (0x0c, '\f')
		- line feed (0x0a, '\n')
		- carriage return (0x0d, '\r')
		- horizontal tab (0x09, '\t')
		- vertical tab (0x0b, '\v')

		@param	candidate	The character to check condition.
		@return				`true` for valid whitespace characters. `false` in other cases.
	*/
	template< typename TChar >
	inline const bool IsWhitespace( const TChar candidate );

	/**
		@brief	Whether the candidate is one of blank space characters.
		Blank characters are whitespace characters used to separate words within a sentence.

		The valid blank space values are next:
		- space (0x20, ' ')
		- horizontal tab (0x09, '\t')

		@param	candidate	The character to check condition.
		@return				`true` for valid blank space characters. `false` in other cases.
	*/
	template< typename TChar >
	inline const bool IsBlankSpace( const TChar candidate );

	/**
		@brief	Whether the candidate is one of printable characters.

		The valid printable values are next:
		- digits (0123456789)
		- uppercase letters (ABCDEFGHIJKLMNOPQRSTUVWXYZ)
		- lowercase letters (abcdefghijklmnopqrstuvwxyz)
		- punctuation characters (!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)
		- space (0x20, ' ')

		@param	candidate	The character to check condition.
		@return				`true` for valid printable characters. `false` in other cases.
	*/
	template< typename TChar >
	inline const bool IsPrintable( const TChar candidate );

	/**
		@brief	Whether the candidate is one of punctuation characters.

		The valid punctuation values are next:
		- punctuation characters (!"#$%&'()*+,-./:;<=>?@[\]^_`{|}~)

		@param	candidate	The character to check condition.
		@return				`true` for valid punctuation characters. `false` in other cases.
	*/
	template< typename TChar >
	inline const bool IsPunctuation( const TChar candidate );
}
}
}
}
