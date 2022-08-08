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

		Such slots - are the main point of intrusive collections.
		The target class, which should be used as value of intrusive collection, should store the field with this type.
		Such field is used by intrusive collection to store the value of target class.
	*/
	class SinglyLinkedListSlot final : private Black::NonCopyable
	{
	// Friendship declarations.
	public:
		// Grant the access to private interface.
		friend class SinglyLinkedListCursor;

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

	// Private lifetime management.
	private:
		explicit SinglyLinkedListSlot( SinglyLinkedList& host );

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
		SinglyLinkedList*		m_host	= nullptr;	// The host list of slot.
		SinglyLinkedListSlot*	m_next	= nullptr;	// The slot hosted after this.
	};
}
}
}
}
