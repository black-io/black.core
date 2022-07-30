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
		@brief	Element slot for intrusive singly-linked list.
	*/
	class SinglyLinkedListSlot final : private Black::NonCopyable
	{
	// Friendship declarations.
	public:
		// Grant the access to private interface.
		friend class SinglyLinkedListIterator;

		// Grant the access to private interface.
		friend class SinglyLinkedList;

	// Lifetime management.
	public:
		SinglyLinkedListSlot() = default;

		SinglyLinkedListSlot( SinglyLinkedListSlot&& other ) noexcept;
		~SinglyLinkedListSlot() noexcept;


		SinglyLinkedListSlot& operator = ( SinglyLinkedListSlot&& other ) noexcept;

	// Public interface.
	public:
		// Query the list where the slot is attached. May return `nullptr`.
		inline SinglyLinkedList* QueryHost()				{ return m_host; };

		// Query the list where the slot is attached. May return `nullptr`.
		inline const SinglyLinkedList* QueryHost() const	{ return m_host; };


		// Whether the slot is attached to list.
		inline const bool IsAttached() const				{ return m_host != nullptr; };

	// Private interface.
	private:
		// Perform the detaching from host list.
		void Detach();

	// Private state.
	private:
		SinglyLinkedList*		m_host	= nullptr;	// The host list of slot.
		SinglyLinkedListSlot*	m_next	= nullptr;	// The slot hosted after this.
	};
}
}
}
}
