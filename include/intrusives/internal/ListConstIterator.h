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
		friend class Black::IntrusiveList<TValue, SLOT_POINTER>;

		// Grant access to private state and constructor.
		friend class ListIterator<TValue, SLOT_POINTER>;

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
		inline explicit ListConstIterator( DoublyLinkedListIterator iterator );

	// Private state.
	private:
		DoublyLinkedListIterator m_iterator; // Regular iterator for inner list type.
	};
}
}
}
}
