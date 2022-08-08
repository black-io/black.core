#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::Clear()
	{
		m_slots.Clear();
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::PushFront( Value& value )
	{
		m_slots.PushFront( Traits::GetSlot( value ) );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::PopFront()
	{
		m_slots.PopFront();
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::PushBack( Value& value )
	{
		m_slots.PushBack( Traits::GetSlot( value ) );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::PopBack()
	{
		m_slots.PopBack();
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::Insert( ConstIterator position, Value& value )
	{
		m_slots.Insert( position.m_iterator, Traits::GetSlot( value ) );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::Erase( ConstIterator position )
	{
		m_slots.Erase( position.m_iterator );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::Value& BasicIntrusiveList<TValue, SLOT_POINTER>::GetFront()
	{
		return Traits::GetValue( m_slots.GetFrontSlot() );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline const typename BasicIntrusiveList<TValue, SLOT_POINTER>::Value& BasicIntrusiveList<TValue, SLOT_POINTER>::GetFront() const
	{
		return Traits::GetValue( m_slots.GetFrontSlot() );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::Value& BasicIntrusiveList<TValue, SLOT_POINTER>::GetBack()
	{
		return Traits::GetValue( m_slots.GetBackSlot() );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline const typename BasicIntrusiveList<TValue, SLOT_POINTER>::Value& BasicIntrusiveList<TValue, SLOT_POINTER>::GetBack() const
	{
		return Traits::GetValue( m_slots.GetBackSlot() );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::Iterator BasicIntrusiveList<TValue, SLOT_POINTER>::GetBegin()
	{
		return Iterator{ m_slots.GetBegin() };
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::ConstIterator BasicIntrusiveList<TValue, SLOT_POINTER>::GetBegin() const
	{
		return ConstIterator{ m_slots.GetBegin() };
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::ConstIterator BasicIntrusiveList<TValue, SLOT_POINTER>::GetConstBegin() const
	{
		return ConstIterator{ m_slots.GetBegin() };
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::Iterator BasicIntrusiveList<TValue, SLOT_POINTER>::GetEnd()
	{
		return Iterator{ m_slots.GetEnd() };
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::ConstIterator BasicIntrusiveList<TValue, SLOT_POINTER>::GetEnd() const
	{
		return ConstIterator{ m_slots.GetEnd() };
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::ConstIterator BasicIntrusiveList<TValue, SLOT_POINTER>::GetConstEnd() const
	{
		return ConstIterator{ m_slots.GetEnd() };
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline const size_t BasicIntrusiveList<TValue, SLOT_POINTER>::GetSize() const
	{
		return m_slots.GetSize();
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline const bool BasicIntrusiveList<TValue, SLOT_POINTER>::IsEmpty() const
	{
		return m_slots.IsEmpty();
	}
}
}
}
}
