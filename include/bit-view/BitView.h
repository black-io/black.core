#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	/**
		@brief	View of plain bits in arbitrary memory.
	*/
	template< typename TBitStorage >
	class BitView final
	{
	// Public inner types.
	public:
		// Type of stored elements.
		using Element		= TBitStorage;

		// Index of arbitrary bit inside of view.
		using BitIndex		= Internal::BitStorageIndex<Element>;

		// Iterator of view.
		using Iterator		= Internal::BitIterator<Element>;

		// Bit adapter.
		using BitAdapter	= Internal::BitAdapter<Element>;


		// Size of single element of view.
		static constexpr size_t ELEMENT_SIZE	= sizeof( Element );

	// Friendship interface.
	public:
		// Swap the content of bit views.
		friend inline void swap( BitView& left, BitView& right )	{ left.Swap( right ); };

		// Get the head iterator of bit view.
		friend inline Iterator begin( BitView& view )				{ return view.GetHead(); };

		// Get the tail iterator of bit view.
		friend inline Iterator end( BitView& view )					{ return view.GetTail(); };

	// Construction and assignment.
	public:
		BitView() = default;
		BitView( const BitView& other ) = default;
		BitView( BitView&& other );
		BitView( Element* head, const size_t bit_length );


		inline BitView& operator = ( const BitView& other ) = default;
		inline BitView& operator = ( BitView&& other );

	// Public interface.
	public:
		// Invalidate the view making it empty.
		inline void Invalidate();


		// Whether the view carries some bit stream.
		inline const bool IsValid() const;

		// Whether the view carries some bits.
		inline const bool IsEmpty() const;

		// Does the iterator is located inside of bit view.
		inline const bool IsInside( Iterator value ) const;


		// Get the element at position.
		inline BitAdapter GetElement( const size_t index ) const;

		// Get the front bit of view.
		inline BitAdapter GetFront() const;

		// get the last significant bit of view.
		inline BitAdapter GetBack() const;

		// Get the head of view - the iterator to first element.
		inline Iterator GetHead() const;

		// Get the tail of view - the iterator next of last element, which may not be dereferenced.
		inline Iterator GetTail() const;

		// Get the view data.
		inline Element* GetData() const;

		// Get the length of view.
		inline const size_t GetLength() const;

		// Get the length of view in storage items.
		inline const size_t GetStorageLength() const;

		// Get the number of bytes the elements of view stored.
		inline const size_t GetUsedBytes() const;


		inline explicit operator const bool () const					{ return !IsEmpty(); };
		inline const bool operator ! () const							{ return IsEmpty(); };

		inline BitAdapter operator [] ( const size_t index ) const		{ return GetElement( index ); };

		inline const bool operator == ( const BitView& other ) const;
		inline const bool operator != ( const BitView& other ) const;

	// STL-conformance interface.
	public:
		using value_type		= BitAdapter;
		using size_type			= size_t;
		using difference_type	= ptrdiff_t;
		using reference			= value_type&;
		using const_reference	= const value_type&;
		using pointer			= Element*;
		using const_pointer		= const Element*;
		using iterator			= Iterator;
		using const_iterator	= Iterator;


		inline const bool empty() const						{ return IsEmpty(); };
		inline value_type at( const size_type index ) const	{ return GetElement( index ); };
		inline value_type front() const						{ return GetFront(); };
		inline value_type back() const						{ return GetBack(); };
		inline iterator begin() const						{ return GetHead(); };
		inline iterator end() const							{ return GetTail(); };
		inline pointer data() const							{ return GetData(); };
		inline size_type size() const						{ return GetLength(); };

	// Private interface.
	private:
		// Swap the content with other bit view.
		inline void Swap( BitView& other );

	// Private state.
	private:
		Element*	m_head			= nullptr;	// Head of bit view stream.
		BitIndex	m_bit_length	{ 0 };		// Length of bit view stream.
	};
}
}
}
