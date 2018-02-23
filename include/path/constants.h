#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Path
{
	// Filesystem lookup options for file/folder lookup.
	enum class FilesystemLookupOptions : int32_t
	{
		InnerFolders	= 0x01L,	// Make the recursive lookup into inner folders.
		AbsolutePath	= 0x02L,	// Return the list with absolute path names.
	};
}
}
}
