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
	void CopyMemory<Black::PlatformType::WindowsDesktop>( void* dest_memory, const void* source_memory, const size_t length )
	{
		::memcpy_s( dest_memory, length, source_memory, length );
	}

	template<>
	void FillMemory<Black::PlatformType::WindowsDesktop>( void* memory, const int32_t pattern, const size_t length )
	{
		::memset( memory, pattern, length );
	}

	template<>
	void ZeroMemory<Black::PlatformType::WindowsDesktop>( void* memory, const size_t length )
	{
		::RtlZeroMemory( memory, length );
	}

	template<>
	void SecuredZeroMemory<Black::PlatformType::WindowsDesktop>( void* memory, const size_t length )
	{
		::RtlSecureZeroMemory( memory, length );
	}

	template<>
	const bool IsMemoryEqual<Black::PlatformType::WindowsDesktop>( const void* left_memory, const void* right_memory, const size_t length )
	{
		return ::memcmp( left_memory, right_memory, length ) == 0;
	}
}
}
}
}
