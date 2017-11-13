#pragma once


namespace Black
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
	template< typename TPointerType >
	inline TPointerType* GetAlignedPointer( TPointerType* pointer, const size_t align )
	{
		return reinterpret_cast<TPointerType*>( ( reinterpret_cast<std::uintptr_t>( pointer ) + ( align - 1 ) ) & ~( align - 1 ) );
	}

	/**
		@brief	Converts value of enumeration type to its underlying type value.
		@param	value			Te value to be converted.
		@tparam	TEnumeration	Type of enumeration.
		@return					Returns value of `TEnumeration` underlying type.
	*/
	template< typename TEnumeration >
	inline const auto GetEnumValue( const TEnumeration& value )
	{
		static_assert( IS_ENUMERATION<TEnumeration>, "`TEnumeration` template argument should be an enumeration." );
		return static_cast< const UnderlyingType<TEnumeration> >( value );
	}

	/**
		@brief	Packs 4 bytes into single 4-byte value.
		The value returned will be formed in endianness given through the template argument `ENDIANNESS`.
		@tparam	ENDIANNESS	The requested endianness.
		@return				Returns endian-dependent 4-byte unsigned integer value.
	*/
	template< PlatformEndianness ENDIANNESS = BUILD_ENDIANNESS >
	constexpr uint32_t GetPackedBytes( const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4 );

	/**
		@brief	Packs 4 bytes into single 4-byte value.
		The value returned will be formed in endianness given through the template argument `ENDIANNESS`.
		@tparam	ENDIANNESS	The requested endianness.
		@return				Returns endian-dependent 4-byte unsigned integer value.
	*/
	template< PlatformEndianness ENDIANNESS = BUILD_ENDIANNESS >
	constexpr uint32_t GetPackedBytes(
		const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4,
		const uint8_t b5, const uint8_t b6, const uint8_t b7, const uint8_t b8
	);

	/**
		@brief	Translation from `std::chrono` time into `double` seconds.
		@param	duration	Time interval, represented in `std::chrono` format.
		@return				Return value is an equivalent amount of seconds, including fractions of second.
	*/
	template< typename TCounterType, typename TPeriodType >
	inline const Time GetSecondsFromDuration( const std::chrono::duration<TCounterType, TPeriodType>& duration )
	{
		return std::chrono::duration_cast<TimeDuration>( duration ).count();
	}

	/**
		@brief	Translation from `Time` seconds into `std::chrono` time.
		@param	seconds		Time interval, represented by amount of seconds.
		@return				Return value is an `std::chrono::nanoseconds` equivalent of `seconds`.
	*/
	template< typename TCounterType = int64_t, typename TPeriodType = std::nano >
	inline auto GetDurationFromSeconds( const Time seconds )
	{
		return std::chrono::duration_cast<std::chrono::duration<TCounterType, TPeriodType>>( TimeDuration{ seconds } );
	}

	/**
		@brief		Return the number of elements in arbitrary container.
		@warning	This implementation uses `container.size()` function.
		@param	container	Elements container.
		@return				Return the number of elements in container.
	*/
	template< typename TContainer >
	constexpr const size_t GetElementsNumber( const TContainer& container )
	{
		return container.size();
	}

	/**
		@brief	Return the number of elements in arbitrary plain array.
		@param	container	Elements container.
		@return				Return the dimension of `container`.
	*/
	template< typename TArrayElement, size_t ARRAY_SIZE >
	constexpr const size_t GetElementsNumber( const TArrayElement (&container)[ ARRAY_SIZE ] )
	{
		return ARRAY_SIZE;
	}

	/**
		@brief	Copying-swap assignation paradigm implementation.

		@tparam	TValue		The type of entities to assign.
		@tparam	TArguments	Construction arguments to asign operation.
		@param	left		The left operand of assign operation.
		@param	arguments	Number of arguments to construct the right operand.
		@return				The value returned is an `left` operand after the assignation.
	*/
	template< typename TValue, typename... TArguments >
	inline TValue& CopyAndSwap( TValue& left, TArguments... arguments )
	{
		TValue temp{ std::forward<TArguments>( arguments )... };
		std::swap( left, temp );
		return left;
	}
}
