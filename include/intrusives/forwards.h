#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
	// To be used in friendship declarations.
	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	class IntrusiveForwardList;

	// To be used in friendship declarations.
	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	class IntrusiveList;
}
}
}
