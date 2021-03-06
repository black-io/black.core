#include <black/core.h>


namespace Black
{
inline namespace Core
{
inline namespace Platform
{
inline namespace PlatformSpecific
{
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
