#pragma once


namespace Black
{
	// String conversion routine for build modes.
	inline void ConvertFromString( const std::string_view source, BuildMode& destination );

	// String conversion routine for platform types.
	inline void ConvertFromString( const std::string_view source, PlatformType& destination );

	// String conversion routine for platform endianness.
	inline void ConvertFromString( const std::string_view source, PlatformEndianness& destination );

	// String conversion routine for build modes.
	inline void ConvertToString( const BuildMode& source, std::string& destination );

	// String conversion routine for platform types.
	inline void ConvertToString( const PlatformType& source, std::string& destination );

	// String conversion routine for platform endianness.
	inline void ConvertToString( const PlatformEndianness& source, std::string& destination );
}
