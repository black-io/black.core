#pragma once


namespace Black::Core::TextUtils
{
namespace Internal
{
	template< typename TOutStorage, typename TPattern, typename TGenerator >
	inline TOutStorage JoinString( TGenerator generate, const size_t count, const TPattern pattern, const TextJoiningFlags flags )
	{
		TOutStorage result;
		for( size_t index = 0; index < count; ++index )
		{
			auto part = generate();

			if( flags.HasFlag( Black::TextJoiningFlag::Trim ) )
			{
				Black::MakeTrimmedString( part );
			}

			CCON( flags.HasFlag( Black::TextJoiningFlag::DropEmpty ) && part.empty() );

			if( !result.empty() )
			{
				result += pattern;
			}

			result += part;
		}

		return result;
	}
}


	template< typename TPartStorage, typename TPattern, typename TOutStorage >
	inline TOutStorage JoinString( const TPartStorage& parts, const TPattern& pattern, const TextJoiningFlags flags )
	{
		static_assert( Internal::IS_VALID_STRING<typename TPartStorage::value_type>, "The type of string parts should be one of regular string types." );
		static_assert( Internal::IS_VALID_STRING<TOutStorage>, "The type of output string buffer should be one of regular string types." );
		static_assert( Internal::IS_VALID_PATTERN<TPattern>, "The type of joining pattern should be one of regular string types or the regular char type." );

		CRET( parts.empty(), TOutStorage{} );

		using ValidStringView	= Internal::StringView<typename TPartStorage::value_type>;
		using ValidPatternView	= Internal::PatternView<TPattern>;

		auto generate = [current_part = parts.begin(), parts_end = parts.end()]() mutable -> ValidStringView
		{
			EXPECTS_DEBUG( current_part != parts_end );
			return ValidStringView{ *current_part++ };
		};

		return Internal::JoinString<TOutStorage>( generate, parts.size(), ValidPatternView{ pattern }, flags );
	}
}
