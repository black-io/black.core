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
		@brief	STL-like interface for array-like container. May be used to treat the custom array-like container as standard container.

		@tparam	TBase					Type of base class, where the initial functionality should defined.
		@tparam	USE_CONST_PROPAGATION	Whether the const-propagation should be used.
	*/
	template< typename TBase, const bool USE_CONST_PROPAGATION = true >
	class StandardArrayFacade : public TBase
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
		// Returns a reference to the element at specified location `index`, with bounds checking.
		inline reference at( const size_type index )				{ return TBase::GetValueAt( index ); };

		// Returns a reference to the element at specified location `index`, with bounds checking.
		inline const_reference at( const size_type index ) const	{ return TBase::GetValueAt( index ); };

		// Returns a reference to the first element.
		inline reference front()									{ return TBase::GetFirstValue(); };

		// Returns a reference to the first element.
		inline const_reference front() const						{ return TBase::GetFirstValue(); };

		// Returns a reference to the last element.
		inline reference back()										{ return TBase::GetLastValue(); };

		// Returns a reference to the last element.
		inline const_reference back() const							{ return TBase::GetLastValue(); };

		// Returns pointer to the underlying memory serving as element storage.
		inline pointer data()										{ return TBase::GetMemory(); };

		// Returns pointer to the underlying memory serving as element storage.
		inline const_pointer data() const							{ return TBase::GetMemory(); };

		// Returns an iterator to the first element.
		inline iterator begin()										{ return TBase::GetBegin(); };

		// Returns an iterator to the first element.
		inline const_iterator begin() const							{ return TBase::GetBegin(); };

		// Returns an iterator to the first element.
		inline const_iterator cbegin() const						{ return TBase::GetBegin(); };

		// Returns an iterator to the element following the last element.
		inline iterator end()										{ return TBase::GetEnd(); };

		// Returns an iterator to the element following the last element.
		inline const_iterator end() const							{ return TBase::GetEnd(); };

		// Returns an iterator to the element following the last element.
		inline const_iterator cend() const							{ return TBase::GetEnd(); };

		// Returns a reverse iterator to the first element.
		inline reverse_iterator rbegin()							{ return std::make_reverse_iterator( TBase::GetEnd() ); };

		// Returns a reverse iterator to the first element.
		inline reverse_const_iterator rbegin() const				{ return std::make_reverse_iterator( TBase::GetEnd() ); };

		// Returns a reverse iterator to the first element.
		inline reverse_const_iterator crbegin() const				{ return std::make_reverse_iterator( TBase::GetEnd() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_iterator rend()								{ return std::make_reverse_iterator( TBase::GetBegin() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_const_iterator rend() const					{ return std::make_reverse_iterator( TBase::GetBegin() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_const_iterator crend() const					{ return std::make_reverse_iterator( TBase::GetBegin() ); };

		// Checks if the container has no elements.
		inline const bool empty() const								{ return TBase::IsEmpty(); };

		// Returns the number of elements in the container.
		inline const size_type size() const							{ return TBase::GetLength(); };

		// Assigns the given value to all elements in the container.
		inline void fill( const_reference value )					{ TBase::FillWith( value ); };

		// Exchanges the contents of the container with those of other.
		inline void swap( TBase& other )							{ TBase::Swap( other ); };
	};

	/**
		@brief	STL-like interface for array-like container. May be used to treat the custom array-like container as standard container.

		This branch doesn't use the const-propagation. The host container allows to access underlaying elements via constant context.

		@tparam	TBase	Type of host, where the functionality should be mixed in.
	*/
	template< typename TBase >
	class StandardArrayFacade<TBase, false> : public TBase
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
		// Returns a reference to the element at specified location `index`, with bounds checking.
		inline reference at( const size_type index ) const			{ return TBase::GetValueAt( index ); };

		// Returns a reference to the first element.
		inline reference front() const								{ return TBase::GetFirstValue(); };

		// Returns a reference to the last element.
		inline reference back() const								{ return TBase::GetLastValue(); };

		// Returns pointer to the underlying memory serving as element storage.
		inline pointer data() const									{ return TBase::GetMemory(); };

		// Returns an iterator to the first element.
		inline iterator begin() const								{ return TBase::GetBegin(); };

		// Returns an iterator to the first element.
		inline iterator cbegin() const								{ return TBase::GetBegin(); };

		// Returns an iterator to the element following the last element.
		inline iterator end() const									{ return TBase::GetEnd(); };

		// Returns an iterator to the element following the last element.
		inline iterator cend() const								{ return TBase::GetEnd(); };

		// Returns a reverse iterator to the first element.
		inline reverse_iterator rbegin() const						{ return std::make_reverse_iterator( TBase::GetEnd() ); };

		// Returns a reverse iterator to the first element.
		inline reverse_iterator crbegin() const						{ return std::make_reverse_iterator( TBase::GetEnd() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_iterator rend() const						{ return std::make_reverse_iterator( TBase::GetBegin() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_iterator crend() const						{ return std::make_reverse_iterator( TBase::GetBegin() ); };

		// Checks if the container has no elements.
		inline const bool empty() const								{ return TBase::IsEmpty(); };

		// Returns the number of elements in the container.
		inline const size_type size() const							{ return TBase::GetLength(); };

		// Assigns the given value to all elements in the container.
		inline void fill( const value_type& value )					{ TBase::FillWith( value ); };

		// Exchanges the contents of the container with those of other.
		inline void swap( TBase& other )							{ TBase::Swap( other ); };
	};
}
}
}
}
