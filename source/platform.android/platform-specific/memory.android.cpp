#include <black/core.h>


namespace Black
{
inline namespace Core
{
inline namespace Platform
{
inline namespace PlatformSpecific
{
	void CopyMemory( void* dest_memory, const void* source_memory, const size_t length )
	{
		::memcpy( dest_memory, source_memory, length );
	}

	void FillMemory( void* memory, const int32_t pattern, const size_t length )
	{
		::memset( memory, pattern, length );
	}

	void ZeroMemory( void* memory, const size_t length )
	{
		::memset( memory, 0, length );
	}

	void SecuredZeroMemory( void* memory, const size_t length )
	{
		::memset( memory, 0, length );
		asm volatile( "" : : "g"( memory ), "g"( length ) );
	}

	const bool IsMemoryEqual( const void* left_memory, const void* right_memory, const size_t length )
	{
		return ::memcmp( left_memory, right_memory, length ) == 0;
	}

	std::string_view FormatArgumentsList( Black::PlainView<char> target_buffer, const char* format, va_list arguments )
	{
		const int32_t status = ::vsnprintf( target_buffer.GetData(), target_buffer.GetLength(), format, arguments );
		CRET( status <= 0, {} );

		return { target_buffer.GetData(), static_cast<size_t>( status ) };
	}

	const size_t ParseArgumentsList( const std::string_view source_buffer, const char* format, va_list arguments )
	{
		return std::max<int32_t>( ::vsscanf( source_buffer.data(), format, arguments ), 0 );
	}
}
}
}
}
