#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Platform
{
namespace Internal
{
	/**
		@brief	Template of COM object deleter.

		This deleter may be used in STL smart pointers to allow them store the COM objects.
		Template made not final to allow the possible EBO for STL pointers.

		@tparam	TClass	Target COM class.
	*/
	template< typename TClass >
	class ComObjectReleaser
	{
	// Public interface.
	public:
		inline void operator () ( TClass* instance ) const
		{
			CRET( instance == nullptr );
			instance->Release();
		}
	};
}
}
}
}
}
