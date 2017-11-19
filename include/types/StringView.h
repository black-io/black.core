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
		static_assert( Black::IS_SAME<TCharType, typename TChatTraits::char_type>, "Traits character type have to be same as `TCharType`." );


		using traits_type				= TChatTraits;
		using value_type				= TCharType;
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
		constexpr const_iterator begin() const						{ return cbegin(); };
		constexpr const_iterator cbegin() const						{ return m_memory; };
		constexpr const_iterator end() const						{ return cend(); };
		constexpr const_iterator cend() const						{ return m_memory + m_length; };
		constexpr const_reverse_iterator rbegin() const				{ return crbegin(); };
		constexpr const_reverse_iterator crbegin() const			{ return const_reverse_iterator{ cend() }; };
		constexpr const_reverse_iterator rend() const				{ return crend(); };
		constexpr const_reverse_iterator crend() const				{ return const_reverse_iterator{ cbegin() }; };

		constexpr const_reference at( const size_type index ) const	{ EXPECTS( index < m_length ); return m_memory[ index ]; };
		constexpr const_reference front() const						{ EXPECTS( m_length > 0 ); return *m_memory; };
		constexpr const_reference back() const						{ EXPECTS( m_length > 0 ); return m_memory[ m_length - 1 ]; };
		constexpr const_pointer data() const						{ return m_memory; };

		constexpr size_type length() const							{ return m_length; };
		constexpr size_type size() const							{ return length(); };
		constexpr size_type max_size() const						{ return numeric_limits<size_type>::max(); };
		constexpr bool empty() const								{ return m_length == 0; };

		constexpr void remove_prefix( const size_type skip_length )
		{
			EXPECTS( skip_length < m_length );

			m_memory += skip_length;
			m_length -= skip_length;
		}

		constexpr void remove_suffix( const size_type skip_length )
		{
			EXPECTS( skip_length < m_length );

			m_length -= skip_length;
		}

		constexpr void swap( RegularStringView& other )
		{
			std::swap( m_memory, other.m_memory );
			std::swap( m_length, other.m_length );
		}

		inline const size_type copy( value_type* dest_memory, const size_type copy_length, const size_type from_index = 0 ) const
		{
			EXPECTS( from_index < m_length );

			const size_type clamped_copy_length = std::min( copy_length, m_length - from_index );
			traits_type::copy( dest_memory, m_memory + from_index, clamped_copy_length );
			return clamped_copy_length;
		}

		constexpr RegularStringView substr( const size_type from_index = 0, const size_type sub_length = npos ) const
		{
			EXPECTS( from_index < m_length );

			return { m_memory + from_index, std::min( sub_length, m_length - from_index ) };
		}

		constexpr const int32_t compare( const RegularStringView& other ) const
		{
			const size_type max_length	= std::min( m_length, other.length() );
			auto compare_result			= traits_type::compare( m_memory, other.data(), max_length );
			CRET( compare_result != 0, compare_result );
			CRET( m_length == other.length(), 0 );
			return ( m_length < other.length() )? -1 : 1;
		}

		constexpr const int32_t compare( const size_type this_index, const size_type this_length, const RegularStringView& other ) const
		{
			return substr( this_index, this_length ).compare( other );
		}

		constexpr const int32_t compare(
			const size_type this_index,
			const size_type this_length,
			const RegularStringView& other,
			const size_type other_index,
			const size_type other_length
		) const
		{
			return substr( this_index, this_length ).compare( other.substr( other_index, other_length ) );
		}

		constexpr const int32_t compare( const value_type* chars ) const
		{
			return compare( RegularStringView<TCharType, TChatTraits>{ chars } );
		}

		constexpr const int32_t compare( const size_type this_index, const size_type this_length, const value_type* chars ) const
		{
			return substr( this_index, this_length ).compare( RegularStringView<TCharType, TChatTraits>{ chars } );
		}

		constexpr const int32_t compare( const size_type this_index, const size_type this_length, const value_type* chars, const size_type other_length ) const
		{
			return substr( this_index, this_length ).compare( RegularStringView<TCharType, TChatTraits>{ chars, other_length } );
		}

		inline const size_type find( const RegularStringView& pattern, const size_type from_index = 0 ) const
		{
			EXPECTS( !pattern.empty() );
			EXPECTS( from_index < m_length );
			CRET( ( m_length - from_index ) < pattern.length(), npos );

			auto match_begin	= end();
			auto pattern_cursor	= pattern.begin();
			for( auto cursor = std::next( begin(), from_index ); cursor != end(); ++cursor )
			{
				if( traits_type::eq( *cursor, *pattern_cursor ) )
				{
					if( match_begin == end() )
					{
						match_begin = cursor;
					}

					++pattern_cursor;
					CRET( pattern_cursor == pattern.end(), std::distance( begin(), match_begin ) );
				}
				else
				{
					CRET( std::distance( cursor, end() ) < pattern.length(), npos );
					pattern_cursor	= pattern.begin();
					match_begin		= end();
				}
			}

			return npos;
		}

		inline const size_type find( const value_type pattern, const size_type from_index = 0 ) const
		{
			EXPECTS( from_index < m_length );

			for( size_type index = from_index; index < m_length; ++index )
			{
				CRET( traits_type::eq( m_memory[ index ], pattern ), index );
			}

			return npos;
		}

		inline const size_type find( const value_type* pattern, const size_type from_index, const size_type pattern_length ) const
		{
			return find( RegularStringView<TCharType, TChatTraits>{ pattern, pattern_length }, from_index );
		}

		inline const size_type find( const value_type* pattern, const size_type from_index = 0 ) const
		{
			return find( RegularStringView<TCharType, TChatTraits>{ pattern }, from_index );
		}

		inline const size_type rfind( const RegularStringView& pattern, const size_type from_index = npos ) const
		{
			EXPECTS( !pattern.empty() );

			const size_type offset = std::min( from_index, m_length );
			CRET( ( m_length - offset ) < pattern.length(), npos );

			auto pattern_cursor = pattern.rbegin();
			for( auto cursor = std::next( rbegin(), offset ); cursor != rend(); ++cursor )
			{
				if( traits_type::eq( *cursor, *pattern_cursor ) )
				{
					++pattern_cursor;
					CRET( pattern_cursor == pattern.rend(), std::distance( begin(), cursor.base() ) - 1 );
				}
				else
				{
					CRET( std::distance( cursor, rend() ) < pattern.length(), npos );
					pattern_cursor	= pattern.rbegin();
				}
			}
		}

		inline const size_type rfind( const value_type pattern, const size_type from_index = npos ) const
		{
			const size_type offset = std::min( from_index, m_length - 1 );

			for( size_type index = offset; index >= 0; --index )
			{
				CRET( traits_type::eq( m_memory[ index ], pattern ), index );
			}

			return npos;
		}

		inline const size_type rfind( const value_type* pattern, const size_type from_index, const size_type pattern_length ) const
		{
			return rfind( RegularStringView<TCharType, TChatTraits>{ pattern, pattern_length }, from_index );
		}

		inline const size_type rfind( const value_type* pattern, const size_type from_index = npos ) const
		{
			return find( RegularStringView<TCharType, TChatTraits>{ pattern }, from_index );
		}

		inline const size_type find_first_of( const RegularStringView& pattern, const size_type from_index = 0 ) const;
		inline const size_type find_first_of( const value_type pattern, const size_type from_index = 0 ) const;
		inline const size_type find_first_of( const value_type* pattern, const size_type from_index, const size_type pattern_length ) const;
		inline const size_type find_first_of( const value_type* pattern, const size_type from_index = 0 ) const;
		inline const size_type find_last_of( const RegularStringView& pattern, const size_type from_index = npos ) const;
		inline const size_type find_last_of( const value_type pattern, const size_type from_index = npos ) const;
		inline const size_type find_last_of( const value_type* pattern, const size_type from_index, const size_type pattern_length ) const;
		inline const size_type find_last_of( const value_type* pattern, const size_type from_index = npos ) const;
		inline const size_type find_first_not_of( const RegularStringView& pattern, const size_type from_index = 0 ) const;
		inline const size_type find_first_not_of( const value_type pattern, const size_type from_index = 0 ) const;
		inline const size_type find_first_not_of( const value_type* pattern, const size_type from_index, const size_type pattern_length ) const;
		inline const size_type find_first_not_of( const value_type* pattern, const size_type from_index = 0 ) const;
		inline const size_type find_last_not_of( const RegularStringView& pattern, const size_type from_index = npos ) const;
		inline const size_type find_last_not_of( const value_type pattern, const size_type from_index = npos ) const;
		inline const size_type find_last_not_of( const value_type* pattern, const size_type from_index, const size_type pattern_length ) const;
		inline const size_type find_last_not_of( const value_type* pattern, const size_type from_index = npos ) const;


		constexpr const_reference operator [] ( const size_type index ) const	{ return at( index ); };

		constexpr const bool operator == ( const RegularStringView& other ) const		{ return compare( other ) == 0; };
		constexpr const bool operator != ( const RegularStringView& other ) const		{ return compare( other ) != 0; };
		constexpr const bool operator < ( const RegularStringView& other ) const		{ return compare( other ) < 0; };
		constexpr const bool operator <= ( const RegularStringView& other ) const		{ return compare( other ) <= 0; };
		constexpr const bool operator > ( const RegularStringView& other ) const		{ return compare( other ) > 0; };
		constexpr const bool operator >= ( const RegularStringView& other ) const		{ return compare( other ) >= 0; };

		template< typename TOtherTraits, typename TAllocator >
		constexpr const bool operator == ( const std::basic_string<TCharType, TOtherTraits, TAllocator>& other ) const
		{
			return operator==( RegularStringView<TCharType, TChatTraits>{ other } );
		}

		template< typename TOtherTraits, typename TAllocator >
		constexpr const bool operator != ( const std::basic_string<TCharType, TOtherTraits, TAllocator>& other ) const
		{
			return operator!=( RegularStringView<TCharType, TChatTraits>{ other } );
		}

		template< typename TOtherTraits, typename TAllocator >
		constexpr const bool operator < ( const std::basic_string<TCharType, TOtherTraits, TAllocator>& other ) const
		{
			return operator<( RegularStringView<TCharType, TChatTraits>{ other } );
		}

		template< typename TOtherTraits, typename TAllocator >
		constexpr const bool operator <= ( const std::basic_string<TCharType, TOtherTraits, TAllocator>& other ) const
		{
			return operator<=( RegularStringView<TCharType, TChatTraits>{ other } );
		}

		template< typename TOtherTraits, typename TAllocator >
		constexpr const bool operator > ( const std::basic_string<TCharType, TOtherTraits, TAllocator>& other ) const
		{
			return operator>( RegularStringView<TCharType, TChatTraits>{ other } );
		}

		template< typename TOtherTraits, typename TAllocator >
		constexpr const bool operator >= ( const std::basic_string<TCharType, TOtherTraits, TAllocator>& other ) const
		{
			return operator>=( RegularStringView<TCharType, TChatTraits>{ other } );
		}

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
