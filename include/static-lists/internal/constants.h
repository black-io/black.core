#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
namespace Internal
{
	// Tagging type to indicate that the `BasicStaticNode` should be instantly insert into static list on construction.
	enum class InstantInsert;

	// Tagging object to indicate that the `BasicStaticNode` should be plugged into the static list just at construction.
	inline constexpr InstantInsert INSTANT_INSERT = {};
}
}
}
}
