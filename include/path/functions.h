#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Path
{
	/**
		@brief	Check that the path is semantically valid.
		This function only checks the rules of some virtual file system.

		@param	path	Suggested path to be checked.
		@return			`true` for valid path.
	*/
	const bool IsValidPath( Black::StringView path );

	/**
		@brief	Check that the path has no redundant symbols.
		Whenever the path contains come dot entities or sequential slashes, the one is not normalized.

		@param	path	Suggested path to be checked.
		@return			`true` for normalized path.
	*/
	const bool IsNormalizedPath( Black::StringView path );

	/**
		@brief	Check that the path is absolute.
		The absolute path always begins from UNC, root slash or root drive.

		@param	path	Suggested path to be checked.
		@return			`true` for absolute path.
	*/
	const bool IsAbsolutePath( Black::StringView path );

	/**
		@brief	Check that the path is not absolute.
		The relative path does not begins from UNC, root slash or root drive.

		@param	path	Suggested path to be checked.
		@return			`true` for relative path.
	*/
	const bool IsRelativePath( Black::StringView path );

	/**
		@brief	Transform the path to normalized variant.
		The function collapses any redundant patterns, so that "A//B", "A/B/", "A/./B" or "A/FOO/../B" will be transformed into "A/B".

		@param	path	Suggested path to be normalized.
	*/
	void MakeNormalizedPath( std::string& path );

	/**
		@brief	Transform the relative path into absolute.
		Normally, this function may work like `JoinPath( GetWorkingFolder(), path )`.
		The function does nothing in case of `path` is already absolute.

		@param	path	Suggested path to be transformed.
	*/
	void MakeAbsolutePath( std::string& path );

	/**
		@brief	Transform the absolute path into relative against some root path.
		@note	In some cases, transformed path may be not truly relative, since there may be no common path between suggested root and given path.

		@param	path	Suggested path to be transformed.
		@param	root	The path to be used as common root.
	*/
	void MakeRelativePath( std::string& path, Black::StringView root );

	/**
		@brief	Transform the path, adding the tail name to its end.

		@param	path	Suggested path to be transformed.
		@param	tail	The new tail for path.
	*/
	void AddPathTail( std::string& path, Black::StringView tail );

	/**
		@brief	Transform the path, removing the tail name from it.
		@note	The function has no effect in case of empty path.
		@note	`ExtractPathTail` function may be used to get the removed tail.

		@param	path	Suggested path to e transformed.
	*/
	void RemovePathTail( std::string& path );

	/**
		@brief	Transform the path, removing the tail name from it.
		@note	The function has no effect in case of empty path.
		@note	`RemovePathTail` function may be used in order the tail name is not needed.

		@param	path	Suggested path to e transformed.
		@return			The value returned is an name of removed tail.
	*/
	std::string ExtractPathTail( std::string& path );

	/**
		@brief	Get the normalized path of given one.
		The function is very similar to `MakeNormalizedPath`, except the normalized path is returned.

		@param	path	Suggested path to be normalized.
		@return			The value returned is an normalized variant of suggested path.
	*/
	std::string GetNormalizedPath( Black::StringView path );

	/**
		@brief	Get the absolute path of given one.
		The function is very similar to `MakeAbsolutePath`, except the absolute path is returned.

		@param	path	Suggested path to be transformed.
		@return			The value returned is an absolute variant of suggested path.
	*/
	std::string GetAbsolutePath( Black::StringView path );

	/**
		@brief	Get the relative path from given one, using some root as common part.
		The function is very similar to `MakeRelativePath`, except the relative path is returned.

		@param	path	Suggested path to be converted.
		@param	root	The path to be used as common root.
		@return			The value returned is an relative path, where the `JoinPath( root, result )` will be equal to `path`.
	*/
	std::string GetRelativePath( Black::StringView path, Black::StringView root );

	/**
		@brief	Get the common root path between two given paths.
		@Note	The function may return empty path in case the suggested paths has not common root.

		@param	left_path	The first path.
		@param	right_path	The second path.
		@return				The value returned is an common root, which is same between two given paths.
		@retval	{}			In case the suggested paths has no common root.
	*/
	std::string GetCommonPath( Black::StringView left_path, Black::StringView right_path );

	/**
		@brief	Get the new path, joining the tail to given one.
		The function is very similar to `AddPathTail`, except the result path is returned.

		@param	path	Suggested path to be extended.
		@param	tail	The tail to extend the path.
		@return			The value returned is an result of joining the `path` with `tail`.
	*/
	std::string JoinPath( Black::StringView path, Black::StringView tail );

	/**
		@brief	Get the new path, joining the parts of given collection.
		The function is very similar to `AddPathTail`, except the result path is returned.

		@param	parts	Collection of parts to be joined into path.
		@return			The value returned is an result of sequential joining the `parts`.
	*/
	std::string JoinPath( const std::vector<Black::StringView>& parts );

	/**
		@brief	Split the given path into [Directory, Basename] pair.
		Formally, the basename is an tail of path.

		@param	path	Suggested path to be splitted.
		@return			The value returned is an pair of [Directory, Basename] parts.
	*/
	std::pair<std::string, std::string> SplitPathBasename( Black::StringView path );

	/**
		@brief	Split the given path into [Path, Extension] pair.
		The path extension is the last part of path after the last dot symbol.

		@param	path	Suggested path to be splitted.
		@return			The value returned is an pair of [Path, Extension] parts.
	*/
	std::pair<std::string, std::string> SplitPathExtension( Black::StringView path );

	/**
		@brief	Split the given path into [Drive, Directory] pair.
		Commonly, the path drive is well known on 'Windows' platform.
		Also, the UNC may be considered as path drive.

		@param	path	Suggested path to be splitted.
		@return			The value returned is an pair of [Drive, Directory] parts.
	*/
	std::pair<std::string, std::string> SplitPathDrive( Black::StringView path );

	/**
		@brief	Get the basename of path.
		This function is very similar to `SplitPathBasename`, except the result is only basename of path.

		@param	path	Suggested path to get the basename.
		@return			The value returned is an basename of suggested path.
	*/
	std::string GetPathBasename( Black::StringView path );

	/**
		@brief	Get the path directory.
		This function is very similar to `SplitPathBasename`, except the result is only directory of path.

		@param	path	Suggested path to get the directory.
		@return			The value returned is an directory of suggested path.
	*/
	std::string GetPathDirectory( Black::StringView path );

	/**
		@brief	Get the path extension.
		This function is very similar to `SplitPathExtension`, except the result is only extension of path.

		@param	path	Suggested path to get the extension.
		@return			The value returned is an extension of suggested path.
	*/
	std::string GetPathExtension( Black::StringView path );

	/**
		@brief	Get the path drive.
		This function is very similar to `SplitPathDrive`, except the result is only drive of path.

		@param	path	Suggested path to get the drive.
		@return			The value returned is an drive of suggested path.
	*/
	std::string GetPathDrive( Black::StringView path );
}
}
}
