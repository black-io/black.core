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
		@brief	Plain vector implementation.

		Plain vector implements the trivial dynamic array functionality to allow easy usage of dynamic size buffers.
		Plain vectors can store only values of trivial types. `std::vector` should be used for types with invariant.

		@tparam	TValue	Type of stored value.
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
}
}
}
}
