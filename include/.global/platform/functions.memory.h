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
		@brief	Copies memory from source pointer to destination pointer.

		May cause potentially unsafe behavior if invalid arguments passed.

		@note	The implementation is platform-specific.

		@param	source_memory	Pointer to source memory with `bytes_to_copy` bytes length or higher.
		@aram	dest_memory		Pointer to destination memory with `bytes_to_copy` bytes length or higher.
		@param	length			Number of bytes to be copied.
	*/
	template< Black::PlatformType PLATFORM_TYPE >
	void CopyMemory( void* dest_memory, const void* source_memory, const size_t length );

	/**
		@brief	Fill every byte of `memory` with `pattern`.

		May cause potentially unsafe behavior if invalid arguments passed.

		@note	The implementation is platform-specific.

		@param	memory	Head of memory to be filled.
		@param	pattern	Filling pattern.
		@param	length	Number of bytes in `memory` to be filled.
	*/
	template< Black::PlatformType PLATFORM_TYPE >
	void FillMemory( void* memory, const int32_t pattern, const size_t length );

	/**
		@brief	Fill every byte of `memory` with zero value.

		May cause potentially unsafe behavior if invalid arguments passed.

		@note	The implementation is platform-specific.

		@param	memory	Head of memory to be filled.
		@param	length	Number of bytes in `memory` to be filled.
	*/
	template< Black::PlatformType PLATFORM_TYPE >
	void ZeroMemory( void* memory, const size_t length );

	/**
		@brief	Fill every byte of `memory` with zero value.

		May cause potentially unsafe behavior if invalid arguments passed.

		@note	The implementation is platform-specific.

		@note	This function is same as `ZeroMemory`, but it may not be dropped while compiler optimizations.
		@param	memory	Head of memory to be filled.
		@param	length	Number of bytes in `memory` to be filled.
	*/
	template< Black::PlatformType PLATFORM_TYPE >
	void SecuredZeroMemory( void* memory, const size_t length );

	/**
		@brief	Compare the two memory blocks checking its identity.

		May cause potentially unsafe behavior if invalid arguments passed.

		@note	The implementation is platform-specific.

		@param	left_memory		Memory head to compare.
		@param	right_memory	Memory head to compare.
		@param	length			The length in bytes to compare.
		@return					The value returned is flag that the left and right memory streams is equal.
	*/
	template< Black::PlatformType PLATFORM_TYPE >
	const bool IsMemoryEqual( const void* left_memory, const void* right_memory, const size_t length );
}
}
}
}
