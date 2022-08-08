#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
namespace Internal
{
	/**
	*/
	template< typename TValue >
	class PlainView
	{
	// Restrictions.
	public:
		static_assert( !std::is_reference_v<TValue>, "Value type may not be reference type." );

	// Public inner types.
	public:
		// Stored value.
		using Value = TValue;

		// Reference to value.
		using ValueReference = TValue&;

		// Pointer to value.
		using ValuePointer = TValue*;

		// Iterator for values.
		using Iterator = TValue*;

	// Public constants.
	public:
		// Size of single store value.
		static constexpr size_t VALUE_SIZE = sizeof( Value );

	// Friendship interface.
	public:
		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline Iterator begin( const PlainView& range )			{ return range.GetBegin(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline Iterator end( const PlainView& range )			{ return range.GetEnd(); };

		// 'Swap' interface.
		friend inline void swap( PlainView& left, PlainView& right )	{ left.Swap( right ); };

	// Construction interface.
	public:
		inline PlainView()						= default;
		inline PlainView( const PlainView& )	= default;

		inline PlainView( PlainView&& other ) noexcept;
		inline PlainView( ValuePointer memory, const size_t length );


		inline PlainView& operator = ( const PlainView& ) = default;
		inline PlainView& operator = ( PlainView&& other ) noexcept;

	// Public interface.
	public:
		// Invalidate the view making it empty.
		inline void Invalidate();


		// Assign the hosted values to given one.
		inline void FillWith( const Value& value );

		// Swap the content of views.
		inline void Swap( PlainView& other );


		// Checks the view is empty.
		inline const bool IsEmpty() const;

		// Checks the iterator is inside of view.
		inline const bool IsInside( Iterator value ) const;


		// Get the element at position.
		inline ValueReference GetValueAt( const size_t index ) const;

		// Get the begin of view - the iterator to first element.
		inline Iterator GetBegin() const			{ return m_memory; };

		// Get the end of view - the iterator next of last element, which may not be dereferenced.
		inline Iterator GetEnd() const				{ return m_memory + m_length; };

		// Get the view data.
		inline ValuePointer GetMemory() const		{ return m_memory; };

		// Get the length of view.
		inline const size_t GetLength() const		{ return m_length; };

		// Get the number of bytes the elements of view stored.
		inline const size_t GetUsedBytes() const	{ return m_length * VALUE_SIZE; };

	private:
		TValue*	m_memory	= nullptr;	// Unowned memory of viewed elements.
		size_t	m_length	= 0;		// Number of viewed elements.
	};
}


	/**
	*/
	template< typename TValue >
	class PlainView : public Black::StandardArrayFacade<Internal::PlainView<TValue>, false>
	{
	// Public aliases.
	public:
		using typename Internal::PlainView<TValue>::Value;
		using typename Internal::PlainView<TValue>::Iterator;


		using Internal::PlainView<TValue>::GetValueAt;
		using Internal::PlainView<TValue>::IsEmpty;

	// Public lifetime management.
	public:
		using Black::StandardArrayFacade<Internal::PlainView<TValue>, false>::StandardArrayFacade;


		PlainView( Iterator begin, Iterator end ) : PlainView{ begin, std::distance( begin, end ) } {};


		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		PlainView( const PlainView<TOtherValue>& other ) : PlainView( other.GetBegin(), other.GetEnd() ) {};

		template< size_t ARRAY_LENGTH >
		PlainView( Value (&elements)[ ARRAY_LENGTH ] ) : PlainView{ elements, ARRAY_LENGTH } {};

		template< size_t ARRAY_LENGTH >
		PlainView( std::array<Value, ARRAY_LENGTH>& elements ) : PlainView{ elements.data(), ARRAY_LENGTH } {};

		template< typename TAllocator >
		PlainView( std::vector<Value, TAllocator>& elements ) : PlainView{ elements.data(), elements.size() } {};


		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainView& operator = ( const PlainView<TOtherValue>& other )		{ return CopyAndSwap( *this, other ); };

		template< size_t ARRAY_LENGTH >
		inline PlainView& operator = ( Value elements[ ARRAY_LENGTH ] )				{ return CopyAndSwap( *this, elements ); };

		template< size_t ARRAY_LENGTH >
		inline PlainView& operator = ( std::array<Value, ARRAY_LENGTH>& elements )	{ return CopyAndSwap( *this, elements ); };

		template< typename TAllocator >
		inline PlainView& operator = ( std::vector<Value, TAllocator>& elements )	{ return CopyAndSwap( *this, elements ); };

	// Public interface.
	public:
		inline TValue& operator [] ( const size_t index ) const	{ return GetValueAt( index ); };


		inline explicit operator const bool () const			{ return !IsEmpty(); };
		inline const bool operator ! () const					{ return IsEmpty(); };
	};
}
}
}
}
