#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	/**
	*/
	template< char... CHARS >
	struct StaticString final
	{
		// Get the regular string.
		constexpr const char* GetData() const;

		// Get the length of string.
		constexpr const size_t GetLength() const;
	};


	// Transform the string literal into static string.
	template< char... CHARS >
	constexpr StaticString<CHARS...> operator "" ToStaticString ()	{ return {} }
}
}
}
