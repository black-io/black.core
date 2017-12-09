#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	/**
		@brief	Compile-time string implementation.
		Static (at compile-time) string is an regular type, which may be used to get the regular string literal for runtime purposes.
		Also, the proper string utils may be used to combine or comparing the CT-strings.
	*/
	template< char... CHARS >
	struct StaticString final
	{
		// Get the length of string.
		constexpr static const size_t GetLength()
		{
			return sizeof...( CHARS );
		}

		// Get the regular string.
		inline static const char* const GetData()
		{
			constexpr static const char data[] = { CHARS..., 0 };
			return data;
		}

		// Get the char at given index. Return `0` for any invalid index.
		inline static const char GetChar( const size_t index )
		{
			return ( index < GetLength() )? GetData()[ index ] : 0;
		}
	};
}
}
}
