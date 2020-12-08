#pragma once


namespace Black
{
inline namespace Core
{
// Namespace for core concurrency subsystem.
inline namespace Concurrency
{
// Core concurrency internal definitions.
namespace Internal
{

}
}
}
}


#include "concurrency.const.h"
#include "concurrency.functions.h"

#include "Mutex.h"
#include "MutexLock.h"
#include "SpinLock.h"
#include "CriticalSection.h"
#include "Monitor.h"

#include "Monitor.inl"
#include "SpinLock.inl"
