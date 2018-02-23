#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Path
{
	/**
	*/
	const bool IsValidPath( Black::StringView path );

	/**
	*/
	const bool IsNormalizedPath( Black::StringView path );

	/**
	*/
	const bool IsAbsolutePath( Black::StringView path );

	/**
	*/
	const bool IsRelativePath( Black::StringView path );

	/**
	*/
	void MakeNormalizedPath( std::string& path );

	/**
	*/
	void MakeAbsolutePath( std::string& path );

	/**
	*/
	void MakeRelativePath( std::string& path, Black::StringView root );

	/**
	*/
	void AddPathTail( std::string& path, Black::StringView tail );

	/**
	*/
	void RemovePathTail( std::string& path );

	/**
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
