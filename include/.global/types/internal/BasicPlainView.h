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
		@brief	Plain view implementation.

		Views are containers of unowned memory. Views only refers to contiguous block of memory where the types values are stored.
		Typically, the view represents the part of some buffer.
		View can refer to memory of mutable or constant values.

		@tparam	TBalue	Type of values in view.
	*/
	template< typename TValue >
	class BasicPlainView
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

	// Construction interface.
	public:
		inline BasicPlainView()							= default;
		inline BasicPlainView( const BasicPlainView& )	= default;

		inline BasicPlainView( BasicPlainView&& other ) noexcept;
		inline BasicPlainView( ValuePointer memory, const size_t length );


		inline BasicPlainView& operator = ( const BasicPlainView& ) = default;
		inline BasicPlainView& operator = ( BasicPlainView&& other ) noexcept;

	// Public interface.
	public:
		// Invalidate the view making it empty.
		inline void Invalidate();


		// Swap the content of views.
		inline void Swap( BasicPlainView& other );


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
}
}
}
}
