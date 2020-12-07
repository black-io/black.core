#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
	/**
		@brief	For-each loop over arbitrary tuple.
		@note	`function` may be global function, lambda object or functor with even template operator ().
		@param	elements	Tuple of elements to be iterated.
		@param	function	Callable object to execute over elements of tuple.
		@tparam	TFunction	Type of callable object.
		@tparam	TArguments	List of tuple types.
	*/
	template< typename TFunction, typename... TArguments >
	void ForEach( std::tuple<TArguments...>& elements, TFunction&& function );
}
}
}
