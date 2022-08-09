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
	// To be used in friendship declarations.
	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	class ForwardListIterator;

	// To be used in friendship declarations.
	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	class BasicIntrusiveForwardList;
}


inline namespace List
{
	// To be used in friendship declarations.
	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	class ListIterator;

	// To be used in friendship declarations.
	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	class BasicIntrusiveList;
}
}
}
}
}
