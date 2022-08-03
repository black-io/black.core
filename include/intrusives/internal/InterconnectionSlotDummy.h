#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
	/**
	*/
	class InterconnectionSlotDummy : public InterconnectionSlot
	{
	// `InterconnectionSlot` virtual overrides.
	public:
		/// @see InterconnectionSlot::Invalidate
		void Invalidate() override {};
	};
}
}
}
}
