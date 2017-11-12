#pragma once


namespace Black
{
	// Build mode specification.
	enum class BuildMode
	{
		Debug		= 0,	// Framework builds in `debug` mode. No optimizations, all checks enabled, verbose logging, verbose debug information, leaks detection.
		Draft,				// Framework builds in `draft release` mode. All as for `debug`, except optimization and memory leaks detection.
		Release,			// Framework builds in `release` mode. Strong speed optimization, no checks, poor logging.
	};

	// Target platform specification.
	enum class PlatformType
	{
		Unknown			= 0x0000U,	// Current platform is unknown.
		WindowsDesktop	= 0x0001U,	// Current platform is Microsoft Windows for desktops.
		MacOs			= 0x0002U,	// Current platform is Apple MacOs.
		Linux			= 0x0003U,	// Current platform is some of Linux family.
		Android			= 0x0101U,	// Current platform is Google Android device.
		Ios				= 0x0102U,	// Current platform is Apple iOS device.
		WindowsMobile	= 0x0103U,	// Current platform is Microsoft Windows mobile device.
		Tizen			= 0x0104U,	// Current platform is Tizen mobile device.
	};

	// Target platform endianness specification.
	enum class PlatformEndianness
	{
		Unknown			= 0,	// Current endianness is unknown.
		LittleEndian,			// Current platform is little-endian (Intel, IBM PC).
		BigEndian,				// Current platform is big-endian (Motorola, Macintosh).
		PdpEndian,				// Current platform is per-word big endian, but words are little-endian.
	};
}
