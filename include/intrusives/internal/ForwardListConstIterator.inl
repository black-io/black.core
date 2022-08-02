#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline ForwardListConstIterator<TValue, SLOT_POINTER>& ForwardListConstIterator<TValue, SLOT_POINTER>::operator++()
	{
		EXPECTS_DEBUG( m_iterator.IsValid() );
		m_iterator.ShiftNext();
		return *this;
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline ForwardListConstIterator<TValue, SLOT_POINTER> ForwardListConstIterator<TValue, SLOT_POINTER>::operator++( int )
	{
		EXPECTS_DEBUG( m_iterator.IsValid() );
		ForwardListConstIterator copy{ m_iterator };
		m_iterator.ShiftNext();
		return copy;
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline const TValue& ForwardListConstIterator<TValue, SLOT_POINTER>::operator*() const
	{
		EXPECTS_DEBUG( m_iterator.IsValid() );
		return Traits::GetValue( *m_iterator );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline const TValue* ForwardListConstIterator<TValue, SLOT_POINTER>::operator->() const
	{
		return &operator*();
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline const bool ForwardListConstIterator<TValue, SLOT_POINTER>::operator==( const ForwardListConstIterator& other ) const
	{
		CRET( m_iterator.IsEnd() != other.m_iterator.IsEnd(), false );
		CRET( m_iterator.IsEnd(), true );
		CRET( m_iterator.IsValid() != other.m_iterator.IsValid(), false );
		return m_iterator.GetCurrentSlot() == other.m_iterator.GetCurrentSlot();
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline const bool ForwardListConstIterator<TValue, SLOT_POINTER>::operator!=( const ForwardListConstIterator& other ) const
	{
		return !operator==( other );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline ForwardListConstIterator<TValue, SLOT_POINTER>::ForwardListConstIterator( SinglyLinkedListIterator iterator )
		: m_iterator{ std::move( iterator ) }
	{
	}
}
}
}
}
