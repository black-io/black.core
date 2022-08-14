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
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::Clear()
	{
		DoublyLinkedList::Clear();
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::PushFront( Value& value )
	{
		DoublyLinkedList::PushFront( Traits::GetSlot( value ) );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::PopFront()
	{
		DoublyLinkedList::PopFront();
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::PushBack( Value& value )
	{
		DoublyLinkedList::PushBack( Traits::GetSlot( value ) );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::PopBack()
	{
		DoublyLinkedList::PopBack();
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::Insert( ConstIterator position, Value& value )
	{
		DoublyLinkedList::Insert( position.m_cursor, Traits::GetSlot( value ) );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveList<TValue, SLOT_POINTER>::Erase( ConstIterator position )
	{
		DoublyLinkedList::Erase( position.m_cursor );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::Value& BasicIntrusiveList<TValue, SLOT_POINTER>::GetFront()
	{
		return Traits::GetValue( DoublyLinkedList::GetFrontSlot() );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline const typename BasicIntrusiveList<TValue, SLOT_POINTER>::Value& BasicIntrusiveList<TValue, SLOT_POINTER>::GetFront() const
	{
		return Traits::GetValue( DoublyLinkedList::GetFrontSlot() );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::Value& BasicIntrusiveList<TValue, SLOT_POINTER>::GetBack()
	{
		return Traits::GetValue( DoublyLinkedList::GetBackSlot() );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline const typename BasicIntrusiveList<TValue, SLOT_POINTER>::Value& BasicIntrusiveList<TValue, SLOT_POINTER>::GetBack() const
	{
		return Traits::GetValue( DoublyLinkedList::GetBackSlot() );
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::Iterator BasicIntrusiveList<TValue, SLOT_POINTER>::GetBegin()
	{
		return Iterator{ DoublyLinkedList::GetBegin() };
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::ConstIterator BasicIntrusiveList<TValue, SLOT_POINTER>::GetBegin() const
	{
		return ConstIterator{ DoublyLinkedList::GetBegin() };
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::Iterator BasicIntrusiveList<TValue, SLOT_POINTER>::GetEnd()
	{
		return Iterator{ DoublyLinkedList::GetEnd() };
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveList<TValue, SLOT_POINTER>::ConstIterator BasicIntrusiveList<TValue, SLOT_POINTER>::GetEnd() const
	{
		return ConstIterator{ DoublyLinkedList::GetEnd() };
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline const size_t BasicIntrusiveList<TValue, SLOT_POINTER>::GetLength() const
	{
		return DoublyLinkedList::GetLength();
	}

	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	inline const bool BasicIntrusiveList<TValue, SLOT_POINTER>::IsEmpty() const
	{
		return DoublyLinkedList::IsEmpty();
	}
}
}
}
}
}
