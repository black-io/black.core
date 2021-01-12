#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
namespace Internal
{
	// Decoration type to translate the type if static list interface into static list tag.
	template< typename TInterface >
	struct InterfaceTag final {};
}
}
}
}
