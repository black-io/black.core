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
		@brief	Regular iterator for constant forward list.
	*/
	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	class ForwardListIterator final
	{
	// Friendship declarations.
	public:
		// Grant access to private state.
		friend class BasicIntrusiveForwardList<TValue, SLOT_POINTER>;

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
		inline ForwardListIterator()								= default;
		inline ForwardListIterator( const ForwardListIterator& )	= default;
		inline ForwardListIterator( ForwardListIterator&& )			= default;
		inline ~ForwardListIterator()								= default;


		inline ForwardListIterator& operator = ( const ForwardListIterator& )	= default;
		inline ForwardListIterator& operator = ( ForwardListIterator&& )		= default;

	// Public interface.
	public:
		inline ForwardListIterator& operator ++ ();
		inline ForwardListIterator operator ++ ( int );

		inline TValue& operator * () const;
		inline TValue* operator -> () const;

		inline const bool operator == ( const ForwardListIterator& other ) const;
		inline const bool operator != ( const ForwardListIterator& other ) const;


		inline operator ForwardListConstIterator<TValue, SLOT_POINTER>() const { return ForwardListConstIterator<TValue, SLOT_POINTER>{ m_cursor }; };

	// Private inner types.
	private:
		// Traits for intrusive operations.
		using Traits = IntrusiveTraits<TValue, Black::IntrusiveForwardListSlot, SLOT_POINTER>;

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
