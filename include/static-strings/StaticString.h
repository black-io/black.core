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
		static constexpr const size_t GetLength()
		{
			return sizeof...( CHARS );
		}

		// Check that the string is empty.
		static constexpr const bool IsEmpty()
		{
			return GetLength() == 0;
		}

		// Get the regular string.
		static inline const char* const GetData()
		{
			static constexpr const char data[] = { CHARS..., 0 };
			return data;
		}

		// Get the char at given index. Return `0` for any invalid index.
		static inline const char GetChar( const size_t index )
		{
			return ( index < GetLength() )? GetData()[ index ] : 0;
		}
	};
}
}
}
