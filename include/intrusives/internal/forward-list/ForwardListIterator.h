#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
inline namespace ForwardList
{
	/**
		@brief	Regular iterator for intrusive forward list.
	*/
	template< typename TValue, typename TTraits >
	class ForwardListIterator final
	{
	// Friendship declarations.
	public:
		// Grant access to private state.
		friend class BasicIntrusiveForwardList<TValue, TTraits>;

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
		using iterator_category = std::forward_iterator_tag;

	// Lifetime management.
	public:
		inline ForwardListIterator()									= default;
		inline ForwardListIterator( const ForwardListIterator& )		= default;
		inline ForwardListIterator( ForwardListIterator&& ) noexcept	= default;
		inline ~ForwardListIterator() noexcept							= default;


		inline ForwardListIterator& operator = ( const ForwardListIterator& )		= default;
		inline ForwardListIterator& operator = ( ForwardListIterator&& ) noexcept	= default;

	// Public interface.
	public:
		inline ForwardListIterator& operator ++ ();
		inline ForwardListIterator operator ++ ( int );

		inline TValue& operator * () const;
		inline TValue* operator -> () const;

		inline const bool operator == ( const ForwardListIterator& other ) const;
		inline const bool operator != ( const ForwardListIterator& other ) const;

	// Private lifetime management.
	private:
		inline explicit ForwardListIterator( SinglyLinkedListCursor cursor );

	// Private state.
	private:
		SinglyLinkedListCursor m_cursor; // Cursor for inner list.
	};
}
}
}
}
}
