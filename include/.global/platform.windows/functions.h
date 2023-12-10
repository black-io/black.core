#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace WindowsDesktop
{
	// Whether the handle is considered valid.
	inline const bool IsHandleValid( ::HANDLE handle )
	{
		return ( handle != 0 ) && ( handle != INVALID_HANDLE_VALUE );
	}
}
}
}
}
