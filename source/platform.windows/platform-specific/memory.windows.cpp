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
		::memcpy_s( dest_memory, length, source_memory, length );
	}

	void FillMemory( void* memory, const int32_t pattern, const size_t length )
	{
		::memset( memory, pattern, length );
	}

	void ZeroMemory( void* memory, const size_t length )
	{
		::RtlZeroMemory( memory, length );
	}

	void SecuredZeroMemory( void* memory, const size_t length )
	{
		::RtlSecureZeroMemory( memory, length );
	}

	const bool IsMemoryEqual( const void* left_memory, const void* right_memory, const size_t length )
	{
		return ::memcmp( left_memory, right_memory, length ) == 0;
	}
}
}
}
}
