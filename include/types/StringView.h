#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	/**
		@brief	Regular string view.
		The string view specification is declared in C++17 standard.
		This specification is conformance interface until the C++17 approved for framework.
	*/
	template< typename TCharType, typename TChatTraits = std::char_traits<TCharType> >
	class RegularStringView final
	{
	// STL-conformance inner entities.
	public:
		static_assert( Black::IS_PLAIN<TCharType>, "The `TCharType` have to be plain type." );
		static_assert( Black::IS_SAME<TCharType, typename std::char_traits<TCharType>::char_type>, "Traits character type have to be same as `TCharType`." );


		using traits_type				= CharTraits;
		using value_type				= Char;
		using pointer					= value_type*;
		using const_pointer				= const value_type*;
		using reference					= value_type&;
		using const_reference			= const value_type&;
		using const_iterator			= const_pointer;
		using iterator					= const_iterator;
		using const_reverse_iterator	= std::reverse_iterator<const_iterator>;
		using reverse_iterator			= const_reverse_iterator;
		using size_type					= std::size_t;
		using difference_type			= std::ptrdiff_t;


		static constexpr size_type npos	= -1;

	// Construction interface.
	public:
		constexpr RegularStringView() = default;
		constexpr RegularStringView( const RegularStringView& ) = default;
		constexpr RegularStringView( const Char* chars, const size_t length ) : m_memory{ chars }, m_length{ length } {};
		inline RegularStringView( const Char* chars ) : m_memory{ chars }, m_length{ CharTraits::length( chars ) } {};

		template< typename TOtherTraits, typename TAllocator >
		inline RegularStringView( const std::basic_string<Char, TOtherTraits, TAllocator>& other ) : RegularStringView{ other.data(), other.size() } {};


		constexpr RegularStringView& operator = ( const RegularStringView& ) = default;

	// STL-conformance interface.
	public:
		constexpr const_iterator begin() const;
		constexpr const_iterator cbegin() const;
		constexpr const_iterator end() const;
		constexpr const_iterator cend() const;
		constexpr const_reverse_iterator rbegin() const;
		constexpr const_reverse_iterator crbegin() const;
		constexpr const_reverse_iterator rend() const;
		constexpr const_reverse_iterator crend() const;

		constexpr const_reference at( const size_type index ) const;
		constexpr const_reference front() const;
		constexpr const_reference back() const;
		constexpr const_pointer data() const;

		constexpr size_type length() const;
		constexpr size_type size() const	{ return length(); };
		constexpr size_type max_size() const;
		constexpr bool empty() const;

		constexpr void remove_prefix( const size_type skip_length );
		constexpr void remove_suffix( const size_type skip_length );
		constexpr void swap( RegularStringView& other );

		inline const size_type copy( value_type* dest_memory, const size_type copy_length, const size_type from_index = 0 ) const;
		constexpr RegularStringView substr( const size_type from_index = 0, const size_type sub_length = npos ) const;
		constexpr const int32_t compare( const RegularStringView& other ) const;
		constexpr const int32_t compare( const size_type this_index, const size_type this_length, const RegularStringView& other ) const;

		constexpr const int32_t compare(
			const size_type this_index,
			const size_type this_length,
			const RegularStringView& other,
			const size_type other_index,
			const size_type other_length
		) const;

		constexpr const int32_t compare( const value_type* chars ) const;
		constexpr const int32_t compare( const size_type this_index, const size_type this_length, const value_type* chars ) const;
		constexpr const int32_t compare( const size_type this_index, const size_type this_length, const value_type* chars, const size_type other_length ) const;


		constexpr const_reference operator [] ( const size_type index ) const	{ return at( index ); };

	// Private interface.
	private:

	private:
		const TCharType*	m_memory	= nullptr;
		size_t				m_length	= 0;
	};

	//
	using StringView	= RegularStringView<char>;

	//
	using StringViewW	= RegularStringView<wchar_t>;

	//
	using StringViewU16	= RegularStringView<char16_t>;

	//
	using StringViewU32	= RegularStringView<char32_t>;
}
}
}
