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
inline namespace Platform
{
// Google Android platform definitions.
inline namespace Android
{
	// JNI version, used by Black framework.
	inline constexpr int32_t JNI_VERSION = JNI_VERSION_1_6;
}
}
}
}
}
