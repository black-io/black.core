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
		@brief	Regular cursor for intrusive singly-linked list.
	*/
	class SinglyLinkedListCursor final
	{
	// Lifetime management.
	public:
		SinglyLinkedListCursor()										= default;
		SinglyLinkedListCursor( const SinglyLinkedListCursor& other )	= default;
		~SinglyLinkedListCursor() noexcept								= default;

		SinglyLinkedListCursor( SinglyLinkedListCursor&& other ) noexcept;
		explicit SinglyLinkedListCursor( SinglyLinkedListSlot* slot ) noexcept;


		SinglyLinkedListCursor& operator = ( const SinglyLinkedListCursor& other )	= default;

		SinglyLinkedListCursor& operator = ( SinglyLinkedListCursor&& other ) noexcept;

	// Public interface.
	public:
		// Shift the cursor to next slot in list. Expects that the slot is valid.
		void ShiftNext();


		// Whether the cursor still valid.
		const bool IsValid() const;

		// Whether the cursor points to end of list.
		const bool IsEnd() const;


		// Get the current slot. Expects that the slot is valid.
		SinglyLinkedListSlot& GetSlot() const;

		// Get the current slot.
		inline SinglyLinkedListSlot* QuerySlot() const		{ return m_slot; };


		inline SinglyLinkedListSlot& operator * () const	{ return GetSlot(); };
		inline SinglyLinkedListSlot* operator -> () const	{ return &GetSlot(); };

	// Private state.
	private:
		SinglyLinkedListSlot* m_slot = nullptr; // Currently observed slot in list.
	};
}
}
}
}
}
