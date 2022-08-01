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
		@brief	Regular iterator for intrusive doubly-linked list.
	*/
	class DoublyLinkedListIterator final
	{
	// Lifetime management.
	public:
		DoublyLinkedListIterator()											= default;
		DoublyLinkedListIterator( const DoublyLinkedListIterator& other )	= default;
		~DoublyLinkedListIterator() noexcept								= default;

		DoublyLinkedListIterator( DoublyLinkedListIterator&& other ) noexcept;
		explicit DoublyLinkedListIterator( DoublyLinkedListSlot* slot ) noexcept;


		DoublyLinkedListIterator& operator = ( const DoublyLinkedListIterator& other )	= default;

		DoublyLinkedListIterator& operator = ( DoublyLinkedListIterator&& other ) noexcept;

	// Public interface.
	public:
		// Shift the iterator to previous slot in list.
		void ShiftBack();

		// Shift the iterator to next slot in list.
		void ShiftNext();


		// Whether the iterator still valid.
		const bool IsValid() const;

		// Whether the iterator points to end of list.
		const bool IsEnd() const;


		// Get the current slot. Expects that the slot is valid.
		DoublyLinkedListSlot& GetSlot() const;

		// Get the current slot.
		inline DoublyLinkedListSlot* QuerySlot() const		{ return m_slot; };


		inline DoublyLinkedListSlot& operator * () const	{ return GetSlot(); };
		inline DoublyLinkedListSlot* operator -> () const	{ return &GetSlot(); };

	// Private state.
	private:
		DoublyLinkedListSlot* m_slot = nullptr; // Currently observed slot in list.
	};
}
}
}
}
