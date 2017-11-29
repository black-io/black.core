#pragma once


namespace Black
{
inline namespace Core
{
inline namespace TextUtils
{
	template< typename TChar, typename TTraits, typename TAllocator, typename... TArguments >
	inline std::basic_string<TChar, TTraits, TAllocator> FormatString(
		const std::basic_string<TChar, TTraits, TAllocator>& format,
		const TArguments&... arguments
	)
	{
		return fmt::format( format, arguments... );
	}

	template< typename TChar, typename... TArguments >
	inline std::basic_string<TChar> FormatString( const TChar* format, const TArguments&... arguments )
	{
		return fmt::format( std::basic_string<TChar>{ format }, arguments... );
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

	template< typename TChar, typename... TArguments >
	inline Black::RegularStringView<TChar> FormatString( Black::PlainView<TChar> buffer, const char* format, const TArguments&... arguments )
	{
		return FormatString( buffer, std::basic_string<TChar>{ format } );
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

		while( std::basic_string<TCharType, TCharTraits, TStringAllocator>::npos != pattern_position )
		{
			string_buffer.replace( pattern_position, pattern_length, replacement );
			pattern_position = string_buffer.find( pattern, pattern_position + replacement_length );
		}
	}

	template< typename TChar >
	inline std::basic_string<TChar> GetUpperCase( Black::RegularStringView<TChar>& string_buffer )
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
	inline std::basic_string<TChar> GetLowerCase( Black::RegularStringView<TChar>& string_buffer )
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
	inline std::basic_string<TChar> GetTrimmedString( Black::RegularStringView<TChar>& string_buffer )
	{
		std::locale used_locale;
		decltype( auto ) char_traits	= std::use_facet< std::ctype<TCharType> >( used_locale );
		auto space_filter				= [&char_traits]( const TChar& symbol ) -> bool
		{
			return !char_traits.is( std::ctype_base::space, symbol );
		};

		std::basic_string<TChar> result;

		auto found_begin = std::find_if( std::begin( string_buffer ), std::end( found_begin ), space_filter );
		CRET( found_begin == std::end( string_buffer ) );

		auto found_end	= std::find_if( std::rbegin( string_buffer ), std::rend( found_begin ), space_filter ).base();
		result			= { found_begin, found_end };
	}

	template< typename TChar, typename TTraits, typename TAllocator >
	inline void MakeTrimmedString( std::basic_string<TChar, TTraits, TAllocator>& string_buffer )
	{
		std::locale used_locale;
		decltype( auto ) char_traits	= std::use_facet< std::ctype<TCharType> >( used_locale );
		auto space_filter				= [&char_traits]( const TChar& symbol ) -> bool
		{
			return !char_traits.is( std::ctype_base::space, symbol );
		};

		decltype( string_buffer ) buffer = std::move( string_buffer );

		auto found_begin = std::find_if( std::begin( buffer ), std::end( buffer ), space_filter );
		CRET( found_begin == std::end( buffer ) );

		auto found_end	= std::find_if( std::rbegin( buffer ), std::rend( buffer ), space_filter ).base();
		string_buffer	= { found_begin, found_end };
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

			String& used_part	= ( flags.HasFlag<TextJoiningFlag::Trim>() )? trimmed_part : part;
			result				+= ( result.empty() )? used_part : pattern + used_part;
		}

		return result;
	}

	template< typename TChar, typename TTraits, typename TAllocator, typename TStorageAllocator, template< typename, typename > class TStorage >
	inline const size_t SplitString(
		TStorage< std::basic_string<TChar, TTraits, TAllocator>, TStorageAllocator >& parts,
		Black::RegularStringView<TChar> string_buffer,
		Black::RegularStringView<TChar> pattern,
		const TextSplittingFlags flags
	)
	{
		using String = std::basic_string<TChar, TTraits, TAllocator>;

		CRET( string_buffer.empty() || pattern.empty(), 0 );
		const size_t stored_parts	= parts.size();
		size_t part_begin			= 0;
		size_t pattern_begin		= string_buffer.find( pattern, part_begin );
		CRET( flags.HasFlag<TextSplittingFlag::OnlySplitted>() && ( pattern_begin == String::npos ), 0 );

		while( pattern_begin < string_buffer.size() )
		{
			const size_t part_length	= ( pattern_begin == String::npos )? String::npos : pattern_begin - part_begin;
			String part					= string_buffer.substr( part_begin, part_length );
			part_begin					= ( pattern_begin == String::npos )? string_buffer.length() : pattern_begin + pattern.length();
			pattern_begin				= string_buffer.find( pattern, part_begin );

			if( flags.HasFlag<TextSplittingFlag::Trim>() )
			{
				MakeTrimmedString( part );
			}

			CCON( flags.HasFlag<TextSplittingFlag::DropEmpty>() && part.empty() );
			CCON( flags.HasFlag<TextSplittingFlag::OnlyUnique>() && Black::IsItemExists( parts, part ) );

			parts.emplace_back( std::move( part ) );
		}

		return parts.size() - stored_parts;
	}

	template< typename TChar, typename TTraits, typename TAllocator, typename TStorageAllocator, template< typename, typename > class TStorage >
	inline std::basic_string<TChar, TTraits, TAllocator> JoinString(
		const TStorage< std::basic_string<TChar, TTraits, TAllocator>, TStorageAllocator >& parts,
		const TChar* pattern,
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

	template< typename TChar, typename TTraits, typename TAllocator, typename TStorageAllocator, template< typename, typename > class TStorage >
	inline const size_t SplitString(
		TStorage< std::basic_string<TChar, TTraits, TAllocator>, TStorageAllocator >& parts,
		const TChar* string_buffer,
		const TChar* pattern,
		const TextSplittingFlags flags = { TextSplittingFlag::DropEmpty, TextSplittingFlag::Trim }
	)
	{
		return SplitString( parts, Black::RegularStringView<TChar>{ string_buffer }, Black::RegularStringView<TChar>{ pattern }, flags );
	}

	template< typename TChar, typename TTraits, typename TAllocator, typename TStorageAllocator, template< typename, typename > class TStorage >
	inline const size_t SplitString(
		TStorage< std::basic_string<TChar, TTraits, TAllocator>, TStorageAllocator >& parts,
		const std::basic_string<TChar, TTraits, TAllocator>& string_buffer,
		const std::basic_string<TChar, TTraits, TAllocator>& pattern,
		const TextSplittingFlags flags = { TextSplittingFlag::DropEmpty, TextSplittingFlag::Trim }
	)
	{
		return SplitString( parts, Black::RegularStringView<TChar>{ string_buffer }, Black::RegularStringView<TChar>{ pattern }, flags );
	}

	template< typename TChar, typename TTraits, typename TAllocator, typename TStorageAllocator, template< typename, typename > class TStorage >
	inline const size_t SplitString(
		TStorage< std::basic_string<TChar, TTraits, TAllocator>, TStorageAllocator >& parts,
		const TChar* string_buffer,
		const std::basic_string<TChar, TTraits, TAllocator>& pattern,
		const TextSplittingFlags flags = { TextSplittingFlag::DropEmpty, TextSplittingFlag::Trim }
	)
	{
		return SplitString( parts, Black::RegularStringView<TChar>{ string_buffer }, Black::RegularStringView<TChar>{ pattern }, flags );
	}

	template< typename TChar, typename TTraits, typename TAllocator, typename TStorageAllocator, template< typename, typename > class TStorage >
	inline const size_t SplitString(
		TStorage< std::basic_string<TChar, TTraits, TAllocator>, TStorageAllocator >& parts,
		const std::basic_string<TChar, TTraits, TAllocator>& string_buffer,
		const TChar* pattern,
		const TextSplittingFlags flags = { TextSplittingFlag::DropEmpty, TextSplittingFlag::Trim }
	)
	{
		return SplitString( parts, Black::RegularStringView<TChar>{ string_buffer }, Black::RegularStringView<TChar>{ pattern }, flags );
	}
}
}
}
