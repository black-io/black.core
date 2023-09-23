#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Platform
{
inline namespace PlatformSpecific
{
	/**
		@brief	Format the `arguments` into `target_buffer` according to `format` specification.
		May cause potentially unsafe behavior if invalid arguments passed.
		@param	target_buffer	Memory buffer for formatted string.
		@param	format			Specification to format the arguments.
		@param	arguments		List of arguments to format.
		@return					Formatted string view with same memory as `target_buffer`.
		@retval	empty view		In case the arguments can not be formated into target buffer.
	*/
	std::string_view FormatArgumentsList( Black::PlainView<char> target_buffer, const char* format, va_list arguments );

	/**
		@brief	Read the `arguments` from `source_buffer` according to `format` specification.
		May cause potentially unsafe behavior if invalid arguments passed.
		@param	source_buffer	Memory buffer to be readden.
		@param	format			Arguments reading specification.
		@param	arguments		List of arguments.
		@return					Number of readden arguments.
		@retval	0				If no argument was read.
	*/
	const size_t ParseArgumentsList( const std::string_view source_buffer, const char* format, va_list arguments );
}
}
}
}
}
