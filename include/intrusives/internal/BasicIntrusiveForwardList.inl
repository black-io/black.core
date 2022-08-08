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
	inline void BasicIntrusiveForwardList<TValue, SLOT_POINTER>::Clear()
	{
		m_slots.Clear();
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveForwardList<TValue, SLOT_POINTER>::PushFront( Value& value )
	{
		m_slots.PushFront( Traits::GetSlot( value ) );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveForwardList<TValue, SLOT_POINTER>::PopFront()
	{
		m_slots.PopFront();
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveForwardList<TValue, SLOT_POINTER>::InsertAfter( ConstIterator position, Value& value )
	{
		m_slots.InsertAfter( position.m_iterator, Traits::GetSlot( value ) );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveForwardList<TValue, SLOT_POINTER>::EraseAfter( ConstIterator position )
	{
		m_slots.EraseAfter( position.m_iterator );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveForwardList<TValue, SLOT_POINTER>::Value& BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetFirstValue()
	{
		return Traits::GetValue( m_slots.GetFrontSlot() );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline const typename BasicIntrusiveForwardList<TValue, SLOT_POINTER>::Value& BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetFirstValue() const
	{
		return Traits::GetValue( m_slots.GetFrontSlot() );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveForwardList<TValue, SLOT_POINTER>::Iterator BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetBegin()
	{
		return Iterator{ m_slots.GetBegin() };
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveForwardList<TValue, SLOT_POINTER>::ConstIterator BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetBegin() const
	{
		return ConstIterator{ m_slots.GetBegin() };
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveForwardList<TValue, SLOT_POINTER>::Iterator BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetEnd()
	{
		return Iterator{ m_slots.GetEnd() };
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveForwardList<TValue, SLOT_POINTER>::ConstIterator BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetEnd() const
	{
		return ConstIterator{ m_slots.GetEnd() };
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline const size_t BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetSize() const
	{
		return m_slots.GetSize();
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline const bool BasicIntrusiveForwardList<TValue, SLOT_POINTER>::IsEmpty() const
	{
		return m_slots.IsEmpty();
	}
}
}
}
}
