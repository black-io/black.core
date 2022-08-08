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
		@brief	Regular iterator for intrusive singly-linked list.
	*/
	class SinglyLinkedListIterator final
	{
	// Lifetime management.
	public:
		SinglyLinkedListIterator()											= default;
		SinglyLinkedListIterator( const SinglyLinkedListIterator& other )	= default;
		~SinglyLinkedListIterator() noexcept								= default;

		SinglyLinkedListIterator( SinglyLinkedListIterator&& other ) noexcept;
		explicit SinglyLinkedListIterator( SinglyLinkedListSlot* slot ) noexcept;


		SinglyLinkedListIterator& operator = ( const SinglyLinkedListIterator& other )	= default;

		SinglyLinkedListIterator& operator = ( SinglyLinkedListIterator&& other ) noexcept;

	// Public interface.
	public:
		// Shift the iterator to next slot in list. Expects that the slot is valid.
		void ShiftNext();


		// Whether the iterator still valid.
		const bool IsValid() const;

		// Whether the iterator points to end of list.
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
