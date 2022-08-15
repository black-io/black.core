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
	template< typename TValue, typename TTraits >
	inline ListIterator<TValue, TTraits>& ListIterator<TValue, TTraits>::operator++()
	{
		EXPECTS_DEBUG( m_cursor.IsValid() );
		m_cursor.ShiftNext();
		return *this;
	}

	template< typename TValue, typename TTraits >
	inline ListIterator<TValue, TTraits> ListIterator<TValue, TTraits>::operator++( int )
	{
		EXPECTS_DEBUG( m_cursor.IsValid() );
		ListIterator copy{ m_cursor };
		m_cursor.ShiftNext();
		return copy;
	}

	template< typename TValue, typename TTraits >
	inline ListIterator<TValue, TTraits>& ListIterator<TValue, TTraits>::operator--()
	{
		EXPECTS_DEBUG( m_cursor.IsEnd() || m_cursor.IsValid() );
		m_cursor.ShiftBack();
		return *this;
	}

	template< typename TValue, typename TTraits >
	inline ListIterator<TValue, TTraits> ListIterator<TValue, TTraits>::operator--( int )
	{
		EXPECTS_DEBUG( m_cursor.IsEnd() || m_cursor.IsValid() );
		ListIterator copy{ m_cursor };
		m_cursor.ShiftBack();
		return copy;
	}

	template< typename TValue, typename TTraits >
	inline TValue& ListIterator<TValue, TTraits>::operator*() const
	{
		EXPECTS_DEBUG( m_cursor.IsValid() );
		return TTraits::GetValue( *m_cursor );
	}

	template< typename TValue, typename TTraits >
	inline TValue* ListIterator<TValue, TTraits>::operator->() const
	{
		return &operator*();
	}

	template< typename TValue, typename TTraits >
	inline const bool ListIterator<TValue, TTraits>::operator==( const ListIterator& other ) const
	{
		CRET( m_cursor.IsEnd() != other.m_cursor.IsEnd(), false );
		CRET( m_cursor.IsEnd(), true );
		CRET( m_cursor.IsValid() != other.m_cursor.IsValid(), false );
		return &m_cursor.GetSlot() == &other.m_cursor.GetSlot();
	}

	template< typename TValue, typename TTraits >
	inline const bool ListIterator<TValue, TTraits>::operator!=( const ListIterator& other ) const
	{
		return !operator==( other );
	}

	template< typename TValue, typename TTraits >
	inline ListIterator<TValue, TTraits>::ListIterator( DoublyLinkedListCursor cursor )
		: m_cursor{ std::move( cursor ) }
	{
	}
}
}
}
}
}
