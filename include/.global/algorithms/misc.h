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
		@brief	Converts value of enumeration type to its underlying type value.
		@param	value			Te value to be converted.
		@tparam	TEnumeration	Type of enumeration.
		@return					Returns value of `TEnumeration` underlying type.
	*/
	template< typename TEnumeration >
	constexpr const auto GetEnumValue( const TEnumeration value )
	{
		static_assert( std::is_enum_v<TEnumeration>, "`TEnumeration` template argument should be an enumeration." );
		return static_cast<const std::underlying_type_t<TEnumeration>>( value );
	}

	/**
		@brief	Copying-swap assignation paradigm implementation.

		@tparam	TValue		The type of entities to assign.
		@tparam	TArguments	Construction arguments to assign operation.
		@param	left		The left operand of assign operation.
		@param	arguments	Number of arguments to construct the right operand.
		@return				The value returned is an `left` operand after the assignation.
	*/
	template< typename TValue, typename... TArguments >
	inline TValue& CopyAndSwap( TValue& left, TArguments&&... arguments )
	{
		using std::swap;

		TValue vicar{ std::forward<TArguments>( arguments )... };
		swap( left, vicar );

		return left;
	}
}
}
}
}
