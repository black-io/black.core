#pragma once


#include <windows.h>

// Release worthless macros

#if( defined( GetCurrentTime ) )
	#undef GetCurrentTime
#endif

#if( defined( min ) )
	#undef min
#endif

#if( defined( max ) )
	#undef max
#endif

#if( defined( CopyMemory ) )
	#undef CopyMemory
#endif

#if( defined( FillMemory ) )
	#undef FillMemory
#endif

#if( defined( MoveMemory ) )
	#undef MoveMemory
#endif

#if( defined( ZeroMemory ) )
	#undef ZeroMemory
#endif

#if( defined( ERROR ) )
	#undef ERROR
#endif

#if( defined( CopyFile ) )
	#undef CopyFile
#endif

#if( defined( MoveFile ) )
	#undef MoveFile
#endif

#if( defined( DeleteFile ) )
	#undef DeleteFile
#endif

#if( defined( AddMonitor ) )
	#undef AddMonitor
#endif


namespace Black
{
inline namespace Core
{
inline namespace Platform
{
inline namespace WindowsDesktop
{
namespace Internal
{

}
}
}
}
}
