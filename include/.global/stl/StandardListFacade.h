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
	class StandardListFacade : public TBase
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

		// Reverse iterator for values.
		using reverse_iterator = std::reverse_iterator<iterator>;

		// Reverse iterator for constant values.
		using reverse_const_iterator = std::reverse_iterator<const_iterator>;

	// Public lifetime management.
	public:
		using TBase::TBase;

	// Public interface.
	public:
		// Returns a reference to the first element.
		inline reference front()										{ return TBase::GetFirstValue(); };

		// Returns a reference to the first element.
		inline const_reference front() const							{ return TBase::GetFirstValue(); };

		// Returns a reference to the last element.
		inline reference back()											{ return TBase::GetLastValue(); };

		// Returns a reference to the last element.
		inline const_reference back() const								{ return TBase::GetLastValue(); };

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

		// Returns a reverse iterator to the first element.
		inline reverse_iterator rbegin()								{ return std::make_reverse_iterator( TBase::GetEnd() ); };

		// Returns a reverse iterator to the first element.
		inline reverse_const_iterator rbegin() const					{ return std::make_reverse_iterator( TBase::GetEnd() ); };

		// Returns a reverse iterator to the first element.
		inline reverse_const_iterator crbegin() const					{ return std::make_reverse_iterator( TBase::GetEnd() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_iterator rend()									{ return std::make_reverse_iterator( TBase::GetBegin() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_const_iterator rend() const						{ return std::make_reverse_iterator( TBase::GetBegin() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_const_iterator crend() const						{ return std::make_reverse_iterator( TBase::GetBegin() ); };

		// Erases all elements from the container.
		inline void clear()												{ TBase::Clear(); };

		// Inserts elements after the specified position in the container.
		inline void insert( iterator position, reference value )		{ TBase::Insert( position, value ); };

		// Removes specified elements from the container.
		inline void erase( iterator position )							{ TBase::Erase( position ); };

		// Prepends the given element value to the ending of the container.
		inline void push_back( reference value )						{ TBase::PushBack( value ); };

		// Prepends the given element value to the beginning of the container.
		inline void push_front( reference value )						{ TBase::PushFront( value ); };

		// Removes the last element of the container.
		inline void pop_back()											{ TBase::PopBack(); };

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
	class StandardListFacade<THost, TBase, false> : public TBase
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

		// Reverse iterator for values.
		using reverse_iterator = std::reverse_iterator<iterator>;

	// Public lifetime management.
	public:
		using TBase::TBase;

	// Public interface.
	public:
		// Returns a reference to the first element.
		inline reference front() const									{ return TBase::GetFirstValue(); };

		// Returns a reference to the last element.
		inline reference back() const									{ return TBase::GetLastValue(); };

		// Returns an iterator to the first element.
		inline iterator begin() const									{ return TBase::GetBegin(); };

		// Returns an iterator to the first element.
		inline iterator cbegin() const									{ return TBase::GetBegin(); };

		// Returns an iterator to the element following the last element.
		inline iterator end() const										{ return TBase::GetEnd(); };

		// Returns an iterator to the element following the last element.
		inline iterator cend() const									{ return TBase::GetEnd(); };

		// Returns a reverse iterator to the first element.
		inline reverse_iterator rbegin() const							{ return std::make_reverse_iterator( TBase::GetEnd() ); };

		// Returns a reverse iterator to the first element.
		inline reverse_iterator crbegin() const							{ return std::make_reverse_iterator( TBase::GetEnd() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_iterator rend() const							{ return std::make_reverse_iterator( TBase::GetBegin() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_iterator crend() const							{ return std::make_reverse_iterator( TBase::GetBegin() ); };

		// Erases all elements from the container.
		inline void clear()												{ TBase::Clear(); };

		// Inserts elements after the specified position in the container.
		inline void insert( iterator position, reference value )		{ TBase::Insert( position, value ); };

		// Removes specified elements from the container.
		inline void erase( iterator position )							{ TBase::Erase( position ); };

		// Prepends the given element value to the ending of the container.
		inline void push_back( reference value )						{ TBase::PushBack( value ); };

		// Prepends the given element value to the beginning of the container.
		inline void push_front( reference value )						{ TBase::PushFront( value ); };

		// Removes the last element of the container.
		inline void pop_back()											{ TBase::PopBack(); };

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
