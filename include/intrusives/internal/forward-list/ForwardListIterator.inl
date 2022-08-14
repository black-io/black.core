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
	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline ForwardListIterator<TValue, SLOT_POINTER>& ForwardListIterator<TValue, SLOT_POINTER>::operator++()
	{
		EXPECTS_DEBUG( m_cursor.IsValid() );
		m_cursor.ShiftNext();
		return *this;
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline ForwardListIterator<TValue, SLOT_POINTER> ForwardListIterator<TValue, SLOT_POINTER>::operator++( int )
	{
		EXPECTS_DEBUG( m_cursor.IsValid() );
		ForwardListIterator copy{ m_cursor };
		m_cursor.ShiftNext();
		return copy;
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline TValue& ForwardListIterator<TValue, SLOT_POINTER>::operator*() const
	{
		EXPECTS_DEBUG( m_cursor.IsValid() );
		return Traits::GetValue( *m_cursor );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline TValue* ForwardListIterator<TValue, SLOT_POINTER>::operator->() const
	{
		return &operator*();
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline const bool ForwardListIterator<TValue, SLOT_POINTER>::operator==( const ForwardListIterator& other ) const
	{
		CRET( m_cursor.IsEnd() != other.m_cursor.IsEnd(), false );
		CRET( m_cursor.IsEnd(), true );
		CRET( m_cursor.IsValid() != other.m_cursor.IsValid(), false );
		return &m_cursor.GetSlot() == &other.m_cursor.GetSlot();
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline const bool ForwardListIterator<TValue, SLOT_POINTER>::operator!=( const ForwardListIterator& other ) const
	{
		return !operator==( other );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline ForwardListIterator<TValue, SLOT_POINTER>::ForwardListIterator( SinglyLinkedListCursor cursor )
		: m_cursor{ std::move( cursor ) }
	{
	}
}
}
}
}
}
