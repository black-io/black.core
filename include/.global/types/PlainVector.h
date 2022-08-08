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
	class PlainVector
	{
	// Restrictions.
	public:
		static_assert( !std::is_reference_v<TValue>,	"Value type may not be reference type." );
		static_assert( !std::is_const_v<TValue>,		"Value type may not be constant." );
		static_assert( std::is_pod_v<TValue>,			"Value type should be plain (PoD) type." );

	// Public inner types.
	public:
		// Stored value.
		using Value = TValue;

		// Reference to value.
		using ValueReference = TValue&;

		// Reference to constant value.
		using ConstValueReference = const TValue&;

		// Pointer to value.
		using ValuePointer = TValue*;

		// Pointer to constant value.
		using ConstValuePointer = const TValue*;

		// Iterator for values.
		using Iterator = TValue*;

		// Iterator for constant values.
		using ConstIterator = const TValue*;

	// Public constants.
	public:
		// Size of single store value.
		static constexpr size_t VALUE_SIZE = sizeof( Value );

	// Friendship interface.
	public:
		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline Iterator begin( PlainVector& range )					{ return range.GetBegin(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline Iterator end( PlainVector& range )					{ return range.GetEnd(); };

		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline ConstIterator begin( const PlainVector& range )		{ return range.GetBegin(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline ConstIterator end( const PlainVector& range )			{ return range.GetEnd(); };

		// 'Swap' interface.
		friend inline void swap( PlainVector& left, PlainVector& right )	{ left.Swap( right ); };

	// Public lifetime management.
	public:
		inline PlainVector() = default;

		inline PlainVector( const PlainVector& other );
		inline PlainVector( PlainVector&& other ) noexcept;

		explicit inline PlainVector( const size_t length );

		inline PlainVector( const size_t length, ConstValueReference prototype );
		inline PlainVector( ConstIterator begin, ConstIterator end );

		inline ~PlainVector() noexcept;


		inline PlainVector& operator = ( const PlainVector& other );
		inline PlainVector& operator = ( PlainVector&& other ) noexcept;

	// Public interface.
	public:
		// Invalidate the used memory making it free.
		inline void Invalidate();

		// Set the number of currently allocated elements.
		inline void SetLength( const size_t length );

		// Set the desired capacity. Takes no effect in case the capacity already fits the desired value.
		inline void ReserveCapacity( const size_t capacity );

		// Set the capacity.
		inline void SetCapacity( const size_t capacity );

		// Set the capacity equal to current length.
		inline void ShrinkToFitLength();


		// Swap the content of vectors.
		inline void Swap( PlainVector& other );


		// Checks the container is empty.
		inline const bool IsEmpty() const;

		// Checks the iterator is inside of container.
		inline const bool IsInside( ConstIterator value ) const;


		// Get the value at position.
		inline ValueReference GetValueAt( const size_t index );

		// Get the value at position.
		inline ConstValueReference GetValueAt( const size_t index ) const;

		// Get the begin of view - the iterator to first element.
		inline Iterator GetBegin()					{ return m_memory; };

		// Get the begin of view - the iterator to first element.
		inline ConstIterator GetBegin() const		{ return m_memory; };

		// Get the end of view - the iterator next of last element, which may not be dereferenced.
		inline Iterator GetEnd()					{ return m_memory + m_length; };

		// Get the end of view - the iterator next of last element, which may not be dereferenced.
		inline ConstIterator GetEnd() const			{ return m_memory + m_length; };

		// Get the memory of managed buffer.
		inline ValuePointer GetMemory()				{ return m_memory; };

		// Get the view data.
		inline ConstValuePointer GetMemory() const	{ return m_memory; };

		// Get the length of view.
		inline const size_t GetLength() const		{ return m_length; };

		// Get the capacity of vector.
		inline const size_t GetCapacity() const		{ return m_capacity; };

		// Get the number of bytes the elements of view stored.
		inline const size_t GetUsedBytes() const	{ return m_length * VALUE_SIZE; };

	// Private interface.
	private:
		// Construct the desired amount of additional elements, using the construction arguments.
		template< typename... TArguments >
		inline void ConstructValues( const size_t length, const TArguments&... arguments );

		// Copy the elements.
		inline void CopyValues( ConstValuePointer elements, const size_t elements_length );

	private:
		TValue*	m_memory	= nullptr;	// Stored elements.
		size_t	m_capacity	= 0;		// Number of elements available for currently allocated memory.
		size_t	m_length	= 0;		// Number of currently allocated elements.
	};
}


	/**
	*/
	template< typename TValue >
	class PlainVector final : public Black::StandardDynamicArrayFacade<Internal::PlainVector<TValue>>
	{
	// Public aliases.
	public:
		using typename Internal::PlainVector<TValue>::ConstValuePointer;


		using Internal::PlainVector<TValue>::GetValueAt;
		using Internal::PlainVector<TValue>::IsEmpty;
		using Internal::PlainVector<TValue>::GetMemory;
		using Internal::PlainVector<TValue>::GetCapacity;
		using Internal::PlainVector<TValue>::GetLength;

	// Public lifetime management.
	public:
		using Black::StandardDynamicArrayFacade<Internal::PlainVector<TValue>>::StandardDynamicArrayFacade;


		PlainVector( ConstValuePointer elements, const size_t length ) : PlainVector{ elements, elements + length } {};
		PlainVector( std::initializer_list<TValue> elements ) : PlainVector{ elements.begin(), elements.end() } {};

		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		explicit PlainVector( PlainView<TOtherValue> elements ) : PlainVector( elements.GetBegin(), elements.GetEnd() ) {};

		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		explicit PlainVector( PlainView<const TOtherValue> elements ) : PlainVector( elements.GetBegin(), elements.GetEnd() ) {};

		template< typename TOtherValue, size_t ARRAY_LENGTH, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		explicit PlainVector( TOtherValue elements[ ARRAY_LENGTH ] ) : PlainVector( elements, ARRAY_LENGTH ) {};

		template< typename TOtherValue, size_t ARRAY_LENGTH, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		explicit PlainVector( const std::array<TOtherValue, ARRAY_LENGTH>& elements ) : PlainVector( elements.data(), ARRAY_LENGTH ) {};

		template< typename TOtherValue, typename TAllocator, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		explicit PlainVector( const std::vector<TOtherValue, TAllocator>& elements ) : PlainVector( elements.data(), elements.size() ) {};


		inline PlainVector& operator = ( std::initializer_list<TValue> elements )					{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainVector& operator = ( PlainView<TOtherValue> elements )							{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainVector& operator = ( PlainView<const TOtherValue> elements )					{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherValue, size_t ARRAY_LENGTH, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainVector& operator = ( TOtherValue elements[ ARRAY_LENGTH ] )						{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherValue, size_t ARRAY_LENGTH, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainVector& operator = ( const std::array<TOtherValue, ARRAY_LENGTH>& elements )	{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherValue, typename TAllocator, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainVector& operator = ( const std::vector<TOtherValue, TAllocator>& elements )		{ return CopyAndSwap( *this, elements ); };

	// Public interface.
	public:
		inline TValue& operator [] ( const size_t index )				{ return GetValueAt( index ); };
		inline const TValue& operator [] ( const size_t index ) const	{ return GetValueAt( index ); };


		inline operator PlainView<TValue> ()				{ return { GetMemory(), GetLength() }; };
		inline operator PlainView<const TValue> () const	{ return { GetMemory(), GetLength() }; };


		inline explicit operator const bool () const	{ return !IsEmpty(); };
		inline const bool operator ! () const			{ return IsEmpty(); };
	};
}
}
}
}
