#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Path
{
inline namespace FileSystem
{
	/**
		@brief	Get the current working directory path.
		@note	The function is platform-specific. The value returned is valid consumable path, but it will vary from one platform to another.
		Any relative path applied to filesystem will be considered relative to current working directory.
		`SetWorkingFolder` function may be used to change the current working directory.

		@return	The value returned is an valid global path, which leads the current working directory for current process on current platform.
	*/
	std::string GetWorkingFolder();

	/**
		@brief	Set the current working directory path.
		@note	The function validates the `path`. It have to be valid platform-specific path for current platform.

		@param	path	The new path for current working directory.
		@return			The value returned is an status of changing the current working directory.
	*/
	const bool SetWorkingFolder( Black::StringView path );

	/**
		@brief	Get the private folder path for current system user.
		@note	The function is platform-specific. The value returned is valid consumable path, but it will vary from one platform to another.
		@note	The user private folder depends on current platform user logged in.
		This path may be used to store personal saves, system logs, crash-dumps, personal caches.

		@return	The value returned is an valid global path, which leads to private folder for current user on current platform.
	*/
	std::string GetUserPrivateFolder();

	/**
		@brief	Get the public folder path for current system user.
		@note	The function is platform-specific. The value returned is valid consumable path, but it will vary from one platform to another.
		@note	The user public folder depends on current platform user logged in.
		This path may be used to store screen-shots, public logs, media contend.

		@return	The value returned is an valid global path, which leads to public folder for current user on current platform.
	*/
	std::string GetUserPublicFolder();

	/**
		@brief	Get the private folder path for launched application.
		@note	The function is platform-specific. The value returned is valid consumable path, but it will vary from one platform to another.
		@note	Read-only access considered for application private folder.
		@note	The application private folder is not related to current user logged in.
		Typically this path is the same as module path for this application (the path, where the binary file is placed).

		@return	The value returned is an valid global path, which leads to private folder for current application.
	*/
	std::string GetApplicationPrivateFolder();

	/**
		@brief	Get the public folder path for launched application.
		@note	The function is platform-specific. The value returned is valid consumable path, but it will vary from one platform to another.
		@note	The application public folder is not related to current user logged in.
		This path may be used to store any caches/saves/logs not related on current user.

		@return	The value returned is an valid global path, which leads to public folder for current application.
	*/
	std::string GetApplicationPublicFolder();

	/**
		@brief	Check that the path leads to valid filesystem entity.
		@note	The behavior of function is platform-specific.
		The function may operate with relative paths as well as with global ones.

		@param	path	Suggested path to check.
		@return			`true` for valid path.
	*/
	const bool IsValidFilesystemPath( Black::StringView path );

	/**
		@brief	Check that the path leads to valid filesystem folder.
		@note	The behavior of function is platform-specific.
		The function may operate with relative paths as well as with global ones.

		@param	path	Suggested path to check.
		@return			`true` for valid folder path.
	*/
	const bool IsValidFolderPath( Black::StringView path );

	/**
		@brief	Check that the path leads to valid filesystem file.
		@note	The behavior of function is platform-specific.
		The function may operate with relative paths as well as with global ones.

		@param	path	Suggested path to check.
		@return			`true` for valid file path.
	*/
	const bool IsValidFilePath( Black::StringView path );

	/**
		@brief	Ensure that the path leads to valid folder.
		@note	The behavior of function is platform-specific.
		The function may create the folder, when one does not exist.
		Also, the function may create each parent folder for given path.
		Actually, the folder creation may be failed when the `path` is invalid, or in order of filesystem errors.

		@param	path	Suggested path to the requested folder.
		@return			`true` if folder already exists of just created. `false` when the path can't be used for folder creation.
	*/
	const bool EnsureFolderCreated( Black::StringView path );

	/**
		@brief	Ensure that the folder, represented by path, is deleted.
		@note	The behavior of function is platform-specific.
		This function deletes all the content of requested folder.

		@param	path	Suggested path to the folder for deletion.
		@retun			`true` when the folder already deleted or was deleted while function execution.
	*/
	const bool EnsureFolderDeleted( Black::StringView path );

	/**
		@brief	Copy the file into new location.
		@note	The behavior of function is platform-specific.
		@note	The function will not create missing folders of destination path, considering it invalid.

		@param	source_path			Path to file source. Have to be valid path, which leads to valid file at filesystem.
		@param	destination_path	Destination path for copying. Have to be valid path, which does not leads to valid filesystem entity.
		@return						`true` when the file is copied. `false` in case of error.
	*/
	const bool CopyFile( Black::StringView source_path, Black::StringView destination_path );

	/**
		@brief	Move the file into new location.
		@note	The behavior of function is platform-specific.
		@note	The function will not create missing folders of destination path, considering it invalid.
		Actually, the function has same effect, as renaming of file.

		@param	source_path			Path to file source. Have to be valid path, which leads to valid file at filesystem.
		@param	destination_path	Destination path for copying. Have to be valid path, which does not leads to valid filesystem entity.
		@return						`true` when the file is moved. `false` in case of error.
	*/
	const bool MoveFile( Black::StringView source_path, Black::StringView destination_path );

	/**
		@brief	Get the size of existing file by given path.
		@note	The behavior of function is platform-specific.

		@brief	path	Suggested path to file. Have to be valid path, which leads to valid file at filesystem.
		@return			The value returned is an valid size (in bytes) of file by path.
		@retval	0		In case of some error.
	*/
	Black::size64_t GetFileSize( Black::StringView path );

	/**
		@brief	Get the GMT local time-stamp of last filesystem entity modification.
		@note	The behavior of function is platform-specific.

		@param	path	The path the to requested entity. Have to be valid path, which leads to valid filesystem entity.
		@return			The value returned is an GMT local time-stamp of last entity modification.
		@retval	0		in case of error or when the path is invalid for current filesystem.
	*/
	std::chrono::seconds GetFilesystemModificationTime( Black::StringView path );

	/**
		@brief	Look for filesystem entities.
		@note	The behavior of function is platform-specific.

		@param	path		The path to start lookup.
		@param	mask		The mask to look for entities.
		@param	flags		The lookup settings.
		@return				The value returned is an pair of { Files, Folders } path lists.
		@retval	{ {}, {} }	Empty lists will be returned in case of error or when nothing found.
	*/
	std::pair<Black::PathList, Black::PathList> FindFilesystemEntities( Black::StringView path, Black::StringView mask, Black::FilesystemLookupFlags flags );

	/**
		@brief	Look for filesystem entities.
		@note	The behavior of function is platform-specific.

		@param	path	The path to start lookup.
		@param	mask	The mask to look for entities.
		@param	flags	The lookup settings.
		@return			The value returned is the list of found folders.
		@retval	{}		Empty list will be returned in case of error or when nothing found.
	*/
	Black::PathList FindFilesystemFolders( Black::StringView path, Black::StringView mask, Black::FilesystemLookupFlags flags );

	/**
		@brief	Look for filesystem entities.
		@note	The behavior of function is platform-specific.

		@param	path	The path to start lookup.
		@param	mask	The mask to look for entities.
		@param	flags	The lookup settings.
		@return			The value returned is the list of found files.
		@retval	{}		Empty list will be returned in case of error or when nothing found.
	*/
	Black::PathList FindFilesystemFiles( Black::StringView path, Black::StringView mask, Black::FilesystemLookupFlags flags );
}
}
}
}
