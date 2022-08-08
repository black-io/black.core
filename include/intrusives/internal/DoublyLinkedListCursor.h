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
		@brief	Regular cursor for intrusive doubly-linked list.
	*/
	class DoublyLinkedListCursor final
	{
	// Lifetime management.
	public:
		DoublyLinkedListCursor()										= default;
		DoublyLinkedListCursor( const DoublyLinkedListCursor& other )	= default;
		~DoublyLinkedListCursor() noexcept								= default;

		DoublyLinkedListCursor( DoublyLinkedListCursor&& other ) noexcept;
		explicit DoublyLinkedListCursor( DoublyLinkedListSlot* slot ) noexcept;


		DoublyLinkedListCursor& operator = ( const DoublyLinkedListCursor& other )	= default;

		DoublyLinkedListCursor& operator = ( DoublyLinkedListCursor&& other ) noexcept;

	// Public interface.
	public:
		// Shift the cursor to previous slot in list.
		void ShiftBack();

		// Shift the cursor to next slot in list.
		void ShiftNext();


		// Whether the cursor still valid.
		const bool IsValid() const;

		// Whether the cursor points to end of list.
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
