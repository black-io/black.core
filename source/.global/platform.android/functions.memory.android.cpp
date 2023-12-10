#include <black/core.h>


namespace Black
{
inline namespace Core
{
inline namespace Global
{
namespace Platform
{
	template<>
	void CopyMemory<Black::PlatformType::Android>( void* dest_memory, const void* source_memory, const size_t length )
	{
		::memcpy( dest_memory, source_memory, length );
	}

	template<>
	void FillMemory<Black::PlatformType::Android>( void* memory, const int32_t pattern, const size_t length )
	{
		::memset( memory, pattern, length );
	}

	template<>
	void ZeroMemory<Black::PlatformType::Android>( void* memory, const size_t length )
	{
		::memset( memory, 0, length );
	}

	template<>
	void SecuredZeroMemory<Black::PlatformType::Android>( void* memory, const size_t length )
	{
		::memset( memory, 0, length );
		asm volatile( "" : : "g"( memory ), "g"( length ) );
	}

	template<>
	const bool IsMemoryEqual<Black::PlatformType::Android>( const void* left_memory, const void* right_memory, const size_t length )
	{
		return ::memcmp( left_memory, right_memory, length ) == 0;
	}
}
}
}
}
