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
		@brief	Element slot for intrusive doubly-linked list.

		Such slots - are the main point of intrusive collections.
		The target class, which should be used as value of intrusive collection, should store the field with this type.
		Such field is used by intrusive collection to store the value of target class.
	*/
	class DoublyLinkedListSlot final : private Black::NonCopyable
	{
	// Friendship declarations.
	public:
		// Grant the access to private interface.
		friend class DoublyLinkedListIterator;

		// Grant the access to private interface.
		friend class DoublyLinkedList;

	// Lifetime management.
	public:
		DoublyLinkedListSlot() = default;

		DoublyLinkedListSlot( DoublyLinkedListSlot&& other ) noexcept;
		~DoublyLinkedListSlot() noexcept;


		DoublyLinkedListSlot& operator = ( DoublyLinkedListSlot&& other ) noexcept;

	// Public interface.
	public:
		// Query the list where the slot is attached. May return `nullptr`.
		inline DoublyLinkedList* QueryHost()				{ return m_host; };

		// Query the list where the slot is attached. May return `nullptr`.
		inline const DoublyLinkedList* QueryHost() const	{ return m_host; };


		// Whether the slot is attached to list.
		inline const bool IsAttached() const				{ return m_host != nullptr; };

	// Private lifetime management.
	private:
		explicit DoublyLinkedListSlot( DoublyLinkedList& host );

	// Private interface.
	private:
		// Reset the state of slot.
		void Reset();

		// Perform the detaching from host list.
		void Detach();


		// Whether the slot implies the end of list.
		const bool IsEndSlot() const;

	// Private state.
	private:
		DoublyLinkedList*		m_host		= nullptr;	// The host list of slot.
		DoublyLinkedListSlot*	m_previous	= nullptr;	// The slot hosted before this.
		DoublyLinkedListSlot*	m_next		= nullptr;	// The slot hosted after this.
	};
}
}
}
}
