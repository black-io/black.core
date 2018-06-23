#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
namespace Internal
{
	// Default implementation of debug name.
	template< Black::BuildMode >
	class DebugName final
	{
	public:
		DebugName()											= default;
		DebugName( const DebugName& )						= default;
		DebugName( DebugName&& )							= default;
		DebugName( std::string&& )							{};
		DebugName( Black::StringView )						{};
		DebugName( const char* const )						{};


		// Fake name getter for non-debug configurations.
		constexpr const char* const GetName() const			{ return "n/a"; };


		inline DebugName& operator = ( const DebugName& )	= default;
		inline DebugName& operator = ( DebugName&& )		= default;
		inline DebugName& operator = ( std::string&& )		{ return *this; };
		inline DebugName& operator = ( Black::StringView )	{ return *this; };
		inline DebugName& operator = ( const char* const )	{ return *this; };

		constexpr const char* const operator * () const		{ return GetName(); };
	};

	// Explicit specialization for Debug name in Debug build configuration.
	template<>
	class DebugName<Black::BuildMode::Debug> final
	{
	public:
		DebugName()						= default;
		DebugName( const DebugName& )	= default;
		DebugName( DebugName&& )		= default;
		DebugName( std::string&& name ) : m_name{ std::move( name ) } {};
		DebugName( Black::StringView name ) : m_name{ name.begin(), name.end() } {};
		DebugName( const char* const name ) : m_name{ name } {};


		// Get the name.
		inline const char* const GetName() const				{ return m_name.data(); };


		inline DebugName& operator = ( const DebugName& )		= default;
		inline DebugName& operator = ( DebugName&& )			= default;
		inline DebugName& operator = ( std::string&& name )		{ m_name = std::move( name ); return *this; };
		inline DebugName& operator = ( Black::StringView name )	{ m_name = { name.begin(), name.end() }; return *this; };
		inline DebugName& operator = ( const char* const name )	{ m_name = name; return *this; };

		inline const char* const operator * () const			{ return GetName(); };

	private:
		std::string	m_name;	// Stored name.
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
