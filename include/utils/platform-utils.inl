#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Utils
{
	template< typename TValueType >
	inline void CopyMemory( TValueType& dest_ref, const TValueType& source_ref )
	{
		CopyMemory( &dest_ref, &source_ref, sizeof( TValueType ) );
	}

	template< typename TValueType >
	inline void FillMemory( TValueType& target_ref, const int32_t pattern )
	{
		FillMemory( &target_ref, pattern, sizeof( TValueType ) );
	}

	template< typename TValueType, size_t ARRAY_LENGTH >
	inline void FillMemory( TValueType (&target_array)[ ARRAY_LENGTH ], const int32_t pattern )
	{
		FillMemory( target_array, pattern, sizeof( TValueType ) * ARRAY_LENGTH );
	}

	template< typename TValueType >
	inline void ZeroMemory( TValueType& target_ref )
	{
		FillMemory( &target_ref, 0, sizeof( TValueType ) );
	}

	template< typename TValueType, size_t ARRAY_LENGTH >
	inline void ZeroMemory( TValueType (&target_array)[ ARRAY_LENGTH ] )
	{
		FillMemory( target_array, 0, sizeof( TValueType ) * ARRAY_LENGTH );
	}

	template< typename TValueType >
	inline void SequredZeroMemory( TValueType& target_ref )
	{
		SequredZeroMemory( &target_ref, sizeof( TValueType ) );
	}

	template< typename TValueType, size_t ARRAY_LENGTH >
	inline void SequredZeroMemory( TValueType (&target_array)[ ARRAY_LENGTH ] )
	{
		SequredZeroMemory( target_array, sizeof( TValueType ) * ARRAY_LENGTH );
	}

	template< typename TValueType >
	inline const bool IsMemoryEqual( const TValueType& left_ref, const TValueType& right_ref )
	{
		return IsMemoryEqual( &left_ref, right_ref, sizeof( TValueType ) );
	}
}


inline namespace TextUtils
{
	inline Black::StringView WriteArguments( Black::PlainView<char> target_buffer, const Black::StringView format, ... )
	{
		va_list arguments;
		va_start( arguments, format );

		Black::StringView result = WriteArguments( target_buffer, format, arguments );

		va_end( arguments );
		return result;
	}

	inline const size_t ReadArguments( const Black::StringView source_buffer, const Black::StringView format, ... )
	{
		va_list arguments;
		va_start( arguments, format );

		const size_t result = ReadArguments( source_buffer, format, arguments );

		va_end( arguments );
		return result;
	}
}
}
}
