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
		@brief	Intrusive singly-linked list.
	*/
	class SinglyLinkedList final : private Black::NonCopyable
	{
	// Friendship declarations.
	public:
		// Grand access to private interface.
		friend class SinglyLinkedListSlot;

	// Public inner types.
	public:
		// Regular slot of list.
		using Slot = SinglyLinkedListSlot;

		// Regular iterator of list.
		using Iterator = SinglyLinkedListIterator;

	// Lifetime management.
	public:
		SinglyLinkedList() = default;

		SinglyLinkedList( SinglyLinkedList&& other ) noexcept;
		~SinglyLinkedList() noexcept;


		SinglyLinkedList& operator = ( SinglyLinkedList&& other ) noexcept;

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
		inline Iterator GetEnd() const			{ return {}; };


		// Get the size of list.
		inline const size_t GetSize() const		{ return m_size; };


		// Whether the list is empty or not.
		inline const bool IsEmpty() const		{ return m_head == nullptr; };

	// Private interface.
	private:
		// Find the position that precedes the given one.
		Iterator FindPositionBefore( Iterator position ) const;

	// Private state.
	private:
		SinglyLinkedListSlot*	m_head	= nullptr;	// The first hosted slot.
		SinglyLinkedListSlot*	m_tail	= nullptr;	// The last hosted slot.
		size_t					m_size	= 0;		// Count of hosted slots.
	};
}
}
}
}
