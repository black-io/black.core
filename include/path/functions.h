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
		The function collapses any redundant patterns, so that "A//B", "A/B/", "A/./B" or "A/foo/../B" will be transformed into "A/B".

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
	*/
	std::string GetNormalizedPath( Black::StringView path );

	/**
	*/
	std::string GetAbsoluteString( Black::StringView path );

	/**
	*/
	std::string GetRelativePath( Black::StringView path, Black::StringView root );

	/**
	*/
	std::string GetCommonPath( Black::StringView left_path, Black::StringView right_path );

	/**
	*/
	std::string JoinPath( Black::StringView path, Black::StringView tail );

	/**
	*/
	std::string JoinPath( const std::vector<Black::StringView>& parts );

	/**
	*/
	std::pair<std::string, std::string> SplitPathBasename( Black::StringView path );

	/**
	*/
	std::pair<std::string, std::string> SplitPathExtension( Black::StringView path );

	/**
	*/
	std::pair<std::string, std::string> SplitPathDrive( Black::StringView path );

	/**
	*/
	std::string GetPathBasename( Black::StringView path );

	/**
	*/
	std::string GetPathDirectoryName( Black::StringView path );

	/**
	*/
	std::string GetPathDrive( Black::StringView path );

	/**
	*/
	std::string GetPathExtension( Black::StringView path );
}
}
}
