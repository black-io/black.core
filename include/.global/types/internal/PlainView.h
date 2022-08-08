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
}
}
}
}
