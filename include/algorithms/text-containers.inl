#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
namespace Internal
{
	template< typename TOutStorage, typename TStringBuffer, typename... TArguments, size_t... INDICES >
	inline TOutStorage FormatString( const TStringBuffer& format, const std::tuple<TArguments...>& arguments, std::index_sequence<INDICES...> )
	{
		return Black::FormatString<TStringBuffer, TOutStorage>( format, std::get<INDICES>( arguments )... );
	}
}


	template< typename TStringBuffer, typename TOutStorage, typename... TArguments >
	inline TOutStorage FormatString( const TStringBuffer& format, const TArguments&... arguments )
	{
		static_assert( Internal::IS_VALID_STRING<TStringBuffer>, "The string buffer should be one of regular string types." );
		static_assert( Internal::HAS_SAME_CHAR_TYPE<TStringBuffer, TOutStorage>, "The type of characters should be same for `format` and result of function." );

		Internal::StringView<TStringBuffer> format_view{ format };
		return TOutStorage{ fmt::format( format_view, arguments... ) };
	}

	template< typename TStringBuffer, typename TOutStorage, typename... TArguments >
	inline TOutStorage FormatString( const TStringBuffer& format, const std::tuple<TArguments...>& arguments )
	{
		return Internal::FormatString<TOutStorage>( format, arguments, std::index_sequence_for<TArguments...>{} );
	}

	template< typename TStringBuffer, typename TOutView, typename... TArguments >
	inline TOutView FormatString( Black::PlainView<std::byte> result_buffer, const TStringBuffer& format, const TArguments&... arguments )
	{
		// @FIXME: Implement this stuff.
		return {};
	}

	template< typename TStringBuffer, typename TPattern, typename TReplacement >
	inline void ReplaceSubstring( TStringBuffer& string_buffer, const TPattern& pattern, const TReplacement& replacement )
	{
		static_assert( Internal::IS_VALID_STRING<TStringBuffer>, "The string buffer should be one of regular string types." );
		static_assert( Internal::IS_MUTABLE<TStringBuffer>, "The string buffer should be valid mutable string (e.g. `std::string` or `char*`)." );
		static_assert( Internal::IS_REARRANGEABLE<TStringBuffer>, "The string buffer should be valid rearrangeable string (e.g. `std::string`)." );
		static_assert( Internal::HAS_SAME_CHAR_TYPE<TStringBuffer, TPattern>, "Pattern has different character type." );
		static_assert( Internal::HAS_SAME_CHAR_TYPE<TStringBuffer, TReplacement>, "Replacement has different character type." );

		// At this point it's pretty obvious that the `TStringBuffer` is some instantiation of `std::basic_string`.

		// But it would be better to store the result into another storage and use string view for string buffer.
		Internal::StringStorage<TStringBuffer>		result;
		const Internal::StringView<TStringBuffer>	buffer_view{ string_buffer };
		const Internal::PatternView<TPattern>		pattern_view{ pattern };
		const Internal::PatternView<TReplacement>	replacement_view{ replacement };

		const size_t pattern_length		= Internal::GetStringLength( pattern_view );
		const size_t replacement_length	= Internal::GetStringLength( replacement_view );
		size_t substring_position		= 0;
		size_t pattern_position			= buffer_view.find( pattern_view, substring_position );

		// Early exit due to no patterns found in buffer.
		CRET( pattern_position == buffer_view.npos );

		while( pattern_position != buffer_view.npos )
		{
			if( substring_position != pattern_position )
			{
				result += buffer_view.substr( substring_position, pattern_position - substring_position );
			}

			if( replacement_length > 0 )
			{
				result += replacement_view;
			}

			substring_position	= pattern_position + pattern_length;
			pattern_position	= buffer_view.find( pattern_view, substring_position );
		}

		// Forcedly store the rest of string buffer.
		if( substring_position < buffer_view.length() )
		{
			result += buffer_view.substr( substring_position );
		}

		// After replacement is done, the result just may be exchanged with the initial string buffer.
		Black::Swap( string_buffer, result );
	}

	template< typename TStringBuffer, typename TOutStorage >
	inline TOutStorage GetUpperCase( const TStringBuffer& string_buffer )
	{
		static_assert( Internal::IS_VALID_STRING<TStringBuffer>, "The string buffer should be one of regular string types." );
		static_assert( Internal::HAS_SAME_CHAR_TYPE<TStringBuffer, TOutStorage>, "Result of function has different character type." );

		TOutStorage result{ string_buffer };
		MakeUpperCase( result );
		return result;
	}

	template< typename TStringBuffer >
	inline void MakeUpperCase( TStringBuffer& string_buffer )
	{
		static_assert( Internal::IS_VALID_STRING<TStringBuffer>, "The string buffer should be one of regular string types." );
		static_assert( Internal::IS_MUTABLE<TStringBuffer>, "The string buffer should be valid mutable string (e.g. `std::string` or `char*`)." );

		using Char = Internal::StringChar<TStringBuffer>;

		std::locale used_locale;
		decltype( auto ) char_traits	= std::use_facet< std::ctype<Char> >( used_locale );
		auto to_lower					= [&char_traits]( Char& symbol )
		{
			symbol = char_traits.toupper( symbol );
		};

		std::for_each( std::begin( string_buffer ), std::end( string_buffer ), to_lower );
	}

	template< typename TStringBuffer, typename TOutStorage >
	inline TOutStorage GetLowerCase( const TStringBuffer& string_buffer )
	{
		static_assert( Internal::IS_VALID_STRING<TStringBuffer>, "The string buffer should be one of regular string types." );
		static_assert( Internal::HAS_SAME_CHAR_TYPE<TStringBuffer, TOutStorage>, "Result of function has different character type." );

		TOutStorage result{ string_buffer };
		MakeLowerCase( result );
		return result;
	}

	template< typename TStringBuffer >
	inline void MakeLowerCase( TStringBuffer& string_buffer )
	{
		static_assert( Internal::IS_VALID_STRING<TStringBuffer>, "The string buffer should be one of regular string types." );
		static_assert( Internal::IS_MUTABLE<TStringBuffer>, "The string buffer should be valid mutable string (e.g. `std::string` or `char*`)." );

		using Char = Internal::StringChar<TStringBuffer>;

		std::locale used_locale;
		decltype( auto ) char_traits	= std::use_facet< std::ctype<Char> >( used_locale );
		auto to_lower					= [&char_traits]( Char& symbol )
		{
			symbol = char_traits.tolower( symbol );
		};

		std::for_each( std::begin( string_buffer ), std::end( string_buffer ), to_lower );
	}

	template< typename TStringBuffer, typename TOutStorage >
	inline TOutStorage GetTrimmedString( const TStringBuffer& string_buffer )
	{
		static_assert( Internal::IS_VALID_STRING<TStringBuffer>, "The string buffer should be one of regular string types." );
		static_assert( Internal::HAS_SAME_CHAR_TYPE<TStringBuffer, TOutStorage>, "Result of function has different character type." );

		Internal::StringView<TStringBuffer> result{ string_buffer };
		MakeTrimmedString( result );
		return TOutStorage{ result };
	}

	template< typename TStringBuffer >
	inline void MakeTrimmedString( TStringBuffer& string_buffer )
	{
		static_assert( Internal::IS_VALID_STRING<TStringBuffer>, "The string buffer should be one of regular string types." );
		static_assert( Internal::IS_REARRANGEABLE<TStringBuffer>, "The string buffer should be valid rearrangeable string (e.g. `std::string`)." );

		using View = Internal::StringView<TStringBuffer>;
		using Char = Internal::StringChar<TStringBuffer>;

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
		Black::Swap( string_buffer, buffer );
	}
}
}
}
