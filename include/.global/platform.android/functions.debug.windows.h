#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
namespace Platform
{
	/**
		@brief	Send the string to debugger in terms of Windows desktop platform.

		The function works only in Debug mode and can be used to write some text into debugger log.
		The `content` data will be represented as single line text.

		@note	The implementation is platform-specific.

		@param	content	The string to be shown in debugger.
	*/
	template<>
	void SendDebugString<Black::PlatformType::WindowsDesktop>( std::string_view content );

	/**
		@brief	Send the logging message to debugger in terms of Windows desktop platform.

		The function works only in Debug mode and can be used to write some text into debugger log.
		The `content` data will be represented as single line text.
		Also shown content will be extended with logging message information.

		@note	The implementation is platform-specific.

		@param	message	The logging message to send.
		@param	content	The string to be shown in debugger.
	*/
	template<>
	void SendDebuggerMessage<Black::PlatformType::WindowsDesktop>( const Black::LogMessage& message, std::string&& content );
}
}
}
}
