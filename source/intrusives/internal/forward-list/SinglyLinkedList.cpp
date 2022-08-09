#include <black/core/intrusives.h>


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
namespace
{
	// Logging channel.
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/SinglyLinkedList";
}


	SinglyLinkedList::SinglyLinkedList( SinglyLinkedList&& other ) noexcept
		: m_head{ std::exchange( other.m_head, &other.m_end ) }
		, m_size{ std::exchange( other.m_size, 0 ) }
	{
		EXPECTS_DEBUG( m_head != nullptr );
		if( m_head == &other.m_end )
		{
			// Empty list moved.
			m_head = &m_end;
			return;
		}

		Slot* tail = m_head;

		// Update the link to hosted list for each slot.
		for( Slot* slot = m_head; slot != &other.m_end; slot = slot->m_next )
		{
			ENSURES_DEBUG( slot != nullptr );
			slot->m_host = this;

			tail = slot;
		}

		// Update the tail slot to link with new end slot.
		tail->m_next = &m_end;
	}

	SinglyLinkedList::~SinglyLinkedList() noexcept
	{
		Clear();
	}

	void SinglyLinkedList::Clear()
	{
		CRET( IsEmpty() );

		EXPECTS_DEBUG( m_head != nullptr );
		while( !IsEmpty() )
		{
			Slot* slot = std::exchange( m_head, m_head->m_next );
			EXPECTS_DEBUG( m_head != nullptr );

			slot->Reset();
		}

		m_size = 0;
	}

	void SinglyLinkedList::PushFront( Slot& slot )
	{
		slot.Detach();

		slot.m_host	= this;
		slot.m_next	= std::exchange( m_head, &slot );

		++m_size;
	}

	void SinglyLinkedList::PopFront()
	{
		EXPECTS( !IsEmpty() );

		Slot* slot = std::exchange( m_head, m_head->m_next );
		slot->Reset();

		EXPECTS_DEBUG( m_size > 0 );
		--m_size;
	}

	void SinglyLinkedList::InsertAfter( Cursor position, Slot& slot )
	{
		EXPECTS_DEBUG( !IsEmpty() );
		EXPECTS_DEBUG( position.IsValid() );
		EXPECTS_DEBUG( position->m_host == this );

		slot.Detach();

		Slot* const slot_before = position.QuerySlot();

		slot.m_host	= this;
		slot.m_next	= std::exchange( slot_before->m_next, &slot );

		++m_size;
	}

	void SinglyLinkedList::EraseAfter( Cursor position )
	{
		EXPECTS_DEBUG( !IsEmpty() );
		EXPECTS_DEBUG( position.IsValid() );
		EXPECTS_DEBUG( position->m_host == this );

		Slot* const slot	= position->m_next;
		ENSURES_DEBUG( !slot->IsEndSlot() );

		position->m_next	= slot->m_next;
		slot->Reset();

		EXPECTS_DEBUG( m_size > 0 );
		--m_size;
	}

	SinglyLinkedList::Slot& SinglyLinkedList::GetFrontSlot() const
	{
		EXPECTS_DEBUG( m_head != nullptr );
		return *m_head;
	}

	void SinglyLinkedList::InsertInstead( Slot& old_slot, Slot& new_slot )
	{
		Slot* const slot_after = old_slot.m_next;

		new_slot.m_host	= this;
		new_slot.m_next	= slot_after;

		if( &old_slot == m_head )
		{
			m_head = &new_slot;
		}
		else
		{
			Slot& slot_before	= FindSlotBefore( old_slot );
			slot_before.m_next	= &new_slot;
		}

		old_slot.Reset();
	}

	void SinglyLinkedList::Erase( Slot& slot )
	{
		Slot* const slot_after	= slot.m_next;

		if( &slot == m_head )
		{
			m_head = slot_after;
		}
		else
		{
			Slot& slot_before	= FindSlotBefore( slot );
			slot_before.m_next	= slot_after;
		}

		slot.Reset();

		EXPECTS_DEBUG( m_size > 0 );
		--m_size;
	}

	SinglyLinkedList::Slot& SinglyLinkedList::FindSlotBefore( Slot& slot ) const
	{
		EXPECTS_DEBUG( !slot.IsEndSlot() );

		Cursor preceder{ GetBegin() };
		while( preceder->m_next != &slot )
		{
			preceder.ShiftNext();
		}

		return *preceder;
	}
}
}
}
}
