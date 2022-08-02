#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
	// To be used in friendship declarations.
	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	class ForwardListIterator;

	// To be used in friendship declarations.
	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	class ListIterator;
}
}
}
}
