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

		@tparam	THost					Type of host, where the functionality should be mixed in.
		@tparam	USE_CONST_PROPAGATION	Whether the const-propagation should be used.
	*/
	template< typename THost, const bool USE_CONST_PROPAGATION = true >
	class StandardArrayFacade : public THost
	{
	// Public inner types.
	public:
		// Regular size type.
		using size_type = size_t;

		// Regular difference type.
		using difference_type = ptrdiff_t;

		// Stored value.
		using value_type = typename THost::Value;

		// Reference to stored value.
		using reference = typename THost::ValueReference;

		// Reference to constant stored value.
		using const_reference = typename THost::ConstValueReference;

		// Pointer to stored value.
		using pointer = typename THost::ValuePointer;

		// Pointer to constant stored value.
		using const_pointer = typename THost::ConstValuePointer;

		// Regular iterator for values.
		using iterator = typename THost::Iterator;

		// Regular iterator for constant values.
		using const_iterator = typename THost::ConstIterator;

		// Reverse iterator for values.
		using reverse_iterator = std::reverse_iterator<iterator>;

		// Reverse iterator for constant values.
		using reverse_const_iterator = std::reverse_iterator<const_iterator>;

	// Public lifetime management.
	public:
		using THost::THost;

	// Public interface.
	public:
		// Returns a reference to the element at specified location `index`, with bounds checking.
		inline reference at( const size_type index )				{ return THost::GetValueAt( index ); };

		// Returns a reference to the element at specified location `index`, with bounds checking.
		inline const_reference at( const size_type index ) const	{ return THost::GetValueAt( index ); };

		// Returns a reference to the first element.
		inline reference front()									{ return THost::GetFirstValue(); };

		// Returns a reference to the first element.
		inline const_reference front() const						{ return THost::GetFirstValue(); };

		// Returns a reference to the last element.
		inline reference back()										{ return THost::GetLastValue(); };

		// Returns a reference to the last element.
		inline const_reference back() const							{ return THost::GetLastValue(); };

		// Returns pointer to the underlying memory serving as element storage.
		inline pointer data()										{ return THost::GetMemory(); };

		// Returns pointer to the underlying memory serving as element storage.
		inline const_pointer data() const							{ return THost::GetMemory(); };

		// Returns an iterator to the first element.
		inline iterator begin()										{ return THost::GetBegin(); };

		// Returns an iterator to the first element.
		inline const_iterator begin() const							{ return THost::GetBegin(); };

		// Returns an iterator to the first element.
		inline const_iterator cbegin() const						{ return THost::GetBegin(); };

		// Returns an iterator to the element following the last element.
		inline iterator end()										{ return THost::GetEnd(); };

		// Returns an iterator to the element following the last element.
		inline const_iterator end() const							{ return THost::GetEnd(); };

		// Returns an iterator to the element following the last element.
		inline const_iterator cend() const							{ return THost::GetEnd(); };

		// Returns a reverse iterator to the first element.
		inline reverse_iterator rbegin()							{ return std::make_reverse_iterator( THost::GetEnd() ); };

		// Returns a reverse iterator to the first element.
		inline reverse_const_iterator rbegin() const				{ return std::make_reverse_iterator( THost::GetEnd() ); };

		// Returns a reverse iterator to the first element.
		inline reverse_const_iterator crbegin() const				{ return std::make_reverse_iterator( THost::GetEnd() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_iterator rend()								{ return std::make_reverse_iterator( THost::GetBegin() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_const_iterator rend() const					{ return std::make_reverse_iterator( THost::GetBegin() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_const_iterator crend() const					{ return std::make_reverse_iterator( THost::GetBegin() ); };

		// Checks if the container has no elements.
		inline const bool empty() const								{ return THost::IsEmpty(); };

		// Returns the number of elements in the container.
		inline const size_type size() const							{ return THost::GetLength(); };

		// Assigns the given value to all elements in the container.
		inline void fill( const_reference value )					{ THost::FillWith( value ); };

		// Exchanges the contents of the container with those of other.
		inline void swap( THost& other )							{ THost::Swap( other ); };
	};

	/**
		@brief	STL-like interface for array-like container. May be used to treat the custom array-like container as standard container.

		This branch doesn't use the const-propagation. The host container allows to access underlaying elements via constant context.

		@tparam	THost	Type of host, where the functionality should be mixed in.
	*/
	template< typename THost >
	class StandardArrayFacade<THost, false>
	{
	// Public inner types.
	public:
		// Regular size type.
		using size_type = size_t;

		// Regular difference type.
		using difference_type = ptrdiff_t;

		// Stored value.
		using value_type = typename THost::Value;

		// Reference to stored value.
		using reference = typename THost::Reference;

		// Pointer to stored value.
		using pointer = typename THost::Pointer;

		// Regular iterator for values.
		using iterator = typename THost::Iterator;

		// Reverse iterator for values.
		using reverse_iterator = std::reverse_iterator<iterator>;

	// Public lifetime management.
	public:
		using THost::THost;

	// Public interface.
	public:
		// Returns a reference to the element at specified location `index`, with bounds checking.
		inline reference at( const size_type index ) const			{ return THost::GetValueAt( index ); };

		// Returns a reference to the first element.
		inline reference front() const								{ return THost::GetFirstValue(); };

		// Returns a reference to the last element.
		inline reference back() const								{ return THost::GetLastValue(); };

		// Returns pointer to the underlying memory serving as element storage.
		inline pointer data() const									{ return THost::GetMemory(); };

		// Returns an iterator to the first element.
		inline iterator begin() const								{ return THost::GetBegin(); };

		// Returns an iterator to the first element.
		inline iterator cbegin() const								{ return THost::GetBegin(); };

		// Returns an iterator to the element following the last element.
		inline iterator end() const									{ return THost::GetEnd(); };

		// Returns an iterator to the element following the last element.
		inline iterator cend() const								{ return THost::GetEnd(); };

		// Returns a reverse iterator to the first element.
		inline reverse_iterator rbegin() const						{ return std::make_reverse_iterator( THost::GetEnd() ); };

		// Returns a reverse iterator to the first element.
		inline reverse_iterator crbegin() const						{ return std::make_reverse_iterator( THost::GetEnd() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_iterator rend() const						{ return std::make_reverse_iterator( THost::GetBegin() ); };

		// Returns a reverse iterator to the element following the last element.
		inline reverse_iterator crend() const						{ return std::make_reverse_iterator( THost::GetBegin() ); };

		// Checks if the container has no elements.
		inline const bool empty() const								{ return THost::IsEmpty(); };

		// Returns the number of elements in the container.
		inline const size_type size() const							{ return THost::GetSize(); };

		// Assigns the given value to all elements in the container.
		inline void fill( const value_type& value )					{ THost::FillWith( value ); };

		// Exchanges the contents of the container with those of other.
		inline void swap( THost& other )							{ THost::Swap( other ); };
	};
}
}
}
}
