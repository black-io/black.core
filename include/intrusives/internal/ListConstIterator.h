#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
	/**
	*/
	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	class ListConstIterator final
	{
	// Friendship declarations.
	public:
		// Grant access to private state.
		friend class BasicIntrusiveList<TValue, SLOT_POINTER>;

		// Grant access to private state and constructor.
		friend class ListIterator<TValue, SLOT_POINTER>;

	// STL-complaint inner types.
	public:
		// Regular difference type.
		using difference_type = ptrdiff_t;

		// Viewed value.
		using value_type = const TValue;

		// Pointer to viewed value.
		using pointer = const TValue*;

		// Reference to viewed value.
		using reference = const TValue&;

		// Category of iterator.
		using iterator_category = std::bidirectional_iterator_tag;

	// Lifetime management.
	public:
		inline ListConstIterator()								= default;
		inline ListConstIterator( const ListConstIterator& )	= default;
		inline ListConstIterator( ListConstIterator&& )			= default;
		inline ~ListConstIterator()								= default;


		inline ListConstIterator& operator = ( const ListConstIterator& )	= default;
		inline ListConstIterator& operator = ( ListConstIterator&& )		= default;

	// Public interface.
	public:
		inline ListConstIterator& operator ++ ();
		inline ListConstIterator operator ++ ( int );

		inline ListConstIterator& operator -- ();
		inline ListConstIterator operator -- ( int );

		inline const TValue& operator * () const;
		inline const TValue* operator -> () const;

		inline const bool operator == ( const ListConstIterator& other ) const;
		inline const bool operator != ( const ListConstIterator& other ) const;

	// Private inner types.
	private:
		// Traits for intrusive operations.
		using Traits = IntrusiveTraits<TValue, Black::IntrusiveListSlot, SLOT_POINTER>;

	// Private lifetime management.
	private:
		inline explicit ListConstIterator( DoublyLinkedListCursor cursor );

	// Private state.
	private:
		DoublyLinkedListCursor m_cursor; // Cursor for inner list.
	};
}
}
}
}
