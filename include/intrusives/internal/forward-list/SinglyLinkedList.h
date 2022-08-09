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
		@brief	Intrusive singly-linked list.
	*/
	class SinglyLinkedList : private Black::NonCopyable
	{
	// Friendship declarations.
	public:
		// Grand access to private interface.
		friend class SinglyLinkedListSlot;

	// Public inner types.
	public:
		// Regular slot of list.
		using Slot = SinglyLinkedListSlot;

		// Regular cursor of list.
		using Cursor = SinglyLinkedListCursor;

	// Lifetime management.
	public:
		SinglyLinkedList() = default;

		SinglyLinkedList( SinglyLinkedList&& other ) noexcept;
		~SinglyLinkedList() noexcept;

	// Public interface.
	public:
		// Clear the list and unlink all hosted slots.
		void Clear();


		// Add the slot as new head. Previous link of slot will be resolved safely.
		void PushFront( Slot& slot );

		// Remove the current head slot from list. Expects that list is not empty.
		void PopFront();

		// Insert the slot after the given position. Expects the position is valid. Previous link of slot will be resolved safely.
		void InsertAfter( Cursor position, Slot& slot );

		// Erase the slot after given position. Expects the position is valid.
		void EraseAfter( Cursor position );


		// Get the slot at the head of list. Expects that list is not empty.
		Slot& GetFrontSlot() const;

		// Get the cursor to beginning of list. May return invalid cursor.
		inline Cursor GetBegin() const			{ return Cursor{ m_head }; };

		// Get the cursor to ending of list. Always return invalid cursor.
		inline Cursor GetEnd() const			{ return Cursor{ &m_end }; };


		// Get the size of list.
		inline const size_t GetSize() const		{ return m_size; };


		// Whether the list is empty or not.
		inline const bool IsEmpty() const		{ return m_head == &m_end; };

	// Private interface.
	private:
		// Insert the new slot instead of given old.
		void InsertInstead( Slot& old_slot, Slot& new_slot );

		// Erase the slot from list.
		void Erase( Slot& slot );


		// Find the slot that precedes the given one.
		Slot& FindSlotBefore( Slot& slot ) const;

	// Private state.
	private:
		SinglyLinkedListSlot*	m_head	= &m_end;		// The first hosted slot.
		size_t					m_size	= 0;			// Count of hosted slots.

	// Private non-state.
	private:
		mutable SinglyLinkedListSlot	m_end{ *this };	// The end of list.
	};
}
}
}
}
}
