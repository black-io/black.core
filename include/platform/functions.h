#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Platform
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
		@brief	Compare the memory of two object checking its identity.
		May cause potentially unsafe behavior if invalid arguments passed.
		@param	left_ref	Left-sided object to check.
		@param	right_ref	Right-sided object to check.
		@return				The value returned is flag that the memory of left and right objects is equal.
	*/
	template< typename TValue >
	inline const bool IsMemoryEqual( const TValue& left_ref, const TValue& right_ref );

	/**
		@brief	Format the variable arguments into `target_buffer` according to `format` specification.
		May cause potentially unsafe behavior if invalid arguments passed.
		@param	target_buffer	Memory buffer for formatted string.
		@param	format			Specification to format the arguments.
		@param	...				List of arguments to format.
		@return					Formatted string view with same memory as `target_buffer`.
		@retval	empty view		In case the arguments can not be formated into target buffer.
	*/
	inline std::string_view WriteArguments( Black::PlainView<char> target_buffer, const std::string& format, ... );

	/**
		@brief	Read the variable arguments from `source_buffer` according to `format` specification.
		May cause potentially unsafe behavior if invalid arguments passed.
		@param	source_buffer	Memory buffer to be readden.
		@param	format			Arguments reading specification.
		@param	...				List of arguments.
		@return					Number of readden arguments.
		@retval	0				If no argument was read.
	*/
	inline const size_t ReadArguments( const std::string_view source_buffer, const std::string& format, ... );
}
}
}
