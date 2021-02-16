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
			char* const string_buffer	= static_cast<char*>( alloca( content_length + 1 ) );

			CopyMemory( string_buffer, content.data(), content_length );
			string_buffer[ content_length ] = 0;

			__android_log_write( ANDROID_LOG_DEBUG, "Black/Debugging", string_buffer );
		}
	}
}
}
}
}
