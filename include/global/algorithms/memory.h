#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Algorithms
{
	/**
		@brief	Wrap for `delete` operator.
		Calls `delete` for `scalar_pointer`. After memory deleted, `nullptr` will be set to `scalar_pointer`.
		@param	scalar_pointer	Pointer, who's memory needs to be deleted.
	*/
	template< typename TValueType >
	constexpr void SafeScalarDelete( TValueType* (&scalar_pointer) )
	{
		delete scalar_pointer;
		scalar_pointer = nullptr;
	}

	/**
		@brief	Wrap for `delete[]` operator.
		Calls `delete[]` for `vector_pointer` considering its memory contains vector of objects.
		After memory deleted, `nullptr` will be set to `vector_pointer`.
		@param	vector_pointer	Pointer, who's memory needs to be deleted.
	*/
	template< typename TValueType >
	constexpr void SafeVectorDelete( TValueType* (&vector_pointer) )
	{
		delete[] vector_pointer;
		vector_pointer = nullptr;
	}

	/**
		@brief		Get the aligned size.
		@warning	This function never checks `size` or `align`. All checks must be done before call.
		@param	size	The size to align.
		@param	align	The alignment.
		@return			The value returned is an aligned `size`, which will be greater or equal to original `size`.
	*/
	constexpr const size_t GetAlignedSize( const size_t size, const size_t align )
	{
		return ( size + ( align - 1 ) ) & ~( align - 1 );
	}

	/**
		@brief		Get the aligned pointer.
		@warning	This function never checks `pointer` or `align`. All checks must be done before call.
		@tparam	TPointerType	The type of given and returned pointer.
		@param	pointer			The pointer to align.
		@param	align			The alignment in bytes.
		@return					The value returned is an aligned `pointer`, which will be greater or equal to original `pointer`.
	*/
	template< typename TPointer >
	inline TPointer* GetAlignedPointer( TPointer* pointer, const size_t align )
	{
		return reinterpret_cast<TPointer*>( ( reinterpret_cast<std::uintptr_t>( pointer ) + ( align - 1 ) ) & ~( align - 1 ) );
	}
}
}
}
}
