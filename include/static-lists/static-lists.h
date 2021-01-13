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

// Most fundamental stuff.
#include "internal/constants.h"
#include "internal/structures.h"
#include "internal/BasicStaticNode.h"
#include "internal/ConstructionProxy.h"

#include "internal/StaticListCommonNode.h"
#include "internal/StaticListIterator.h"
#include "internal/StaticListNode.h"
#include "internal/StaticStorageNode.h"

#include "internal/BasicStaticList.h"

// Declarations of static lists.
#include "StaticList.h"
#include "StaticStorage.h"

#include "predefined-lists.h"

// Deferred implementations.
#include "StaticStorage.inl"
#include "StaticList.inl"

#include "internal/BasicStaticList.inl"

#include "internal/StaticStorageNode.inl"
#include "internal/StaticListNode.inl"
#include "internal/StaticListIterator.inl"

#include "internal/BasicStaticNode.inl"
