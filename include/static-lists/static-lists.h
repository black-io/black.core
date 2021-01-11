#pragma once


namespace Black
{
inline namespace Core
{
// Static chains and static lists subsystem.
inline namespace StaticLists
{
// Internal definitions for static lists.
namespace Internal
{

}
}
}
}


// Some forwards.
#include "internal/forwards.h"
#include "forwards.h"

// Most fundamental stuff.
#include "internal/BasicStaticNode.h"
#include "internal/ConstructionProxy.h"
#include "internal/StaticListIterator.h"
#include "internal/StaticListNode.h"

// Implementation of static list.
#include "StaticList.h"

// Deferred implementations.
#include "StaticList.inl"

#include "internal/StaticListNode.inl"
#include "internal/StaticListIterator.inl"
#include "internal/BasicStaticNode.inl"
