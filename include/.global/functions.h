#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
	/**
		@brief	Copies memory from source to destination.

		Affects directly to memory, calls no constructors!

		@aram	dest_ref	Reference to destination object.
		@param	source_ref	Reference to source object.
		@tparam	TValue		Type of given objects. Helps determinate size of memory to copy.
	*/
	template< typename TValue >
	inline void CopyMemory( TValue& dest_ref, const TValue& source_ref );

	/**
		@brief	Copies memory from source pointer to destination pointer.

		May cause potentially unsafe behavior if invalid arguments passed.

		@note	The implementation is platform-specific.

		@param	source_memory	Pointer to source memory with `bytes_to_copy` bytes length or higher.
		@aram	dest_memory		Pointer to destination memory with `bytes_to_copy` bytes length or higher.
		@param	length			Number of bytes to be copied.
	*/
	inline void CopyMemory( void* dest_memory, const void* source_memory, const size_t length );

	/**
		@brief	Fills every byte of `target_ref` with `pattern` byte.

		Affects directly to memory, calls no destructor!

		@param	target_ref	Reference to object, which memory will be filed.
		@param	pattern		Value the memory will be filled with. Note, only first byte of value will be used.
		@tparam	TValue		Type of passed object. Helps determinate size of memory to fill.
	*/
	template< typename TValue >
	inline void FillMemory( TValue& target_ref, const int32_t pattern );

	/**
		@brief	Fills every byte of `target_array` array with `pattern` byte.

		Affects directly to memory, calls no destructor!

		@param	target_array	Reference to array of objects, which memory will be filed.
		@param	pattern			Value the memory will be filled with. Note, only first byte of value will be used.
		@tparam	TValue			Type of passed object. Helps determinate size of memory to fill.
		@tparam	ARRAY_LENGTH	Number of elements in array.
	*/
	template< typename TValue, size_t ARRAY_LENGTH >
	inline void FillMemory( TValue (&target_array)[ ARRAY_LENGTH ], const int32_t pattern );

	/**
		@brief	Fill every byte of `memory` with `pattern`.

		May cause potentially unsafe behavior if invalid arguments passed.

		@note	The implementation is platform-specific.

		@param	memory	Head of memory to be filled.
		@param	pattern	Filling pattern.
		@param	length	Number of bytes in `memory` to be filled.
	*/
	inline void FillMemory( void* memory, const int32_t pattern, const size_t length );

	/**
		@brief	Fills every byte of `target_ref` with zero.

		Affects directly to memory, calls no destructor!

		@param	target_ref	Reference to object, which memory will be filed.
		@tparam	TValue		Type of passed object. Helps determinate size of memory to fill.
	*/
	template< typename TValue >
	inline void ZeroMemory( TValue& target_ref );

	/**
		@brief	Fills every byte of `target_array` array with zero.

		Affects directly to memory, calls no destructor!

		@param	target_array	Reference to array of objects, which memory will be filed.
		@tparam	TValue			Type of passed object. Helps determinate size of memory to fill.
		@tparam	ARRAY_LENGTH	Number of elements in array.
	*/
	template< typename TValue, size_t ARRAY_LENGTH >
	inline void ZeroMemory( TValue (&target_array)[ ARRAY_LENGTH ] );

	/**
		@brief	Fill every byte of `memory` with zero value.

		May cause potentially unsafe behavior if invalid arguments passed.

		@note	The implementation is platform-specific.

		@param	memory	Head of memory to be filled.
		@param	length	Number of bytes in `memory` to be filled.
	*/
	inline void ZeroMemory( void* memory, const size_t length );

	/**
		@brief	Fills every byte of `target_ref` with zero.

		Affects directly to memory, calls no destructor!

		@note	This function is same as `FillMemory`, but it may not be dropped while compiler optimizations.
		@param	target_ref	Reference to object, which memory will be filed.
		@tparam	TValue		Type of passed object. Helps determinate size of memory to fill.
	*/
	template< typename TValue >
	inline void SecuredZeroMemory( TValue& target_ref );

	/**
		@brief	Fills every byte of `target_array` array with zero.

		Affects directly to memory, calls no destructor!

		@param	target_array	Reference to array of objects, which memory will be filed.
		@tparam	TValue			Type of passed object. Helps determinate size of memory to fill.
		@tparam	ARRAY_LENGTH	Number of elements in array.
	*/
	template< typename TValue, size_t ARRAY_LENGTH >
	inline void SecuredZeroMemory( TValue (&target_array)[ ARRAY_LENGTH ] );

	/**
		@brief	Fill every byte of `memory` with zero value.

		May cause potentially unsafe behavior if invalid arguments passed.

		@note	The implementation is platform-specific.

		@note	This function is same as `ZeroMemory`, but it may not be dropped while compiler optimizations.
		@param	memory	Head of memory to be filled.
		@param	length	Number of bytes in `memory` to be filled.
	*/
	inline void SecuredZeroMemory( void* memory, const size_t length );

	/**
		@brief	Compare the memory of two object checking its identity.

		May cause potentially unsafe behavior if invalid arguments passed.

		@param	left_ref	Left-sided object to check.
		@param	right_ref	Right-sided object to check.
		@return				The value returned is flag that the memory of left and right objects is equal.
	*/
	template< typename TValue >
	inline const bool IsMemoryEqual( const TValue& left_ref, const TValue& right_ref );

	/**
		@brief	Compare the two memory blocks checking its identity.

		May cause potentially unsafe behavior if invalid arguments passed.

		@note	The implementation is platform-specific.

		@param	left_memory		Memory head to compare.
		@param	right_memory	Memory head to compare.
		@param	length			The length in bytes to compare.
		@return					The value returned is flag that the left and right memory streams is equal.
	*/
	inline const bool IsMemoryEqual( const void* left_memory, const void* right_memory, const size_t length );

	/**
		@brief	Format the variable arguments into `target_buffer` according to `format` specification.

		May cause potentially unsafe behavior if invalid arguments passed.

		@param	target_buffer	Memory buffer for formatted string.
		@param	format			Specification to format the arguments.
		@param	...				List of arguments to format.
		@return					Formatted string view with same memory as `target_buffer`.
		@retval	empty view		In case the arguments can not be formated into target buffer.
	*/
	inline std::string_view FormatArguments( Black::PlainView<char> target_buffer, const char* format, ... );

	/**
		@brief	Format the `arguments` into `target_buffer` according to `format` specification.

		May cause potentially unsafe behavior if invalid arguments passed.

		@note	The implementation is platform-specific.

		@param	target_buffer	Memory buffer for formatted string.
		@param	format			Specification to format the arguments.
		@param	arguments		List of arguments to format.
		@return					Formatted string view with same memory as `target_buffer`.
		@retval	empty view		In case the arguments can not be formated into target buffer.
	*/
	inline std::string_view FormatArgumentsList( Black::PlainView<char> target_buffer, const char* format, va_list arguments );

	/**
		@brief	Read the variable arguments from `source_buffer` according to `format` specification.

		May cause potentially unsafe behavior if invalid arguments passed.

		@param	source_buffer	Memory buffer to be readden.
		@param	format			Arguments reading specification.
		@param	...				List of arguments.
		@return					Number of readden arguments.
		@retval	0				If no argument was read.
	*/
	inline const size_t ParseArguments( const std::string_view source_buffer, const char* format, ... );

	/**
		@brief	Read the `arguments` from `source_buffer` according to `format` specification.

		May cause potentially unsafe behavior if invalid arguments passed.

		@note	The implementation is platform-specific.

		@param	source_buffer	Memory buffer to be readden.
		@param	format			Arguments reading specification.
		@param	arguments		List of arguments.
		@return					Number of readden arguments.
		@retval	0				If no argument was read.
	*/
	inline const size_t ParseArgumentsList( const std::string_view source_buffer, const char* format, va_list arguments );

	/**
		@brief	Send the string to debugger.

		The function works only in Debug mode and can be used to write some text into debugger log.
		The `content` data will be represented as single line text.

		@note	The implementation is platform-specific.

		@param	content	The string to be shown in debugger.
	*/
	inline void SendDebugString( std::string_view content );

	/**
		@brief	Send the logging message to debugger.

		The function works only in Debug mode and can be used to write some text into debugger log.
		The `content` data will be represented as single line text.
		Also shown content will be extended with logging message information.

		@note	The implementation is platform-specific.

		@param	message	The logging message to send.
		@param	content	The string to be shown in debugger.
	*/
	inline void SendDebuggerMessage( const Black::LogMessage& message, std::string&& content );
}
}
}
