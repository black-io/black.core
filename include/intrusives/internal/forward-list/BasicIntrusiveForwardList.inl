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
	template< typename TValue, typename TTraits >
	inline void BasicIntrusiveForwardList<TValue, TTraits>::Clear()
	{
		SinglyLinkedList::Clear();
	}

	template< typename TValue, typename TTraits >
	inline void BasicIntrusiveForwardList<TValue, TTraits>::PushFront( Value& value )
	{
		SinglyLinkedList::PushFront( TTraits::GetSlot( value ) );
	}

	template< typename TValue, typename TTraits >
	inline void BasicIntrusiveForwardList<TValue, TTraits>::PopFront()
	{
		SinglyLinkedList::PopFront();
	}

	template< typename TValue, typename TTraits >
	inline void BasicIntrusiveForwardList<TValue, TTraits>::InsertAfter( Iterator position, Value& value )
	{
		SinglyLinkedList::InsertAfter( position.m_cursor, TTraits::GetSlot( value ) );
	}

	template< typename TValue, typename TTraits >
	inline void BasicIntrusiveForwardList<TValue, TTraits>::EraseAfter( Iterator position )
	{
		SinglyLinkedList::EraseAfter( position.m_cursor );
	}

	template< typename TValue, typename TTraits >
	inline typename BasicIntrusiveForwardList<TValue, TTraits>::Value& BasicIntrusiveForwardList<TValue, TTraits>::GetFirstValue()
	{
		return TTraits::GetValue( SinglyLinkedList::GetFrontSlot() );
	}

	template< typename TValue, typename TTraits >
	inline const typename BasicIntrusiveForwardList<TValue, TTraits>::Value& BasicIntrusiveForwardList<TValue, TTraits>::GetFirstValue() const
	{
		return TTraits::GetValue( SinglyLinkedList::GetFrontSlot() );
	}

	template< typename TValue, typename TTraits >
	inline typename BasicIntrusiveForwardList<TValue, TTraits>::Iterator BasicIntrusiveForwardList<TValue, TTraits>::GetBegin()
	{
		return Iterator{ SinglyLinkedList::GetBegin() };
	}

	template< typename TValue, typename TTraits >
	inline typename BasicIntrusiveForwardList<TValue, TTraits>::Iterator BasicIntrusiveForwardList<TValue, TTraits>::GetEnd()
	{
		return Iterator{ SinglyLinkedList::GetEnd() };
	}

	template< typename TValue, typename TTraits >
	inline const size_t BasicIntrusiveForwardList<TValue, TTraits>::GetLength() const
	{
		return SinglyLinkedList::GetLength();
	}

	template< typename TValue, typename TTraits >
	inline const bool BasicIntrusiveForwardList<TValue, TTraits>::IsEmpty() const
	{
		return SinglyLinkedList::IsEmpty();
	}
}
}
}
}
}
