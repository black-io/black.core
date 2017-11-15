#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	/**
	*/
	template< typename TStoredType >
	class PlainVector final
	{
	// Inner entities.
	public:
		static_assert( !IS_REFERENCE<TStoredType>,	"Element type may not be reference type." );
		static_assert( !IS_CONST<TStoredType>,		"Element type may not be constant." );


		// Size of single element of view.
		static constexpr size_t ELEMENT_SIZE	= sizeof( TStoredType );


		// Type of stored elements.
		using Element		= TStoredType;

		// Iterator of view.
		using Iterator		= Element*;

		// Iterator of view.
		using ConstIterator	= const Element*;

	// Construction interface.
	public:
		PlainVector()						= default;
		PlainVector( const PlainVector& )	= default;
		PlainVector( PlainVector&& )		= default;
		explicit PlainVector( const size_t length );
		PlainVector( const size_t length, const TStoredType& proto );
		PlainVector( TStoredType* elements, const size_t length );
		PlainVector( TStoredType* head, TStoredType* tail );
		PlainVector( std::initializer_list<TStoredType> elements );

		template< typename TOtherType, typename = EnableIf<IS_CONVERTIBLE<TOtherType*, TStoredType*>> >
		explicit PlainVector( PlainView<TOtherType> elements );

		template< typename TOtherType, size_t ARRAY_LENGTH, typename = EnableIf<IS_CONVERTIBLE<TOtherType*, TStoredType*>> >
		explicit PlainVector( TOtherType elements[ ARRAY_LENGTH ] );

		template< typename TOtherType, size_t ARRAY_LENGTH, typename = EnableIf<IS_CONVERTIBLE<TOtherType*, TStoredType*>> >
		explicit PlainVector( const std::array<TOtherType, ARRAY_LENGTH>& elements );

		template< typename TOtherType, typename TAllocator, typename = EnableIf<IS_CONVERTIBLE<TOtherType*, TStoredType*>> >
		explicit PlainVector( const std::vector<TOtherType, TAllocator>& elements );


		~PlainVector();


		inline PlainVector& operator = ( const PlainVector& )									= default;
		inline PlainVector& operator = ( PlainVector&& )										= default;
		inline PlainVector& operator = ( std::initializer_list<TStoredType> elements )			{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherType, typename = EnableIf<IS_CONVERTIBLE<TOtherType*, TStoredType*>> >
		inline PlainVector& operator = ( PlainView<TOtherType> elements )						{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherType, size_t ARRAY_LENGTH, typename = EnableIf<IS_CONVERTIBLE<TOtherType*, TStoredType*>> >
		inline PlainVector& operator = ( TOtherType elements[ ARRAY_LENGTH ] )					{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherType, size_t ARRAY_LENGTH, typename = EnableIf<IS_CONVERTIBLE<TOtherType*, TStoredType*>> >
		inline PlainVector& operator = ( const std::array<TOtherType, ARRAY_LENGTH>& elements )	{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherType, typename TAllocator, typename = EnableIf<IS_CONVERTIBLE<TOtherType*, TStoredType*>> >
		inline PlainVector& operator = ( const std::vector<TOtherType, TAllocator>& elements )	{ return CopyAndSwap( *this, elements ); };

	// Public interface.
	public:
		// Invalidate the used memory making it free.
		inline void Invalidate();

		// Copy the elements from given view.
		inline void CopyFrom( const PlainView<TStoredType>& other );

		// Swap the content of views.
		inline void Swap( PlainView& other );

		// Set the number of currently allocated elements.
		inline void SetSize( const size_t new_size );

		// Set the desired capacity. Takes no effect in case the capacity already fits the desired value.
		inline void ReserveCapacity( const size_t desired_size );

		// Set the capacity.
		inline void SetCapacity( const size_t new_size );

		// Set the capacity equal to current size.
		inline void ShrinkToFitSize();


		// Checks the view is empty.
		inline const bool IsEmpty() const;

		// Checks the iterator is inside of view.
		inline const bool IsInside( Iterator value ) const;


		// Get the element at position.
		inline TStoredType& GetElement( const size_t index );

		// Get the element at position.
		inline const TStoredType& GetElement( const size_t index ) const;

		// Get the head of view - the iterator to first element.
		inline Iterator GetHead()					{ return m_head; };

		// Get the tail of view - the iterator next of last element, which may not be dereferenced.
		inline Iterator GetTail()					{ return m_tail; };

		// Get the head of view - the iterator to first element.
		inline ConstIterator GetHead() const		{ return m_head; };

		// Get the tail of view - the iterator next of last element, which may not be dereferenced.
		inline ConstIterator GetTail() const		{ return m_tail; };

		// Get the view data.
		inline TStoredType* GetData()				{ return m_head; };

		// Get the view data.
		inline const TStoredType* GetData() const	{ return m_head; };

		// Get the length of view.
		inline const size_t GetLength() const		{ return m_length; };

		// Get the capacity of vector.
		inline const size_t GetCapacity() const		{ return m_capacity; };

		// Get the number of bytes the elements of view stored.
		inline const size_t GetUsedBytes() const	{ return m_length * ELEMENT_SIZE; };


		inline operator PlainView<TStoredType> ()				{ return { m_memory, m_length }; };
		inline operator PlainView<const TStoredType> () const	{ return { m_memory, m_length }; };

		inline explicit operator const bool () const			{ return !IsEmpty(); };
		inline const bool operator ! () const					{ return IsEmpty(); };

		inline TStoredType& operator [] ( const size_t index )						{ return GetElement( index ); };
		inline const TStoredType& operator [] ( const size_t index ) const			{ return GetElement( index ); };

		inline const bool operator == ( const PlainVector& other ) const			{ return m_memory == other.m_memory; };
		inline const bool operator != ( const PlainVector& other ) const			{ return m_memory != other.m_memory; };
		inline const bool operator == ( const PlainView<TStoredType>& other ) const	{ return ( m_memory == other.m_head ) && ( m_length == other.m_length ); };
		inline const bool operator != ( const PlainView<TStoredType>& other ) const	{ return ( m_memory != other.m_head ) || ( m_length != other.m_length ); };

	// STL-conformance interface.
	public:

	// Private interface.
	private:

	private:
		TStoredType*	m_memory	= nullptr;	// Stored elements.
		size_t			m_capacity	= 0;		// Number of elements available for currently allocated memory.
		size_t			m_length	= 0;		// Number of currently allocated elements.
	};
}
}
}
