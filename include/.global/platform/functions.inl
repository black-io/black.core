#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Platform
{
	template< typename TValue >
	inline void CopyMemory( TValue& dest_ref, const TValue& source_ref )
	{
		Black::CopyMemory( &dest_ref, &source_ref, sizeof( TValue ) );
	}

	template< typename TValue >
	inline void FillMemory( TValue& target_ref, const int32_t pattern )
	{
		Black::FillMemory( &target_ref, pattern, sizeof( TValue ) );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline void FillMemory( TValue (&target_array)[ ARRAY_LENGTH ], const int32_t pattern )
	{
		Black::FillMemory( target_array, pattern, sizeof( TValue ) * ARRAY_LENGTH );
	}

	template< typename TValue >
	inline void ZeroMemory( TValue& target_ref )
	{
		Black::ZeroMemory( &target_ref, sizeof( TValue ) );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline void ZeroMemory( TValue (&target_array)[ ARRAY_LENGTH ] )
	{
		Black::ZeroMemory( target_array, sizeof( TValue ) * ARRAY_LENGTH );
	}

	template< typename TValue >
	inline void SecuredZeroMemory( TValue& target_ref )
	{
		Black::SecuredZeroMemory( &target_ref, sizeof( TValue ) );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline void SecuredZeroMemory( TValue (&target_array)[ ARRAY_LENGTH ] )
	{
		Black::SecuredZeroMemory( target_array, sizeof( TValue ) * ARRAY_LENGTH );
	}

	template< typename TValue >
	inline const bool IsMemoryEqual( const TValue& left_ref, const TValue& right_ref )
	{
		return Black::IsMemoryEqual( &left_ref, &right_ref, sizeof( TValue ) );
	}

	inline std::string_view FormatArguments( Black::PlainView<char> target_buffer, const char* format, ... )
	{
		va_list arguments;
		va_start( arguments, format );

		std::string_view result = Black::FormatArgumentsList( target_buffer, format, arguments );

		va_end( arguments );
		return result;
	}

	inline const size_t ParseArguments( const std::string_view source_buffer, const char* format, ... )
	{
		va_list arguments;
		va_start( arguments, format );

		const size_t result = Black::ParseArgumentsList( source_buffer, format, arguments );

		va_end( arguments );
		return result;
	}
}
}
}
}
