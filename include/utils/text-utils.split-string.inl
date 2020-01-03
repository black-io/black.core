#pragma once


namespace Black::Core::TextUtils
{
namespace Internal
{
	template< typename TStringBuffer, typename TPattern, typename TConsumer >
	inline const size_t SplitString( TConsumer consume, const TStringBuffer& string_buffer, const TPattern& pattern, const TextSplittingFlags flags )
	{
		const size_t not_found		= string_buffer.npos;
		const size_t pattern_length	= GetStringLength( pattern );

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
}


	template< typename TStorage, typename TStringBuffer, typename TPattern >
	inline const size_t SplitString( TStorage& parts, const TStringBuffer& string_buffer, const TPattern& pattern, const TextSplittingFlags flags )
	{
		static_assert( Internal::IS_VALID_STRING<TStringBuffer>, "The type of input string buffer should be one of regular string types." );
		static_assert( Internal::IS_VALID_PATTERN<TPattern>, "The type of splitting pattern should be one of regular string types or the regular char type." );

		using ValidStringView	= Internal::StringView<TStringBuffer>;
		using ValidPatternView	= Internal::PatternView<TPattern>;

		static_assert( Internal::HAS_SAME_CHAR_TYPE<ValidStringView, ValidPatternView>, "Pattern has different character type." );

		auto consume = [&parts]( const ValidStringView part ) { parts.emplace_back( part ); };
		return Internal::SplitString( consume, ValidStringView{ string_buffer }, ValidPatternView{ pattern }, flags );
	}
}
