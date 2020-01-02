#pragma once


namespace Black
{
inline namespace Core
{
inline namespace TextUtils
{
	template< typename TChar, typename... TArguments >
	inline std::basic_string<TChar> FormatString( const TChar* format, const TArguments&... arguments )
	{
		return fmt::format( std::basic_string<TChar>{ format }, arguments... );
	}

	template< typename TChar, typename... TArguments >
	inline Black::RegularStringView<TChar> FormatString( Black::PlainView<TChar> buffer, const char* format, const TArguments&... arguments )
	{
		return FormatString( buffer, std::basic_string<TChar>{ format } );
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline void ReplaceSubstring(
		std::basic_string<TChar, TTraits, TAllocator>& string_buffer,
		const TChar* pattern,
		const TChar* replacement
	)
	{
		ReplaceSubstring( string_buffer, Black::RegularStringView<TChar>{ pattern }, Black::RegularStringView<TChar>{ replacement } );
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline void ReplaceSubstring(
		std::basic_string<TChar, TTraits, TAllocator>& string_buffer,
		const std::basic_string<TChar, TTraits, TAllocator>& pattern,
		const TChar* replacement
	)
	{
		ReplaceSubstring( string_buffer, Black::RegularStringView<TChar>{ pattern }, Black::RegularStringView<TChar>{ replacement } );
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline void ReplaceSubstring(
		std::basic_string<TChar, TTraits, TAllocator>& string_buffer,
		const TChar* pattern,
		const std::basic_string<TChar, TTraits, TAllocator>& replacement
	)
	{
		ReplaceSubstring( string_buffer, Black::RegularStringView<TChar>{ pattern }, Black::RegularStringView<TChar>{ replacement } );
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline void ReplaceSubstring(
		std::basic_string<TChar, TTraits, TAllocator>& string_buffer,
		const std::basic_string<TChar, TTraits, TAllocator>& pattern,
		const std::basic_string<TChar, TTraits, TAllocator>& replacement
	)
	{
		ReplaceSubstring( string_buffer, Black::RegularStringView<TChar>{ pattern }, Black::RegularStringView<TChar>{ replacement } );
	}

	template< typename TChar >
	inline std::basic_string<TChar> GetUpperCase( const TChar* const string_buffer )
	{
		return GetUpperCase( Black::RegularStringView<TChar>{ string_buffer } );
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline std::basic_string<TChar> GetUpperCase( const std::basic_string<TChar, TTraits, TAllocator>& string_buffer )
	{
		return GetUpperCase( Black::RegularStringView<TChar>{ string_buffer } );
	}

	template< typename TChar >
	inline std::basic_string<TChar> GetLowerCase( const TChar* const string_buffer )
	{
		return GetLowerCase( Black::RegularStringView<TChar>{ string_buffer } );
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline std::basic_string<TChar> GetLowerCase( const std::basic_string<TChar, TTraits, TAllocator>& string_buffer )
	{
		return GetLowerCase( Black::RegularStringView<TChar>{ string_buffer } );
	}

	template< typename TChar >
	inline std::basic_string<TChar> GetTrimmedString( const TChar* const string_buffer )
	{
		return GetTrimmedString( Black::RegularStringView<TChar>{ string_buffer } );
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline std::basic_string<TChar> GetTrimmedString( const std::basic_string<TChar, TTraits, TAllocator>& string_buffer )
	{
		return GetTrimmedString( Black::RegularStringView<TChar>{ string_buffer } );
	}

	template< typename TChar, typename TTraits, typename TAllocator, typename TStorageAllocator, template< typename, typename > class TStorage >
	inline std::basic_string<TChar, TTraits, TAllocator> JoinString(
		const TStorage< std::basic_string<TChar, TTraits, TAllocator>, TStorageAllocator >& parts,
		const TChar* const pattern,
		const TextJoiningFlags flags = { TextJoiningFlag::DropEmpty }
	)
	{
		return JoinString( parts, Black::RegularStringView<TChar>{ pattern }, flags );
	}

	template< typename TChar, typename TTraits, typename TAllocator, typename TStorageAllocator, template< typename, typename > class TStorage >
	inline std::basic_string<TChar, TTraits, TAllocator> JoinString(
		const TStorage< std::basic_string<TChar, TTraits, TAllocator>, TStorageAllocator >& parts,
		const std::basic_string<TChar, TTraits, TAllocator>& pattern,
		const TextJoiningFlags flags = { TextJoiningFlag::DropEmpty }
	)
	{
		return JoinString( parts, Black::RegularStringView<TChar>{ pattern }, flags );
	}

	template< typename TChar, typename TTraits, typename TAllocator, typename... TArguments >
	inline std::basic_string<TChar, TTraits, TAllocator> FormatString(
		const std::basic_string<TChar, TTraits, TAllocator>& format,
		const TArguments&... arguments
	)
	{
		return fmt::format( format, arguments... );
	}

	template< typename TChar, typename TTraits, typename TAllocator, typename... TArguments >
	inline Black::RegularStringView<TChar> FormatString(
		Black::PlainView<TChar> buffer,
		const std::basic_string<TChar, TTraits, TAllocator>& format,
		const TArguments&... arguments
	)
	{
		// @FIXME: Implement this stuff.
		return {};
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline void ReplaceSubstring(
		std::basic_string<TChar, TTraits, TAllocator>& string_buffer,
		Black::RegularStringView<TChar> pattern,
		Black::RegularStringView<TChar> replacement
	)
	{
		const size_t replacement_length	= replacement.length();
		const size_t pattern_length		= pattern.length();
		size_t pattern_position			= string_buffer.find( pattern );

		while( std::basic_string<TChar, TTraits, TAllocator>::npos != pattern_position )
		{
			string_buffer.replace( pattern_position, pattern_length, replacement );
			pattern_position = string_buffer.find( pattern, pattern_position + replacement_length );
		}
	}

	template< typename TChar >
	inline std::basic_string<TChar> GetUpperCase( Black::RegularStringView<TChar> string_buffer )
	{
		std::basic_string<TChar> result{ string_buffer.begin(), string_buffer.end() };
		MakeUpperCase( result );
		return result;
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline void MakeUpperCase( std::basic_string<TChar, TTraits, TAllocator>& string_buffer )
	{
		std::locale used_locale;
		decltype( auto ) char_traits = std::use_facet< std::ctype<TChar> >( used_locale );
		std::for_each( string_buffer.begin(), string_buffer.end(), [&char_traits]( TChar& symbol ) { symbol = char_traits.toupper( symbol ); } );
	}

	template< typename TChar >
	inline std::basic_string<TChar> GetLowerCase( Black::RegularStringView<TChar> string_buffer )
	{
		std::basic_string<TChar> result{ string_buffer.begin(), string_buffer.end() };
		MakeLowerCase( result );
		return result;
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline void MakeLowerCase( std::basic_string<TChar, TTraits, TAllocator>& string_buffer )
	{
		std::locale used_locale;
		decltype( auto ) char_traits = std::use_facet< std::ctype<TChar> >( used_locale );
		std::for_each( string_buffer.begin(), string_buffer.end(), [&char_traits]( TChar& symbol ) { symbol = char_traits.tolower( symbol ); } );
	}

	template< typename TChar >
	inline std::basic_string<TChar> GetTrimmedString( Black::RegularStringView<TChar> string_buffer )
	{
		CRET( string_buffer.empty(), {} );

		std::locale used_locale;
		decltype( auto ) char_traits	= std::use_facet< std::ctype<TChar> >( used_locale );
		auto space_filter				= [&char_traits]( const TChar& symbol ) -> bool
		{
			return !char_traits.is( std::ctype_base::space, symbol );
		};

		auto found_begin = std::find_if( std::begin( string_buffer ), std::end( string_buffer ), space_filter );
		CRET( found_begin == std::end( string_buffer ), {} );

		auto found_end	= std::find_if( std::rbegin( string_buffer ), std::rend( string_buffer ), space_filter ).base();
		return { found_begin, found_end };
	}

	template< typename TStringBuffer >
	inline void MakeTrimmedString( TStringBuffer& string_buffer )
	{
		static_assert( Internal::IS_REARRANGEABLE<TStringBuffer>, "The string buffer should be valid rearrangeable string (e.g. `std::string`)." );

		using View = Internal::StringView<TStringBuffer>;
		using Char = typename View::value_type;

		const View buffer_view{ string_buffer };
		CRET( buffer_view.empty() );

		std::locale used_locale;
		decltype( auto ) char_traits	= std::use_facet< std::ctype<Char> >( used_locale );
		auto space_filter				= [&char_traits]( const Char& symbol ) -> bool
		{
			return !char_traits.is( std::ctype_base::space, symbol );
		};

		auto found_begin = std::find_if( buffer_view.begin(), buffer_view.end(), space_filter );
		if( found_begin == buffer_view.end() )
		{
			string_buffer = {};
			return;
		}

		auto found_end	= std::find_if( buffer_view.rbegin(), buffer_view.rend(), space_filter ).base();
		CRET( std::distance( found_begin, found_end ) == buffer_view.length() );

		const size_t result_position	= std::distance( buffer_view.begin(), found_begin );
		const size_t result_length		= std::distance( found_begin, found_end );
		TStringBuffer buffer{ buffer_view.substr( result_position, result_length ) };
		std::swap( string_buffer, buffer );
	}

	template< typename TChar, typename TTraits, typename TAllocator, typename TStorageAllocator, template< typename, typename > class TStorage >
	inline std::basic_string<TChar, TTraits, TAllocator> JoinString(
		const TStorage< std::basic_string<TChar, TTraits, TAllocator>, TStorageAllocator >& parts,
		Black::RegularStringView<TChar> pattern,
		const TextJoiningFlags flags
	)
	{
		using String = std::basic_string<TChar, TTraits, TAllocator>;

		CRET( parts.empty(), {} );
		String result;

		String trimmed_part;
		for( auto& part : parts )
		{
			if( flags.HasFlag<TextJoiningFlag::Trim>() )
			{
				trimmed_part = GetTrimmedString( part );
				CCON( flags.HasFlag<TextJoiningFlag::DropEmpty>() && trimmed_part.empty() );
			}
			else
			{
				CCON( flags.HasFlag<TextJoiningFlag::DropEmpty>() && part.empty() );
			}

			const String& used_part	= ( flags.HasFlag<TextJoiningFlag::Trim>() )? trimmed_part : part;
			result					+= ( result.empty() )? used_part : String{ pattern } + used_part;
		}

		return result;
	}
}
}
}
