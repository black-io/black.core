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
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/DoublyLinkedList";
}


	DoublyLinkedList::DoublyLinkedList( DoublyLinkedList&& other ) noexcept
		: m_head{ std::exchange( other.m_head, &other.m_end ) }
		, m_size{ std::exchange( other.m_size, 0 ) }
		, m_end{ std::move( other.m_end ) }
	{
		EXPECTS_DEBUG( m_head != nullptr );
		if( m_head == &other.m_end )
		{
			// Empty list moved.
			m_head = &m_end;
			ENSURES_DEBUG( m_end.m_previous == nullptr );
		}
		else
		{
			// Update the tail slot to link with new end slot.
			m_end.m_previous->m_next = &m_end;
		}
		ENSURES_DEBUG( m_end.m_next == nullptr );

		// Update the link to hosted list for each slot.
		for( Slot* slot = m_head; slot != nullptr; slot = slot->m_next )
		{
			slot->m_host = this;
		}
	}

	DoublyLinkedList::~DoublyLinkedList() noexcept
	{
		Clear();
	}

	DoublyLinkedList& DoublyLinkedList::operator=( DoublyLinkedList&& other ) noexcept
	{
		// End the lifetime of current list.
		DoublyLinkedList::~DoublyLinkedList();

		// Start the lifetime of new list by moving the given `other`.
		return *new( this ) DoublyLinkedList{ std::move( other ) };
	}

	void DoublyLinkedList::Clear()
	{
		CRET( IsEmpty() );

		EXPECTS_DEBUG( m_head != nullptr );
		while( !IsEmpty() )
		{
			Slot* slot = std::exchange( m_head, m_head->m_next );
			EXPECTS_DEBUG( m_head != nullptr );

			m_head->m_previous	= nullptr;
			slot->m_host		= nullptr;
			slot->m_next		= nullptr;
			ENSURES_DEBUG( slot->m_previous == nullptr );
		}

		m_size = 0;
	}

	void DoublyLinkedList::PushFront( Slot& slot )
	{
		slot.Detach();
		ENSURES_DEBUG( slot.m_previous == nullptr );

		slot.m_host				= this;
		slot.m_next				= std::exchange( m_head, &slot );
		slot.m_next->m_previous	= &slot;

		++m_size;
	}

	void DoublyLinkedList::PopFront()
	{
		EXPECTS( !IsEmpty() );

		Slot* slot = std::exchange( m_head, m_head->m_next );

		slot->m_host		= nullptr;
		slot->m_next		= nullptr;
		m_head->m_previous	= nullptr;

		EXPECTS_DEBUG( m_size > 0 );
		--m_size;
	}

	void DoublyLinkedList::PushBack( Slot& slot )
	{
		if( IsEmpty() )
		{
			PushFront( slot );
			return;
		}

		slot.Detach();

		Slot* tail			= m_end.m_previous;
		tail->m_next		= &slot;
		slot.m_previous		= tail;
		slot.m_host			= this;
		slot.m_next			= &m_end;
		m_end.m_previous	= &slot;

		++m_size;
	}

	void DoublyLinkedList::PopBack()
	{
		EXPECTS( !IsEmpty() );

		if( m_head == m_end.m_previous )
		{
			PopFront();
			return;
		}

		Slot* tail					= m_end.m_previous;
		tail->m_previous->m_next	= tail->m_next;
		tail->m_next->m_previous	= tail->m_previous;
		tail->m_host				= nullptr;
		tail->m_previous			= nullptr;
		tail->m_next				= nullptr;

		EXPECTS_DEBUG( m_size > 0 );
		--m_size;
	}

	void DoublyLinkedList::InsertBefore( Iterator position, Slot& slot )
	{
		if( position.IsEnd() )
		{
			PushBack( slot );
			return;
		}

		EXPECTS_DEBUG( position.IsValid() );
		EXPECTS_DEBUG( position->m_host == this );

		if( position.GetCurrentSlot() == m_head )
		{
			PushFront( slot );
			return;
		}

		slot.Detach();

		Slot* pre_position		= position->m_previous;
		pre_position->m_next	= &slot;
		slot.m_previous			= pre_position;
		slot.m_host				= this;
		slot.m_next				= position.GetCurrentSlot();
		position->m_previous	= &slot;

		++m_size;
	}

	void DoublyLinkedList::Erase( Iterator position )
	{
		EXPECTS_DEBUG( position.IsValid() );
		EXPECTS_DEBUG( !IsEmpty() );
		EXPECTS_DEBUG( position->m_host == this );

		if( position.GetCurrentSlot() == m_end.m_previous )
		{
			PopBack();
			return;
		}

		if( position.GetCurrentSlot() == m_head )
		{
			PopFront();
			return;
		}

		position->m_previous->m_next	= position->m_next;
		position->m_next->m_previous	= position->m_previous;
		position->m_host				= nullptr;
		position->m_previous			= nullptr;
		position->m_next				= nullptr;

		EXPECTS_DEBUG( m_size > 0 );
		--m_size;
	}

	DoublyLinkedList::Slot& DoublyLinkedList::GetFrontSlot() const
	{
		EXPECTS_DEBUG( !IsEmpty() );
		return *m_head;
	}

	DoublyLinkedList::Slot& DoublyLinkedList::GetBackSlot() const
	{
		EXPECTS_DEBUG( !IsEmpty() );
		return *m_end.m_previous;
	}
}
}
}
}
