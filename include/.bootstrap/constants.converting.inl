#pragma once


namespace Black
{
	inline void ConvertFromString( const std::string_view source, BuildMode& destination )
	{
		// To simplify the name qualification.
		using namespace Core::Bootstrap::Internal;


		auto found_name = std::find( std::begin( BuildModeMappings::NAMES ), std::end( BuildModeMappings::NAMES ), source );
		EXPECTS_DEBUG( found_name != std::end( BuildModeMappings::NAMES ) );

		if( found_name != std::end( BuildModeMappings::NAMES ) )
		{
			destination = static_cast<BuildMode>( std::distance( std::begin( BuildModeMappings::NAMES ), found_name ) );
		}
		else
		{
			destination = BuildMode::Release;
		}
	}

	inline void ConvertFromString( const std::string_view source, PlatformType& destination )
	{
		// To simplify the name qualification.
		using namespace Core::Bootstrap::Internal;


		auto found_name = std::find( std::begin( PlatformTypeMappings::NAMES ), std::end( PlatformTypeMappings::NAMES ), source );
		EXPECTS_DEBUG( found_name != std::end( PlatformTypeMappings::NAMES ) );

		if( found_name != std::end( PlatformTypeMappings::NAMES ) )
		{
			destination = static_cast<PlatformType>( std::distance( std::begin( PlatformTypeMappings::NAMES ), found_name ) );
		}
		else
		{
			destination = PlatformType::Unknown;
		}
	}

	inline void ConvertFromString( const std::string_view source, PlatformEndianness& destination )
	{
		// To simplify the name qualification.
		using namespace Core::Bootstrap::Internal;


		auto found_name = std::find( std::begin( PlatformEndiannessMappings::NAMES ), std::end( PlatformEndiannessMappings::NAMES ), source );
		EXPECTS_DEBUG( found_name != std::end( PlatformEndiannessMappings::NAMES ) );

		if( found_name != std::end( PlatformEndiannessMappings::NAMES ) )
		{
			destination = static_cast<PlatformEndianness>( std::distance( std::begin( PlatformEndiannessMappings::NAMES ), found_name ) );
		}
		else
		{
			destination = PlatformEndianness::Unknown;
		}
	}

	inline void ConvertToString( const BuildMode& source, std::string& destination )
	{
		destination = Core::Bootstrap::Internal::BuildModeMappings::NAMES[ Black::GetEnumValue( source ) ];
	}

	inline void ConvertToString( const PlatformType& source, std::string& destination )
	{
		destination = Core::Bootstrap::Internal::PlatformTypeMappings::NAMES[ Black::GetEnumValue( source ) ];
	}

	inline void ConvertToString( const PlatformEndianness& source, std::string& destination )
	{
		destination = Core::Bootstrap::Internal::PlatformEndiannessMappings::NAMES[ Black::GetEnumValue( source ) ];
	}
}
