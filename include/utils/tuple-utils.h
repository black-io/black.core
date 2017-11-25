#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Utils
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
	void ForEach( std::tuple<TArguments...>& elements, const TFunction& function );
}


inline namespace TextUtils
{
	/**
		@brief	Format the arguments into string.
		Uses formatting syntax similar to `str.format` from Python.
		Syntax documentation : http://cppformat.github.io/latest/syntax.html
		@param	format		Declares the format, how `arguments` must be placed in output string.
		@param	arguments	The arguments to be formatted.
		@tparam	TChar		Type of string character.
		@tparam	TArguments	Types of passed arguments.
		@return				The value returned is an formatted string.
	*/
	template< typename TChar, typename... TArguments >
	inline std::basic_string<TChar> FormatString( Black::RegularStringView<TChar> format, const std::tuple<TArguments...>& arguments );
}
}
}
