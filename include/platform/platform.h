#pragma once


namespace Black
{
inline namespace Core
{
// Core platform subsystem.
inline namespace Platform
{
// Internal definitions for platforms.
namespace Internal
{

}
}
}
}


// Include most fundamental platform stuff.
#include "functions.h"
#include "platform-specific/debug.h"
#include "platform-specific/formatting.h"
#include "platform-specific/memory.h"

// Include the platform-specific code.
#include BLACK_CURRENT_PLATFORM_HEADER

// Deferred implementations.
#include "functions.inl"
