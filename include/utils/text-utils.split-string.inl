#pragma once


namespace Black::Core::TextUtils
{
namespace Internal
{
	template< typename TChar, typename TTraits, typename TPattern, typename TConsumer >
	inline const size_t GenericSplitString(
		TConsumer consume,
		const std::basic_string_view<TChar, TTraits> string_buffer,
		const TPattern& pattern,
		const size_t pattern_length,
		const TextSplittingFlags flags
	)
	{
		constexpr size_t not_found = std::basic_string_view<TChar, TTraits>::npos;

		CRET( string_buffer.empty(), 0 );
		size_t part_begin		= 0;
		size_t pattern_begin	= string_buffer.find( pattern, part_begin );
		CRET( flags.HasFlag( TextSplittingFlag::OnlySplitted ) && ( pattern_begin == string_buffer.npos ), 0 );

		std::vector<uint32_t> found_parts;
		while( part_begin < string_buffer.length() )
		{
			const size_t part_length	= ( pattern_begin == not_found )? not_found : pattern_begin - part_begin;
			auto part					= string_buffer.substr( part_begin, part_length );
			part_begin					= ( pattern_begin == not_found )? string_buffer.length() : pattern_begin + pattern_length;
			pattern_begin				= string_buffer.find( pattern, part_begin );

			if( flags.HasFlag( TextSplittingFlag::Trim ) )
			{
				MakeTrimmedString( part );
			}

			const uint32_t part_hash = Black::GetUnreliableHash( part );
			CCON( flags.HasFlag( TextSplittingFlag::DropEmpty ) && part.empty() );
			CCON( flags.HasFlag( TextSplittingFlag::OnlyUnique ) && Black::IsItemExists( found_parts, part_hash ) );

			found_parts.push_back( part_hash );
			consume( part );
		}

		return found_parts.size();
	}

	template< typename TChar, typename TTraits, typename TConsumer >
	inline const size_t SplitString(
		TConsumer consume,
		const std::basic_string_view<TChar, TTraits> string_buffer,
		const TChar pattern,
		const TextSplittingFlags flags
	)
	{
		return GenericSplitString( consume, string_buffer, pattern, 1, flags );
	}

	template< typename TChar, typename TTraits, typename TConsumer >
	inline const size_t SplitString(
		TConsumer consume,
		const std::basic_string_view<TChar, TTraits> string_buffer,
		const std::basic_string_view<TChar, TTraits> pattern,
		const TextSplittingFlags flags
	)
	{
		CRET( pattern.empty(), 0 );
		return GenericSplitString( consume, string_buffer, pattern, pattern.length(), flags );
	}
}


	template< typename TStorage, typename TStringBuffer, typename TPattern >
	inline const size_t SplitString( TStorage& parts, const TStringBuffer& string_buffer, const TPattern& pattern, const TextSplittingFlags flags )
	{
		static_assert( Internal::IS_VALID_STRING<TStringBuffer>, "The type input string buffer should be one of regular string types." );
		static_assert( Internal::IS_VALID_PATTERN<TPattern>, "The type split pattern should be one of regular string types or the regular char type." );

		using ValidStringView	= Internal::StringView<TStringBuffer>;
		using ValidPatternView	= Internal::PatternView<TPattern>;

		auto consume = [&parts]( const ValidStringView part ) { parts.emplace_back( part ); };
		return Internal::SplitString( consume, ValidStringView{ string_buffer }, ValidPatternView{ pattern }, flags );
	}
}
