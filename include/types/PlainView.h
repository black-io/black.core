#pragma once


namespace Black
{
inline namespace Core
{
	/**
	*/
	template< typename TStoredType >
	class PlainView final
	{
	// Inner entities.
	public:
		static_assert( !IS_REFERENCE<TStoredType>, "Element type may not be reference type." );


		// Size of single element of view.
		static constexpr size_t ELEMENT_SIZE	= sizeof( TStoredType );


		// Type of stored elements.
		using Element		= TStoredType;

		// Iterator of view.
		using Iterator		= Element*;

	// Construction interface.
	public:
		PlainView()						= default;
		PlainView( const PlainView& )	= default;
		PlainView( PlainView&& )		= default;
		PlainView( Element* head, Element* tail );
		PlainView( Element* head, const size_t length );

		template< typename TOtherType, typename = Conditional<IS_CONVERTIBLE<TOtherType*, TStoredType*>> >
		PlainView( const PlainView<TOtherType>& other );

		template< size_t ARRAY_LENGTH >
		PlainView( Element elements[ ARRAY_LENGTH ] ) : PlainView{ elements, ARRAY_LENGTH } {};

		template< size_t ARRAY_LENGTH >
		PlainView( std::array<Element, ARRAY_LENGTH>& elements ) : PlainView{ elements.data(), ARRAY_LENGTH } {};

		template< typename TAllocator >
		PlainView( std::vector<Element, TAllocator>& elements ) : PlainView{ elements.data(), elements.size() } {};


		inline PlainView& operator = ( const PlainView& )	= default;
		inline PlainView& operator = ( PlainView& )			= default;

		template< typename TOtherType, typename = Conditional<IS_CONVERTIBLE<TOtherType*, TStoredType*>> >
		inline PlainView& operator = ( const PlainView<TOtherType>& other );

		template< size_t ARRAY_LENGTH >
		inline PlainView& operator = ( Element elements[ ARRAY_LENGTH ] );

		template< size_t ARRAY_LENGTH >
		inline PlainView& operator = ( std::array<Element, ARRAY_LENGTH>& elements );

		template< typename TAllocator >
		inline PlainView& operator = ( std::vector<Element, TAllocator>& elements );

	// Public interface.
	public:
		//
		inline const bool IsEmpty() const;

		//
		inline const bool IsInside( Iterator value ) const;


		//
		inline TStoredType* GetElement( const size_t index ) const;

		//
		inline Iterator GetHead() const				{ return m_head; };

		//
		inline Iterator GetTail() const				{ return m_tail; };

		//
		inline TStoredType* GetData() const			{ return m_head; };

		//
		inline const size_t GetLength() const		{ return m_size; };

		//
		inline const size_t GetUsedBytes() const	{ return m_size * ELEMENT_SIZE; };


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


		inline const bool empty() const						{ return IsEmpty(); };
		inline reference at( const size_type index ) const	{ return GetElement( index ); };
		inline iterator begin() const						{ return GetHead(); };
		inline iterator end() const							{ return GetTail(); };
		inline pointer data() const							{ return GetData(); };
		inline size_type size() const						{ return GetLength(); };

	private:
		TStoredType*	m_head	= nullptr;	// Head of view.
		TStoredType*	m_tail	= nullptr;	// Tail of view.
		size_t			m_size	= 0;		// Size of view.
	};
}
}
