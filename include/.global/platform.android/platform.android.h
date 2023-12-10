#pragma once


// External dependencies.
#include <jni.h>
#include <android/log.h>


namespace Black
{
inline namespace Core
{
inline namespace Global
{
// Google Android platform definitions.
inline namespace Android
{
// Internal platform-related stuff for Google Android platform.
namespace Internal
{

}
}
}
}
}


// Platform-specific stuff.
#include "constants.h"

#include "functions.debug.android.h"
#include "functions.formatting.android.h"
#include "functions.memory.android.h"
