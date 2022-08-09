#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Stl
{
	/**
		@brief	STL-like interface for dynamic array-like container. May be used to treat the custom array-like container as standard container.

		This facade extends the `StandardArrayFacade` and allow to reserve the memory and resize the array.

		@tparam	THost					Type of final host, where the facade used to add the functionality.
		@tparam	TBase					Type of base class, where the initial functionality should defined.
		@tparam	USE_CONST_PROPAGATION	Whether the const-propagation should be used.
	*/
	template< typename THost, typename TBase, const bool USE_CONST_PROPAGATION = true >
	class StandardDynamicArrayFacade : public StandardArrayFacade<THost, TBase, USE_CONST_PROPAGATION>
	{
	// Used inner types.
	public:
		using typename StandardArrayFacade<THost, TBase, USE_CONST_PROPAGATION>::size_type;

	// Public lifetime management.
	public:
		using StandardArrayFacade<THost, TBase, USE_CONST_PROPAGATION>::StandardArrayFacade;

	// Public interface.
	public:
		// Returns the number of elements that the container has currently allocated space for.
		inline const size_type capacity() const					{ return TBase::GetCapacity(); };

		// Increase the capacity of the container to a value that's greater or equal to `new_capacity`.
		inline void reserve( const size_type new_capacity )		{ TBase::ReserveCapacity( new_capacity ); };

		// Resizes the container to contain count elements. Capacity may be modified as well.
		inline void resize( const size_type new_size )			{ TBase::SetLength( new_size ); };

		// Erases all elements from the container.
		inline void clear()										{ TBase::SetLength( 0 ); };
	};
}
}
}
}
