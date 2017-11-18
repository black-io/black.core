#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Utils
{
inline namespace PlatformSpecific
{
	/**
		@brief	Copies memory from source pointer to destination pointer.
		May cause potentially unsafe behavior if invalid arguments passed.
		@param	source_memory	Pointer to source memory with `bytes_to_copy` bytes length or higher.
		@aram	dest_memory		Pointer to destination memory with `bytes_to_copy` bytes length or higher.
		@param	length			Number of bytes to be copied.
	*/
	void CopyMemory( const void* source_memory, void* dest_memory, const size_t length );

	/**
		@brief	Fill every byte of `memory` with `pattern`.
		May cause potentially unsafe behavior if invalid arguments passed.
		@param	memory	Head of memory to be filled.
		@param	pattern	Filling pattern.
		@param	length	Number of bytes in `memory` to be filled.
	*/
	void FillMemory( void* memory, const int32_t pattern, const size_t length );

	/**
		@brief	Fill every byte of `memory` with `pattern`.
		May cause potentially unsafe behavior if invalid arguments passed.
		@note	This function is same as `FillMemory`, but it may not be dropped while compiler optimizations.
		@param	memory	Head of memory to be filled.
		@param	pattern	Filling pattern.
		@param	length	Number of bytes in `memory` to be filled.
	*/
	void SequredFillMemory( void* memory, const int32_t pattern, const size_t length );

	/**
		@brief	Compare the two memory blocks checking its identity.
		May cause potentially unsafe behavior if invalid arguments passed.
		@param	left_memory		Memory head to compare.
		@param	right_memory	Memory head to compare.
		@param	length			The length in bytes to compare.
		@return					The value returned is flag that the left and right memory streams are equal.
	*/
	const bool IsMemoryEqual( const void* left_memory, const void* right_memory, const size_t length );
}
}

inline namespace TextUtils
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
	StringView WriteArguments( StringView target_buffer, const StringView format, va_list arguments );

	/**
		@brief	Read the `arguments` from `source_buffer` according to `format` specification.
		May cause potentially unsafe behavior if invalid arguments passed.
		@param	source_buffer	Memory buffer to be readen.
		@param	format			Arguments reading specification.
		@param	arguments		List of arguments.
		@return					Number of readen arguments.
		@retval	0				If no argument was read.
	*/
	const size_t ReadArguments( const StringView soure_buffer, const StringView format, va_list arguments );
}
}
}
}
