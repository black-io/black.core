#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
	template< typename TValue >
	inline void CopyMemory( TValue& dest_ref, const TValue& source_ref )
	{
		Platform::CopyMemory<Black::BUILD_PLATFORM>( &dest_ref, &source_ref, sizeof( TValue ) );
	}

	inline void CopyMemory( void* dest_memory, const void* source_memory, const size_t length )
	{
		Platform::CopyMemory<Black::BUILD_PLATFORM>( dest_memory, source_memory, length );
	}

	template< typename TValue >
	inline void FillMemory( TValue& target_ref, const int32_t pattern )
	{
		Platform::FillMemory<Black::BUILD_PLATFORM>( &target_ref, pattern, sizeof( TValue ) );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline void FillMemory( TValue (&target_array)[ ARRAY_LENGTH ], const int32_t pattern )
	{
		Platform::FillMemory<Black::BUILD_PLATFORM>( target_array, pattern, sizeof( TValue ) * ARRAY_LENGTH );
	}

	inline void FillMemory( void* memory, const int32_t pattern, const size_t length )
	{
		Platform::FillMemory<Black::BUILD_PLATFORM>( memory, pattern, length );
	}

	template< typename TValue >
	inline void ZeroMemory( TValue& target_ref )
	{
		Platform::ZeroMemory<Black::BUILD_PLATFORM>( &target_ref, sizeof( TValue ) );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline void ZeroMemory( TValue (&target_array)[ ARRAY_LENGTH ] )
	{
		Platform::ZeroMemory<Black::BUILD_PLATFORM>( target_array, sizeof( TValue ) * ARRAY_LENGTH );
	}

	inline void ZeroMemory( void* memory, const size_t length )
	{
		Platform::ZeroMemory<Black::BUILD_PLATFORM>( memory, length );
	}

	template< typename TValue >
	inline void SecuredZeroMemory( TValue& target_ref )
	{
		Platform::SecuredZeroMemory<Black::BUILD_PLATFORM>( &target_ref, sizeof( TValue ) );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline void SecuredZeroMemory( TValue (&target_array)[ ARRAY_LENGTH ] )
	{
		Platform::SecuredZeroMemory<Black::BUILD_PLATFORM>( target_array, sizeof( TValue ) * ARRAY_LENGTH );
	}

	inline void SecuredZeroMemory( void* memory, const size_t length )
	{
		Platform::SecuredZeroMemory<Black::BUILD_PLATFORM>( memory, length );
	}

	template< typename TValue >
	inline const bool IsMemoryEqual( const TValue& left_ref, const TValue& right_ref )
	{
		return Platform::IsMemoryEqual<Black::BUILD_PLATFORM>( &left_ref, &right_ref, sizeof( TValue ) );
	}

	inline const bool IsMemoryEqual( const void* left_memory, const void* right_memory, const size_t length )
	{
		return Platform::IsMemoryEqual<Black::BUILD_PLATFORM>( left_memory, right_memory, length );
	}

	inline std::string_view FormatArguments( Black::PlainView<char> target_buffer, const char* format, ... )
	{
		va_list arguments;
		va_start( arguments, format );

		std::string_view result{ Platform::FormatArgumentsList<Black::BUILD_PLATFORM>( target_buffer, format, arguments ) };

		va_end( arguments );
		return result;
	}

	inline std::string_view FormatArgumentsList( Black::PlainView<char> target_buffer, const char* format, va_list arguments )
	{
		return Platform::FormatArgumentsList<Black::BUILD_PLATFORM>( target_buffer, format, arguments );
	}

	inline const size_t ParseArguments( const std::string_view source_buffer, const char* format, ... )
	{
		va_list arguments;
		va_start( arguments, format );

		const size_t result = Platform::ParseArgumentsList<Black::BUILD_PLATFORM>( source_buffer, format, arguments );

		va_end( arguments );
		return result;
	}

	inline const size_t ParseArgumentsList( const std::string_view source_buffer, const char* format, va_list arguments )
	{
		return Platform::ParseArgumentsList<Black::BUILD_PLATFORM>( source_buffer, format, arguments );
	}

	inline void SendDebugString( std::string_view content )
	{
		Platform::SendDebugString<Black::BUILD_PLATFORM>( content );
	}

	inline void SendDebuggerMessage( const Black::LogMessage& message, std::string&& content )
	{
		Platform::SendDebuggerMessage<Black::BUILD_PLATFORM>( message, std::move( content ) );
	}
}
}
}
