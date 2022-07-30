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
		@brief	Intrusive doubly-linked list.
	*/
	class DoublyLinkedList final : private Black::NonCopyable
	{
	// Friendship declarations.
	public:
		// Grand access to private interface.
		friend class DoublyLinkedListSlot;

	// Public inner types.
	public:
		// Regular slot of list.
		using Slot = DoublyLinkedListSlot;

		// Regular iterator of list.
		using Iterator = DoublyLinkedListIterator;

	// Lifetime management.
	public:
		DoublyLinkedList() = default;

		DoublyLinkedList( DoublyLinkedList&& other ) noexcept;
		~DoublyLinkedList() noexcept;


		DoublyLinkedList& operator = ( DoublyLinkedList&& other ) noexcept;

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

		// Insert the slot before the given iterator. Expects the iterator is valid. Previous link of slot will be resolved safely.
		void InsertBefore( Iterator position, Slot& slot );

		// Erase the slot by given iterator. Expects the iterator is valid.
		void Erase( Iterator position );


		// Get the slot at the head of list. Expects that list is not empty.
		Slot& GetFrontSlot() const;

		// Get the slot at the tail of list. Expects that list is not empty.
		Slot& GetBackSlot() const;

		// Get the iterator to beginning of list. May return invalid iterator.
		inline Iterator GetBegin() const		{ return Iterator{ m_head }; };

		// Get the iterator to ending of list. Always return invalid iterator.
		inline Iterator GetEnd() const			{ return Iterator{ &m_end }; };


		// Get the size of list.
		inline const size_t GetSize() const		{ return m_size; };


		// Whether the list is empty or not.
		inline const bool IsEmpty() const		{ return m_head == &m_end; };

	// Private state.
	private:
		DoublyLinkedListSlot*	m_head	= &m_end;		// The first hosted slot
		size_t					m_size	= 0;			// Count of hosted slots.

	// Private non-state.
	private:
		mutable DoublyLinkedListSlot	m_end{ *this };	// The end of list, the element after the tail.
	};
}
}
}
}
