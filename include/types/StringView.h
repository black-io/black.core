#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	/**
		@brief	Regular string view.
		The string view is just extension of `std::basic_string_view` template.
		`RegularStringView` type guaranties that the view of string will ends with '\0' symbol.

		@tparam	TChar	Type of viewed symbols.
		@tparam	TTraits	Used char traits.
	*/
	template< typename TChar, typename TTraits = std::char_traits<TChar> >
	class RegularStringView final : public std::basic_string_view<TChar, TTraits>
	{
	// Major inner types.
	public:
		/// @brief	Compatible STL string view type.
		using View		= std::basic_string_view<TChar, TTraits>;

		/// @brief	Compatible STL string type.
		template< typename TAllocator >
		using Host		= std::basic_string<TChar, TTraits, TAllocator>;

	// Construction and initialization.
	public:
		RegularStringView()													= default;
		RegularStringView( const RegularStringView& other )					= default;
		RegularStringView( RegularStringView&& other )						= default;
		RegularStringView( const TChar* const memory )						: RegularStringView{ View{ memory, TTraits::length( memory ) } } {};
		RegularStringView( const TChar* const memory, const size_t length )	: RegularStringView{ View{ memory, length } } {};

		template< typename TAllocator >
		RegularStringView( const Host<TAllocator>& string )					: RegularStringView{ static_cast<View>( string ) } {};

		explicit RegularStringView( View string )
			: std::basic_string_view<TChar, TTraits>{ std::move( string ) }
		{
			EXPECTS( View::length() == TTraits::length( View::data() ) );
		}

		RegularStringView& operator = ( const RegularStringView& other )	= default;
		RegularStringView& operator = ( RegularStringView&& other )			= default;
		RegularStringView& operator = ( const TChar* const memory )			{ return Black::CopyAndSwap( *this, memory ); };
		RegularStringView& operator = ( const View string )					{ return Black::CopyAndSwap( *this, string ); };

		template< typename TAllocator >
		RegularStringView& operator = ( const Host<TAllocator>& string )	{ return Black::CopyAndSwap( *this, string ); };
	};

	/// @brief	Regular multi-byte string view.
	using StringView	= RegularStringView<char>;

	/// @brief	Regular wide string view.
	using StringViewW	= RegularStringView<wchar_t>;

	/// @brief	Regular UTF-16 string view.
	using StringViewU16	= RegularStringView<char16_t>;

	// @brief	Regular UTF-32 string view.
	using StringViewU32	= RegularStringView<char32_t>;

	// Stream output operator for any regular string view.
	template< typename TChar, typename TTraits = std::char_traits<TChar> >
	inline std::basic_ostream<TChar, TTraits>& operator << ( std::basic_ostream<TChar, TTraits>& left, const RegularStringView<TChar, TTraits> right )
	{
		left << right.data();
		return left;
	}
}
}
}
