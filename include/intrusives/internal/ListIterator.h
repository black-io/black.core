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
	class ListIterator final
	{
	// Friendship declarations.
	public:
		// Grant access to private state.
		friend class BasicIntrusiveList<TValue, SLOT_POINTER>;

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

		inline const TValue& operator * () const;
		inline const TValue* operator -> () const;

		inline const bool operator == ( const ListIterator& other ) const;
		inline const bool operator != ( const ListIterator& other ) const;


		inline operator ListConstIterator<TValue, SLOT_POINTER>() const { return ListConstIterator<TValue, SLOT_POINTER>{ m_iterator }; };

	// Private inner types.
	private:
		// Traits for intrusive operations.
		using Traits = IntrusiveTraits<TValue, Black::IntrusiveListSlot, SLOT_POINTER>;

	// Private lifetime management.
	private:
		inline explicit ListIterator( DoublyLinkedListIterator iterator );

	// Private state.
	private:
		DoublyLinkedListIterator m_iterator; // Regular iterator for inner list type.
	};
}
}
}
}
