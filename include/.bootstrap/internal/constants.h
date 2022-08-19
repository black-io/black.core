#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Bootstrap
{
namespace Internal
{
	/**
		@brief	Mapping to support the conversion from `Black::BuildMode` constants to string values.
	*/
	struct BuildModeMappings final
	{
		// Names of corresponded enumeration values.
		static inline constexpr std::string_view NAMES[] {
			"debug",	// Black::BuildMode::Debug
			"draft",	// Black::BuildMode::Draft
			"release",	// Black::BuildMode::Release
		};
	};

	/**
		@brief	Mapping to support the conversion from `Black::PlatformType` constants to string values.
	*/
	struct PlatformTypeMappings final
	{
		// Names of corresponded enumeration values.
		static inline constexpr std::string_view NAMES[] {
			"unknown",	// Black::PlatformType::Unknown
			"windows",	// Black::PlatformType::WindowsDesktop
			"macos",	// Black::PlatformType::MacOs
			"linux",	// Black::PlatformType::Linux
			"android",	// Black::PlatformType::Android
			"ios",		// Black::PlatformType::Ios
		};
	};

	/**
		@brief	Mapping to support the conversion from `Black::PlatformEndianness` constants to string values.
	*/
	struct PlatformEndiannessMappings final
	{
		// Names of corresponded enumeration values.
		static inline constexpr std::string_view NAMES[] {
			"unknown",			// Black::PlatformEndianness::Unknown
			"little-endian",	// Black::PlatformEndianness::LittleEndian
			"big-endian",		// Black::PlatformEndianness::BigEndian
		};
	};
}
}
}
}
