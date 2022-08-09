#pragma once


namespace Black
{
inline namespace Core
{
// Core intrusive objects subsystem.
inline namespace Intrusives
{
// Internal definitions for intrusives.
namespace Internal
{

}
}
}
}


// Most fundamental stuff.
#include "internal/forwards.h"

// Internal stuff.
#include "internal/forward-list/SinglyLinkedListSlot.h"
#include "internal/forward-list/SinglyLinkedListCursor.h"
#include "internal/forward-list/SinglyLinkedList.h"

#include "internal/list/DoublyLinkedListSlot.h"
#include "internal/list/DoublyLinkedListCursor.h"
#include "internal/list/DoublyLinkedList.h"

#include "internal/IntrusiveTraits.h"

// Intrusive containers.
#include "aliases.h"
#include "forwards.h"
#include "internal/forwards.templates.h"

#include "internal/forward-list/ForwardListConstIterator.h"
#include "internal/forward-list/ForwardListIterator.h"
#include "internal/forward-list/BasicIntrusiveForwardList.h"
#include "IntrusiveForwardList.h"

#include "internal/list/ListConstIterator.h"
#include "internal/list/ListIterator.h"
#include "internal/list/BasicIntrusiveList.h"
#include "IntrusiveList.h"

#include "internal/interconnection/BasicInterconnectionSlot.h"
#include "internal/interconnection/InterconnectionSlotDummy.h"
#include "internal/interconnection/InterconnectionSlot.h"
#include "Interconnection.h"

// Deferred implementations
#include "internal/interconnection/InterconnectionSlot.inl"

#include "internal/list/BasicIntrusiveList.inl"
#include "internal/list/ListIterator.inl"
#include "internal/list/ListConstIterator.inl"

#include "internal/forward-list/BasicIntrusiveForwardList.inl"
#include "internal/forward-list/ForwardListIterator.inl"
#include "internal/forward-list/ForwardListConstIterator.inl"

#include "internal/IntrusiveTraits.inl"
