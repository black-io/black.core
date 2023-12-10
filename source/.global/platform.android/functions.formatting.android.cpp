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
	std::string_view FormatArgumentsList<Black::PlatformType::Android>( Black::PlainView<char> target_buffer, const char* format, va_list arguments )
	{
		const int32_t status = ::vsnprintf( target_buffer.data(), target_buffer.GetLength(), format, arguments );
		CRET( status <= 0, {} );

		return { target_buffer.data(), static_cast<size_t>( status ) };
	}

	template<>
	const size_t ParseArgumentsList<Black::PlatformType::Android>( const std::string_view source_buffer, const char* format, va_list arguments )
	{
		return std::max<int32_t>( ::vsscanf( source_buffer.data(), format, arguments ), 0 );
	}
}
}
}
}
