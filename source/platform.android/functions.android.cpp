#include <black.core.h>


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

	void SecuredZeroMemory( void* memory, const size_t length )
	{
		::memset( memory, 0, length );
		asm volatile( "" : : "g"( memory ), "g"( length ) );
	}

	const bool IsMemoryEqual( const void* left_memory, const void* right_memory, const size_t length )
	{
		return ::memcmp( left_memory, right_memory, length ) == 0;
	}

	Black::StringView WriteArguments( Black::PlainView<char> target_buffer, const Black::StringView format, va_list arguments )
	{
		const int32_t status = ::vsnprintf( target_buffer.GetData(), target_buffer.GetLength(), format.data(), arguments );
		CRET( status <= 0, {} );

		return { target_buffer.GetData(), static_cast<size_t>( status ) };
	}

	const size_t ReadArguments( const Black::StringView source_buffer, const Black::StringView format, va_list arguments )
	{
		return std::max<int32_t>( ::vsscanf( source_buffer.data(), format.data(), arguments ), 0 );
	}
}
}
}
}
