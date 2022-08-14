#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
inline namespace List
{
	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline ListIterator<TValue, SLOT_POINTER>& ListIterator<TValue, SLOT_POINTER>::operator++()
	{
		EXPECTS_DEBUG( m_cursor.IsValid() );
		m_cursor.ShiftNext();
		return *this;
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline ListIterator<TValue, SLOT_POINTER> ListIterator<TValue, SLOT_POINTER>::operator++( int )
	{
		EXPECTS_DEBUG( m_cursor.IsValid() );
		ListIterator copy{ m_cursor };
		m_cursor.ShiftNext();
		return copy;
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline ListIterator<TValue, SLOT_POINTER>& ListIterator<TValue, SLOT_POINTER>::operator--()
	{
		EXPECTS_DEBUG( m_cursor.IsEnd() || m_cursor.IsValid() );
		m_cursor.ShiftBack();
		return *this;
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline ListIterator<TValue, SLOT_POINTER> ListIterator<TValue, SLOT_POINTER>::operator--( int )
	{
		EXPECTS_DEBUG( m_cursor.IsEnd() || m_cursor.IsValid() );
		ListIterator copy{ m_cursor };
		m_cursor.ShiftBack();
		return copy;
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline TValue& ListIterator<TValue, SLOT_POINTER>::operator*() const
	{
		EXPECTS_DEBUG( m_cursor.IsValid() );
		return Traits::GetValue( *m_cursor );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline TValue* ListIterator<TValue, SLOT_POINTER>::operator->() const
	{
		return &operator*();
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline const bool ListIterator<TValue, SLOT_POINTER>::operator==( const ListIterator& other ) const
	{
		CRET( m_cursor.IsEnd() != other.m_cursor.IsEnd(), false );
		CRET( m_cursor.IsEnd(), true );
		CRET( m_cursor.IsValid() != other.m_cursor.IsValid(), false );
		return &m_cursor.GetSlot() == &other.m_cursor.GetSlot();
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline const bool ListIterator<TValue, SLOT_POINTER>::operator!=( const ListIterator& other ) const
	{
		return !operator==( other );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline ListIterator<TValue, SLOT_POINTER>::ListIterator( DoublyLinkedListCursor cursor )
		: m_cursor{ std::move( cursor ) }
	{
	}
}
}
}
}
}
