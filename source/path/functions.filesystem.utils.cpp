#include <black.path.h>


namespace Black
{
inline namespace Core
{
inline namespace Path
{
inline namespace FileSystem
{
	const bool IsValidFilesystemPath( Black::StringView path )
	{

	}

	const bool IsValidFolderPath( Black::StringView path )
	{

	}

	const bool IsValidFilePath( Black::StringView path )
	{

	}

	const bool EnsureFolderCreated( Black::StringView path )
	{

	}

	const bool EnsureFolderDeleted( Black::StringView path )
	{

	}

	const bool CopyFile( Black::StringView source_path, Black::StringView destination_path )
	{

	}

	const bool MoveFile( Black::StringView source_path, Black::StringView destination_path )
	{

	}

	Black::size64_t GetFileSize( Black::StringView path )
	{

	}

	std::chrono::seconds GetFilesystemModificationTime( Black::StringView path )
	{

	}

	std::pair<Black::PathList, Black::PathList> FindFilesystemEntities( Black::StringView path, Black::StringView mask, Black::FilesystemLookupFlags flags )
	{

	}

	Black::PathList FindFilesystemFolders( Black::StringView path, Black::StringView mask, Black::FilesystemLookupFlags flags )
	{

	}

	Black::PathList FindFilesystemFiles( Black::StringView path, Black::StringView mask, Black::FilesystemLookupFlags flags )
	{

	}
}
}
}
}
