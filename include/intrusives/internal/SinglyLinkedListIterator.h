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
		// Shift the iterator to next slot in list.
		void ShiftNext();


		// Get the current slot.
		inline SinglyLinkedListSlot* GetCurrentSlot() const	{ return m_current_slot; };


		// Whether the iterator still valid.
		inline const bool IsValid() const					{ return m_current_slot != nullptr; };


		inline SinglyLinkedListSlot* operator -> () const	{ return m_current_slot; };

	// Private state.
	private:
		SinglyLinkedListSlot* m_current_slot = nullptr; // Currently observed slot in list.
	};
}
}
}
}
