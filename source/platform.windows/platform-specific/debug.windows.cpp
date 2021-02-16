#include <black/core.h>


namespace Black
{
inline namespace Core
{
inline namespace Platform
{
inline namespace PlatformSpecific
{
	void SendDebugString( std::string_view content )
	{
		if constexpr( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
		{
			const size_t content_length = content.size();
			char* const string_buffer	= static_cast<char*>( _malloca( content_length + 2 ) );
			CRET( string_buffer == nullptr );

			auto buffer_cleaner = Black::ScopeLeaveHandler{ [string_buffer]() { _freea( string_buffer ); } };

			CopyMemory( string_buffer, content.data(), content_length );
			string_buffer[ content_length ]		= '\n';
			string_buffer[ content_length + 1 ]	= 0;

			OutputDebugStringA( string_buffer );
		}
	}
}
}
}
}
