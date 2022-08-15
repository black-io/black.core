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
	inline void BasicIntrusiveList<TValue, TTraits>::Clear()
	{
		DoublyLinkedList::Clear();
	}

	template< typename TValue, typename TTraits >
	inline void BasicIntrusiveList<TValue, TTraits>::PushFront( Value& value )
	{
		DoublyLinkedList::PushFront( TTraits::GetSlot( value ) );
	}

	template< typename TValue, typename TTraits >
	inline void BasicIntrusiveList<TValue, TTraits>::PopFront()
	{
		DoublyLinkedList::PopFront();
	}

	template< typename TValue, typename TTraits >
	inline void BasicIntrusiveList<TValue, TTraits>::PushBack( Value& value )
	{
		DoublyLinkedList::PushBack( TTraits::GetSlot( value ) );
	}

	template< typename TValue, typename TTraits >
	inline void BasicIntrusiveList<TValue, TTraits>::PopBack()
	{
		DoublyLinkedList::PopBack();
	}

	template< typename TValue, typename TTraits >
	inline void BasicIntrusiveList<TValue, TTraits>::Insert( Iterator position, Value& value )
	{
		DoublyLinkedList::Insert( position.m_cursor, TTraits::GetSlot( value ) );
	}

	template< typename TValue, typename TTraits >
	inline void BasicIntrusiveList<TValue, TTraits>::Erase( Iterator position )
	{
		DoublyLinkedList::Erase( position.m_cursor );
	}

	template< typename TValue, typename TTraits >
	inline typename BasicIntrusiveList<TValue, TTraits>::Value& BasicIntrusiveList<TValue, TTraits>::GetFront() const
	{
		return TTraits::GetValue( DoublyLinkedList::GetFrontSlot() );
	}

	template< typename TValue, typename TTraits >
	inline typename BasicIntrusiveList<TValue, TTraits>::Value& BasicIntrusiveList<TValue, TTraits>::GetBack() const
	{
		return TTraits::GetValue( DoublyLinkedList::GetBackSlot() );
	}

	template< typename TValue, typename TTraits >
	inline typename BasicIntrusiveList<TValue, TTraits>::Iterator BasicIntrusiveList<TValue, TTraits>::GetBegin() const
	{
		return Iterator{ DoublyLinkedList::GetBegin() };
	}

	template< typename TValue, typename TTraits >
	inline typename BasicIntrusiveList<TValue, TTraits>::Iterator BasicIntrusiveList<TValue, TTraits>::GetEnd() const
	{
		return Iterator{ DoublyLinkedList::GetEnd() };
	}

	template< typename TValue, typename TTraits >
	inline const size_t BasicIntrusiveList<TValue, TTraits>::GetLength() const
	{
		return DoublyLinkedList::GetLength();
	}

	template< typename TValue, typename TTraits >
	inline const bool BasicIntrusiveList<TValue, TTraits>::IsEmpty() const
	{
		return DoublyLinkedList::IsEmpty();
	}
}
}
}
}
}
