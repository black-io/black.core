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
		@brief	Intrusive doubly-linked list.
	*/
	class DoublyLinkedList : private Black::NonCopyable
	{
	// Friendship declarations.
	public:
		// Grand access to private interface.
		friend class DoublyLinkedListSlot;

	// Public inner types.
	public:
		// Regular slot of list.
		using Slot = DoublyLinkedListSlot;

		// Regular cursor of list.
		using Cursor = DoublyLinkedListCursor;

	// Lifetime management.
	public:
		DoublyLinkedList() = default;

		DoublyLinkedList( DoublyLinkedList&& other ) noexcept;
		~DoublyLinkedList() noexcept;

	// Public interface.
	public:
		// Clear the list and unlink all hosted slots.
		void Clear();


		// Add the slot as new head. Previous link of slot will be resolved safely.
		void PushFront( Slot& slot );

		// Remove the current head slot from list. Expects that list is not empty.
		void PopFront();

		// Add the slot as new tail. Previous link of slot will be resolved safely.
		void PushBack( Slot& slot );

		// Remove the current tail from list. Expects that list is not empty.
		void PopBack();

		// Insert the slot before the given position. Expects the position is valid. Previous link of slot will be resolved safely.
		void Insert( Cursor position, Slot& slot );

		// Erase the slot at given position. Expects the position is valid.
		void Erase( Cursor position );


		// Get the slot at the head of list. Expects that list is not empty.
		Slot& GetFrontSlot() const;

		// Get the slot at the tail of list. Expects that list is not empty.
		Slot& GetBackSlot() const;

		// Get the cursor to beginning of list. May return invalid cursor.
		inline Cursor GetBegin() const			{ return Cursor{ m_head }; };

		// Get the cursor to ending of list. Always return invalid cursor.
		inline Cursor GetEnd() const			{ return Cursor{ &m_end }; };


		// Get the size of list.
		inline const size_t GetLength() const	{ return m_length; };


		// Whether the list is empty or not.
		inline const bool IsEmpty() const		{ return m_head == &m_end; };

	// Private interface.
	private:
		// Insert the new slot instead of given old.
		void InsertInstead( Slot& old_slot, Slot& new_slot );

		// Erase the slot from list.
		void Erase( Slot& slot );

	// Private state.
	private:
		DoublyLinkedListSlot*	m_head		= &m_end;	// The first hosted slot
		size_t					m_length	= 0;		// Count of hosted slots.

	// Private non-state.
	private:
		mutable DoublyLinkedListSlot	m_end{ *this };	// The end of list, the element after the tail.
	};
}
}
}
}
}
