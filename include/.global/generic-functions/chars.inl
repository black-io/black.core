#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace GenericFunctions
{
	template< typename TChar >
	inline const bool IsAlphaNumeric( const TChar candidate )
	{
		if constexpr( std::is_same_v<std::decay_t<TChar>, char> )
		{
			return std::isalnum( static_cast<int32_t>( candidate ) ) != 0;
		}
		else if constexpr( std::is_same_v<std::decay_t<TChar>, wchar_t> )
		{
			return std::iswalnum( static_cast<wint_t>( candidate ) ) != 0;
		}
		else
		{
			return false;
		}
	}

	template< typename TChar >
	inline const bool IsAlphabetic( const TChar candidate )
	{
		if constexpr( std::is_same_v<std::decay_t<TChar>, char> )
		{
			return std::isalpha( static_cast<int32_t>( candidate ) ) != 0;
		}
		else if constexpr( std::is_same_v<std::decay_t<TChar>, wchar_t> )
		{
			return std::iswalpha( static_cast<wint_t>( candidate ) ) != 0;
		}
		else
		{
			return false;
		}
	}

	template< typename TChar >
	inline const bool IsLowerCase( const TChar candidate )
	{
		if constexpr( std::is_same_v<std::decay_t<TChar>, char> )
		{
			return std::islower( static_cast<int32_t>( candidate ) ) != 0;
		}
		else if constexpr( std::is_same_v<std::decay_t<TChar>, wchar_t> )
		{
			return std::iswlower( static_cast<wint_t>( candidate ) ) != 0;
		}
		else
		{
			return false;
		}
	}

	template< typename TChar >
	inline const bool IsUpperCase( const TChar candidate )
	{
		if constexpr( std::is_same_v<std::decay_t<TChar>, char> )
		{
			return std::isupper( static_cast<int32_t>( candidate ) ) != 0;
		}
		else if constexpr( std::is_same_v<std::decay_t<TChar>, wchar_t> )
		{
			return std::iswupper( static_cast<wint_t>( candidate ) ) != 0;
		}
		else
		{
			return false;
		}
	}

	template< typename TChar >
	inline const bool IsNumeric( const TChar candidate )
	{
		if constexpr( std::is_same_v<std::decay_t<TChar>, char> )
		{
			return std::isdigit( static_cast<int32_t>( candidate ) ) != 0;
		}
		else if constexpr( std::is_same_v<std::decay_t<TChar>, wchar_t> )
		{
			return std::iswdigit( static_cast<wint_t>( candidate ) ) != 0;
		}
		else
		{
			return false;
		}
	}

	template< typename TChar >
	inline const bool IsHexadecimal( const TChar candidate )
	{
		if constexpr( std::is_same_v<std::decay_t<TChar>, char> )
		{
			return std::isxdigit( static_cast<int32_t>( candidate ) ) != 0;
		}
		else if constexpr( std::is_same_v<std::decay_t<TChar>, wchar_t> )
		{
			return std::iswxdigit( static_cast<wint_t>( candidate ) ) != 0;
		}
		else
		{
			return false;
		}
	}

	template< typename TChar >
	inline const bool IsControl( const TChar candidate )
	{
		if constexpr( std::is_same_v<std::decay_t<TChar>, char> )
		{
			return std::iscntrl( static_cast<int32_t>( candidate ) ) != 0;
		}
		else if constexpr( std::is_same_v<std::decay_t<TChar>, wchar_t> )
		{
			return std::iswcntrl( static_cast<wint_t>( candidate ) ) != 0;
		}
		else
		{
			return false;
		}
	}

	template< typename TChar >
	inline const bool IsGraphical( const TChar candidate )
	{
		if constexpr( std::is_same_v<std::decay_t<TChar>, char> )
		{
			return std::isgraph( static_cast<int32_t>( candidate ) ) != 0;
		}
		else if constexpr( std::is_same_v<std::decay_t<TChar>, wchar_t> )
		{
			return std::iswgraph( static_cast<wint_t>( candidate ) ) != 0;
		}
		else
		{
			return false;
		}
	}

	template< typename TChar >
	inline const bool IsWhitespace( const TChar candidate )
	{
		if constexpr( std::is_same_v<std::decay_t<TChar>, char> )
		{
			return std::isspace( static_cast<int32_t>( candidate ) ) != 0;
		}
		else if constexpr( std::is_same_v<std::decay_t<TChar>, wchar_t> )
		{
			return std::iswspace( static_cast<wint_t>( candidate ) ) != 0;
		}
		else
		{
			return false;
		}
	}

	template< typename TChar >
	inline const bool IsBlankSpace( const TChar candidate )
	{
		if constexpr( std::is_same_v<std::decay_t<TChar>, char> )
		{
			return std::isblank( static_cast<int32_t>( candidate ) ) != 0;
		}
		else if constexpr( std::is_same_v<std::decay_t<TChar>, wchar_t> )
		{
			return std::iswblank( static_cast<wint_t>( candidate ) ) != 0;
		}
		else
		{
			return false;
		}
	}

	template< typename TChar >
	inline const bool IsPrintable( const TChar candidate )
	{
		if constexpr( std::is_same_v<std::decay_t<TChar>, char> )
		{
			return std::isprint( static_cast<int32_t>( candidate ) ) != 0;
		}
		else if constexpr( std::is_same_v<std::decay_t<TChar>, wchar_t> )
		{
			return std::iswprint( static_cast<wint_t>( candidate ) ) != 0;
		}
		else
		{
			return false;
		}
	}

	template< typename TChar >
	inline const bool IsPunctuation( const TChar candidate )
	{
		if constexpr( std::is_same_v<std::decay_t<TChar>, char> )
		{
			return std::ispunct( static_cast<int32_t>( candidate ) ) != 0;
		}
		else if constexpr( std::is_same_v<std::decay_t<TChar>, wchar_t> )
		{
			return std::iswpunct( static_cast<wint_t>( candidate ) ) != 0;
		}
		else
		{
			return false;
		}
	}
}
}
}
}
