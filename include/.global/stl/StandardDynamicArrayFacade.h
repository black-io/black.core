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
	*/
	template< typename THost, const bool USE_CONST_PROPAGATION = true >
	class StandardDynamicArrayFacade : public StandardArrayFacade<THost, USE_CONST_PROPAGATION>
	{
	// Used inner types.
	public:
		using StandardArrayFacade<THost, USE_CONST_PROPAGATION>::size_type;

	// Public lifetime management.
	public:
		using StandardArrayFacade<THost, USE_CONST_PROPAGATION>::StandardArrayFacade;

	// Public interface.
	public:
		// Returns the number of elements that the container has currently allocated space for.
		inline const size_type capacity() const					{ return THost::GetCapacity(); };

		// Increase the capacity of the container to a value that's greater or equal to `new_capacity`.
		inline void reserve( const size_type new_capacity )		{ THost::ReserveCapacity( new_capacity ); };

		// Resizes the container to contain count elements. Capacity may be modified as well.
		inline void resize( const size_type new_size )			{ THost::SetLength( new_size ); };
	};
}
}
}
}
