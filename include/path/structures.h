#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Path
{
	// Regular list of paths.
	using PathList = std::deque<std::string>;

	// Filesystem lookup options for file/folder lookup.
	using FilesystemLookupFlags = Black::EnumFlags<FilesystemLookupOptions>;
}
}
}
