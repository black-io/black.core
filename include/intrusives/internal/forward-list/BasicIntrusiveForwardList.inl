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
		SinglyLinkedList::Clear();
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveForwardList<TValue, SLOT_POINTER>::PushFront( Value& value )
	{
		SinglyLinkedList::PushFront( Traits::GetSlot( value ) );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveForwardList<TValue, SLOT_POINTER>::PopFront()
	{
		SinglyLinkedList::PopFront();
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveForwardList<TValue, SLOT_POINTER>::InsertAfter( ConstIterator position, Value& value )
	{
		SinglyLinkedList::InsertAfter( position.m_cursor, Traits::GetSlot( value ) );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline void BasicIntrusiveForwardList<TValue, SLOT_POINTER>::EraseAfter( ConstIterator position )
	{
		SinglyLinkedList::EraseAfter( position.m_cursor );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveForwardList<TValue, SLOT_POINTER>::Value& BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetFirstValue()
	{
		return Traits::GetValue( SinglyLinkedList::GetFrontSlot() );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline const typename BasicIntrusiveForwardList<TValue, SLOT_POINTER>::Value& BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetFirstValue() const
	{
		return Traits::GetValue( SinglyLinkedList::GetFrontSlot() );
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveForwardList<TValue, SLOT_POINTER>::Iterator BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetBegin()
	{
		return Iterator{ SinglyLinkedList::GetBegin() };
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveForwardList<TValue, SLOT_POINTER>::ConstIterator BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetBegin() const
	{
		return ConstIterator{ SinglyLinkedList::GetBegin() };
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveForwardList<TValue, SLOT_POINTER>::Iterator BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetEnd()
	{
		return Iterator{ SinglyLinkedList::GetEnd() };
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline typename BasicIntrusiveForwardList<TValue, SLOT_POINTER>::ConstIterator BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetEnd() const
	{
		return ConstIterator{ SinglyLinkedList::GetEnd() };
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline const size_t BasicIntrusiveForwardList<TValue, SLOT_POINTER>::GetSize() const
	{
		return SinglyLinkedList::GetSize();
	}

	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	inline const bool BasicIntrusiveForwardList<TValue, SLOT_POINTER>::IsEmpty() const
	{
		return SinglyLinkedList::IsEmpty();
	}
}
}
}
}
