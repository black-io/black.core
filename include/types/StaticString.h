#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	// Compile-time string implementation.
	template< char... CHARS >
	struct StaticString final
	{
		// Get the regular string.
		constexpr const char* GetData() const;

		// Get the length of string.
		constexpr const size_t GetLength() const;

		// Get the element at position.
		constexpr char GetElement( const size_t index ) const;

		// Concatenate two strings.
		template< char... OTHER_CHARS >
		constexpr auto Combine( StaticString<OTHER_CHARS...> other ) const;

		// Remove the prefix from string.
		template< size_t PREFIX_LENGTH >
		constexpr auto RemovePrefix() const;

		// Remove the suffix from string.
		template< size_t PREFIX_LENGTH >
		constexpr auto RemoveSuffix() const;

		// Extract the substring from string.
		template< size_t POSITION, size_t LENGTH = Black::UNDEFINED_INDEX >
		constexpr auto GetSubstring() const;

		// Compare two strings.
		template< char... OTHER_CHARS >
		constexpr bool IsEqual( StaticString<OTHER_CHARS...> other ) const;

		// Check that the string starts with given substring.
		template< char... OTHER_CHARS >
		constexpr bool IsStartsWIth( StaticString<OTHER_CHARS...> other ) const;

		// Check that the string ends with given substring.
		template< char... OTHER_CHARS >
		constexpr bool IsEndsWIth( StaticString<OTHER_CHARS...> other ) const;


		template< char... OTHER_CHARS >
		constexpr auto operator + ( StaticString<OTHER_CHARS...> other ) const	{ return Combine( other ); };

		template< char... OTHER_CHARS >
		constexpr bool operator == ( StaticString<OTHER_CHARS...> other ) const	{ return IsEqual( other ); };

		template< char... OTHER_CHARS >
		constexpr bool operator != ( StaticString<OTHER_CHARS...> other ) const	{ return !IsEqual( other ); };
	};


	// Transform the string literal into static string.
	template< char... CHARS >
	constexpr StaticString<CHARS...> operator "" ToStaticString ()	{ return {} }
}
}
}
