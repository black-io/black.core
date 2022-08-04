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
#include "internal/SinglyLinkedListSlot.h"
#include "internal/SinglyLinkedListIterator.h"
#include "internal/SinglyLinkedList.h"

#include "internal/DoublyLinkedListSlot.h"
#include "internal/DoublyLinkedListIterator.h"
#include "internal/DoublyLinkedList.h"

#include "internal/IntrusiveTraits.h"

// Intrusive containers.
#include "aliases.h"
#include "forwards.h"
#include "internal/forwards.templates.h"

#include "internal/ForwardListConstIterator.h"
#include "internal/ForwardListIterator.h"
#include "IntrusiveForwardList.h"

#include "internal/ListConstIterator.h"
#include "internal/ListIterator.h"
#include "IntrusiveList.h"

#include "internal/BasicInterconnectionSlot.h"
#include "internal/InterconnectionSlotDummy.h"
#include "internal/InterconnectionSlot.h"
#include "Interconnection.h"

// Deferred implementations
#include "internal/InterconnectionSlot.inl"

#include "IntrusiveList.inl"
#include "internal/ListIterator.inl"
#include "internal/ListConstIterator.inl"

#include "IntrusiveForwardList.inl"
#include "internal/ForwardListIterator.inl"
#include "internal/ForwardListConstIterator.inl"

#include "internal/IntrusiveTraits.inl"
