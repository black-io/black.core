#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	/**
		@brief	The more flexible view of plain elements.
		The `plain view` is one more helper class to simplify the controlling of plain arrays.
	*/
	template< typename TStoredType >
	class PlainView final
	{
	// Inner entities.
	public:
		static_assert( !IS_REFERENCE<TStoredType>,	"Element type may not be reference type." );


		// Size of single element of view.
		static constexpr size_t ELEMENT_SIZE	= sizeof( TStoredType );


		// Type of stored elements.
		using Element		= TStoredType;

		// Iterator of view.
		using Iterator		= Element*;

	// Friendship interface.
	public:
		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline Iterator begin( const PlainView& range )			{ return range.GetHead(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline Iterator end( const PlainView& range )			{ return range.GetTail(); };

		// 'Swap' interface.
		friend inline void swap( PlainView& left, PlainView& right )	{ left.Swap( right ); };

	// Construction interface.
	public:
		PlainView()						= default;
		PlainView( const PlainView& )	= default;
		PlainView( PlainView&& other );
		PlainView( Element* head, Element* tail );
		PlainView( Element* head, const size_t length );

		template< typename TOtherType, typename = Black::EnableIf<Black::IS_CONVERTIBLE<TOtherType*, TStoredType*>> >
		explicit PlainView( const PlainView<TOtherType>& other ) : PlainView( other.m_head, other.m_tail ) {};

		template< size_t ARRAY_LENGTH >
		explicit PlainView( Element (&elements)[ ARRAY_LENGTH ] ) : PlainView{ elements, ARRAY_LENGTH } {};

		template< size_t ARRAY_LENGTH >
		explicit PlainView( std::array<Element, ARRAY_LENGTH>& elements ) : PlainView{ elements.data(), ARRAY_LENGTH } {};

		template< typename TAllocator >
		explicit PlainView( std::vector<Element, TAllocator>& elements ) : PlainView{ elements.data(), elements.size() } {};


		inline PlainView& operator = ( const PlainView& )	= default;
		inline PlainView& operator = ( PlainView&& other );

		template< typename TOtherType, typename = Black::EnableIf<Black::IS_CONVERTIBLE<TOtherType*, TStoredType*>> >
		inline PlainView& operator = ( const PlainView<TOtherType>& other )				{ return CopyAndSwap( *this, other ); };

		template< size_t ARRAY_LENGTH >
		inline PlainView& operator = ( Element elements[ ARRAY_LENGTH ] )				{ return CopyAndSwap( *this, elements ); };

		template< size_t ARRAY_LENGTH >
		inline PlainView& operator = ( std::array<Element, ARRAY_LENGTH>& elements )	{ return CopyAndSwap( *this, elements ); };

		template< typename TAllocator >
		inline PlainView& operator = ( std::vector<Element, TAllocator>& elements )		{ return CopyAndSwap( *this, elements ); };

	// Public interface.
	public:
		// Invalidate the view making it empty.
		inline void Invalidate();


		// Checks the view is empty.
		inline const bool IsEmpty() const;

		// Checks the iterator is inside of view.
		inline const bool IsInside( Iterator value ) const;


		// Get the element at position.
		inline TStoredType& GetElement( const size_t index ) const;

		// Get the head of view - the iterator to first element.
		inline Iterator GetHead() const				{ return m_head; };

		// Get the tail of view - the iterator next of last element, which may not be dereferenced.
		inline Iterator GetTail() const				{ return m_tail; };

		// Get the view data.
		inline TStoredType* GetData() const			{ return m_head; };

		// Get the length of view.
		inline const size_t GetLength() const		{ return m_length; };

		// Get the number of bytes the elements of view stored.
		inline const size_t GetUsedBytes() const	{ return m_length * ELEMENT_SIZE; };


		inline explicit operator const bool () const					{ return !IsEmpty(); };
		inline const bool operator ! () const							{ return IsEmpty(); };

		inline TStoredType& operator [] ( const size_t index ) const	{ return GetElement( index ); };

		inline const bool operator == ( const PlainView& other ) const;
		inline const bool operator != ( const PlainView& other ) const;

	// STL-conformance interface.
	public:
		using value_type		= Element;
		using size_type			= std::size_t;
		using difference_type	= std::ptrdiff_t;
		using reference			= value_type&;
		using const_reference	= const value_type&;
		using pointer			= value_type*;
		using const_pointer		= const value_type*;
		using iterator			= Iterator;


		inline void swap( PlainView& other )				{ Swap( other ); };
		inline const bool empty() const						{ return IsEmpty(); };
		inline reference at( const size_type index ) const	{ return GetElement( index ); };
		inline iterator begin() const						{ return GetHead(); };
		inline iterator end() const							{ return GetTail(); };
		inline pointer data() const							{ return GetData(); };
		inline size_type size() const						{ return GetLength(); };

	// Private interface.
	private:
		// Swap the content of views.
		inline void Swap( PlainView& other );

	private:
		TStoredType*	m_head		= nullptr;	// Head of view.
		TStoredType*	m_tail		= nullptr;	// Tail of view.
		size_t			m_length	= 0;		// Number of elements in view.
	};
}
}
}
