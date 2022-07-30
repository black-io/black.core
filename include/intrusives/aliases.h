#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
	// Regular slot for intrusive forward list.
	using IntrusiveForwardListSlot = Internal::SinglyLinkedListSlot;

	// Regular slot for intrusive list.
	using IntrusiveListSlot = Internal::DoublyLinkedListSlot;
}
}
}
