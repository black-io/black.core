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
	template< typename THost, typename TBase, const bool USE_CONST_PROPAGATION = true >
	class StandardForwardListFacade : public TBase
	{
	// Public inner types.
	public:
		// Regular size type.
		using size_type = size_t;

		// Regular difference type.
		using difference_type = ptrdiff_t;

		// Stored value.
		using value_type = typename TBase::Value;

		// Reference to stored value.
		using reference = typename TBase::ValueReference;

		// Reference to constant stored value.
		using const_reference = typename TBase::ConstValueReference;

		// Pointer to stored value.
		using pointer = typename TBase::ValuePointer;

		// Pointer to constant stored value.
		using const_pointer = typename TBase::ConstValuePointer;

		// Regular iterator for values.
		using iterator = typename TBase::Iterator;

		// Regular iterator for constant values.
		using const_iterator = typename TBase::ConstIterator;

	// Public lifetime management.
	public:
		using TBase::TBase;

	// Public interface.
	public:
		// Returns a reference to the first element.
		inline reference front()										{ return TBase::GetFirstValue(); };

		// Returns a reference to the first element.
		inline const_reference front() const							{ return TBase::GetFirstValue(); };

		// Returns an iterator to the first element.
		inline iterator begin()											{ return TBase::GetBegin(); };

		// Returns an iterator to the first element.
		inline const_iterator begin() const								{ return TBase::GetBegin(); };

		// Returns an iterator to the first element.
		inline const_iterator cbegin() const							{ return TBase::GetBegin(); };

		// Returns an iterator to the element following the last element.
		inline iterator end()											{ return TBase::GetEnd(); };

		// Returns an iterator to the element following the last element.
		inline const_iterator end() const								{ return TBase::GetEnd(); };

		// Returns an iterator to the element following the last element.
		inline const_iterator cend() const								{ return TBase::GetEnd(); };

		// Erases all elements from the container.
		inline void clear()												{ TBase::Clear(); };

		// Inserts elements after the specified position in the container.
		inline void insert_after( iterator position, reference value )	{ TBase::InsertAfter( position, value ); };

		// Removes specified elements from the container.
		inline void erase_after( iterator position )					{ TBase::EraseAfter( position ); };

		// Prepends the given element value to the beginning of the container.
		inline void push_front( reference value )						{ TBase::PushFront( value ); };

		// Removes the first element of the container.
		inline void pop_front()											{ TBase::PopFront(); };

		// Checks if the container has no elements.
		inline const bool empty() const									{ return TBase::IsEmpty(); };

		// Returns the number of elements in the container.
		inline const size_type size() const								{ return TBase::GetLength(); };

		// Exchanges the contents of the container with those of other.
		inline void swap( THost& other )								{ TBase::Swap( other ); };
	};

	/**
	*/
	template< typename THost, typename TBase >
	class StandardForwardListFacade<THost, TBase, true> : public TBase
	{
	// Public inner types.
	public:
		// Regular size type.
		using size_type = size_t;

		// Regular difference type.
		using difference_type = ptrdiff_t;

		// Stored value.
		using value_type = typename TBase::Value;

		// Reference to stored value.
		using reference = typename TBase::ValueReference;

		// Pointer to stored value.
		using pointer = typename TBase::ValuePointer;

		// Regular iterator for values.
		using iterator = typename TBase::Iterator;

	// Public lifetime management.
	public:
		using TBase::TBase;

	// Public interface.
	public:
		// Returns a reference to the first element.
		inline reference front() const									{ return TBase::GetFirstValue(); };

		// Returns an iterator to the first element.
		inline iterator begin() const									{ return TBase::GetBegin(); };

		// Returns an iterator to the first element.
		inline iterator cbegin() const									{ return TBase::GetBegin(); };

		// Returns an iterator to the element following the last element.
		inline iterator end() const										{ return TBase::GetEnd(); };

		// Returns an iterator to the element following the last element.
		inline iterator cend() const									{ return TBase::GetEnd(); };

		// Erases all elements from the container.
		inline void clear()												{ TBase::Clear(); };

		// Inserts elements after the specified position in the container.
		inline void insert_after( iterator position, reference value )	{ TBase::InsertAfter( position, value ); };

		// Removes specified elements from the container.
		inline void erase_after( iterator position )					{ TBase::EraseAfter( position ); };

		// Prepends the given element value to the beginning of the container.
		inline void push_front( reference value )						{ TBase::PushFront( value ); };

		// Removes the first element of the container.
		inline void pop_front()											{ TBase::PopFront(); };

		// Checks if the container has no elements.
		inline const bool empty() const									{ return TBase::IsEmpty(); };

		// Returns the number of elements in the container.
		inline const size_type size() const								{ return TBase::GetLength(); };

		// Exchanges the contents of the container with those of other.
		inline void swap( THost& other )								{ TBase::Swap( other ); };
	};
}
}
}
}
