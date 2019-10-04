#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
namespace Internal
{
	// Common deduction branch. True functionality.
	template< Black::BuildMode >
	class DebugName final
	{
	// Construction and initialization.
	public:
		DebugName()						= default;
		DebugName( const DebugName& )	= default;
		DebugName( DebugName&& )		= default;
		DebugName( std::string name ) : m_name{ std::move( name ) } {};
		DebugName( std::string_view name ) : m_name{ name } {};
		DebugName( Black::StringView name ) : m_name{ name.begin(), name.end() } {};
		DebugName( const char* const name ) : m_name{ name } {};


		inline DebugName& operator = ( const DebugName& )		= default;
		inline DebugName& operator = ( DebugName&& )			= default;
		inline DebugName& operator = ( std::string name )		{ return Black::CopyAndSwap( *this, std::move( name ) ); };
		inline DebugName& operator = ( std::string_view name )	{ return Black::CopyAndSwap( *this, name ); };
		inline DebugName& operator = ( Black::StringView name )	{ return Black::CopyAndSwap( *this, name ); };
		inline DebugName& operator = ( const char* const name )	{ return Black::CopyAndSwap( *this, name ); };

	// Public interface.
	public:
		// Get the name.
		inline const char* const GetName() const				{ return m_name.data(); };


		inline const char* const operator * () const			{ return GetName(); };

	// Private state.
	private:
		std::string	m_name;	// Stored name.
	};

	// Terminal deduction branch. Fake functionality for release build.
	template<>
	class DebugName<Black::BuildMode::Release> final
	{
	// Fake initialization.
	public:
		DebugName()												= default;
		DebugName( const DebugName& )							= default;
		DebugName( DebugName&& )								= default;
		DebugName( std::string name )							{};
		DebugName( std::string_view name )						{};
		DebugName( Black::StringView name )						{};
		DebugName( const char* const name )						{};


		inline DebugName& operator = ( const DebugName& )		= default;
		inline DebugName& operator = ( DebugName&& )			= default;
		inline DebugName& operator = ( std::string name )		{ return *this; };
		inline DebugName& operator = ( std::string_view name )	{ return *this; };
		inline DebugName& operator = ( Black::StringView name )	{ return *this; };
		inline DebugName& operator = ( const char* const name )	{ return *this; };

	// Fake interface.
	public:
		// Fake name getter.
		inline const char* const GetName() const				{ return ""; };


		inline const char* const operator * () const			{ return GetName(); };
	};
}


	/**
		@brief	Debug name for any entity.
		Debug names are visible only in Debug build configuration. For any other configuration such names will be empty.
		Ideally, any code about debug names may be omitted out of code for non-Debug build configurations.
	*/
	using DebugName = Internal::DebugName<Black::BUILD_CONFIGURATION>;
}
}
}
