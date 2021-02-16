#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Platform
{
inline namespace PlatformSpecific
{
	/**
		@brief	Send the string to debugger.

		The function works only in Debug mode and can be used to write some text into debugger log.
		The `content` data will be represented as single line text.

		@param	content	The string to be shown in debugger.
	*/
	void SendDebugString( std::string_view content );
}
}
}
}
