#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
inline namespace List
{
	/**
		@brief	Regular iterator for intrusive list.
	*/
	template< typename TValue, typename TTraits >
	class ListIterator final
	{
	// Friendship declarations.
	public:
		// Grant access to private state.
		friend class BasicIntrusiveList<TValue, TTraits>;

	// STL-complaint inner types.
	public:
		// Regular difference type.
		using difference_type = ptrdiff_t;

		// Viewed value.
		using value_type = TValue;

		// Pointer to viewed value.
		using pointer = TValue*;

		// Reference to viewed value.
		using reference = TValue&;

		// Category of iterator.
		using iterator_category = std::bidirectional_iterator_tag;

	// Lifetime management.
	public:
		inline ListIterator()						= default;
		inline ListIterator( const ListIterator& )	= default;
		inline ListIterator( ListIterator&& )		= default;
		inline ~ListIterator()						= default;


		inline ListIterator& operator = ( const ListIterator& )	= default;
		inline ListIterator& operator = ( ListIterator&& )		= default;

	// Public interface.
	public:
		inline ListIterator& operator ++ ();
		inline ListIterator operator ++ ( int );

		inline ListIterator& operator -- ();
		inline ListIterator operator -- ( int );

		inline TValue& operator * () const;
		inline TValue* operator -> () const;

		inline const bool operator == ( const ListIterator& other ) const;
		inline const bool operator != ( const ListIterator& other ) const;

	// Private lifetime management.
	private:
		inline explicit ListIterator( DoublyLinkedListCursor cursor );

	// Private state.
	private:
		DoublyLinkedListCursor m_cursor; // Cursor for inner list.
	};
}
}
}
}
}
