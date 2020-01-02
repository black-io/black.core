#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
namespace Internal
{
	// Regular debug name implementation.
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

	// Fake debug name implementation. Well used in release builds.
	class FakeDebugName final
	{
	// Fake initialization.
	public:
		FakeDebugName()												= default;
		FakeDebugName( const FakeDebugName& )						= default;
		FakeDebugName( FakeDebugName&& )							= default;
		FakeDebugName( std::string name )							{};
		FakeDebugName( std::string_view name )						{};
		FakeDebugName( Black::StringView name )						{};
		FakeDebugName( const char* const name )						{};


		inline FakeDebugName& operator = ( const FakeDebugName& )	= default;
		inline FakeDebugName& operator = ( FakeDebugName&& )		= default;
		inline FakeDebugName& operator = ( std::string name )		{ return *this; };
		inline FakeDebugName& operator = ( std::string_view name )	{ return *this; };
		inline FakeDebugName& operator = ( Black::StringView name )	{ return *this; };
		inline FakeDebugName& operator = ( const char* const name )	{ return *this; };

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
	using DebugName = Black::BuildModeDependent<Internal::FakeDebugName, Internal::DebugName>;
}
}
}
