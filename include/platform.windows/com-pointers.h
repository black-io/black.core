#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Platform
{
inline namespace WindowsDesktop
{
	// Regular unique pointer for COM objects.
	template< typename TClass >
	using UniqueComPointer = std::unique_ptr<TClass, Internal::ComObjectReleaser<TClass>>;

	// Regular scoped pointer for COM objects.
	template< typename TClass >
	using ScopedComPointer = Black::ScopedPointer<TClass, Internal::ComObjectReleaser<TClass>>;

	// Regular shared pointer for COM objects.
	template< typename TClass >
	using SharedComPointer = std::shared_ptr<TClass>;
}
}
}
}
