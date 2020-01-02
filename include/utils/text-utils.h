#pragma once


namespace Black
{
inline namespace Core
{
inline namespace TextUtils
{
	/**
		@brief	Format the arguments into string.
		Uses formatting syntax similar to `str.format` from Python.
		Syntax documentation : http://cppformat.github.io/latest/syntax.html
		@param	format		Declares the format, how `arguments` must be placed in output string.
		@param	arguments	The arguments to be formatted.
		@tparam	TChar		Type of string character.
		@tparam	TArguments	Types of passed arguments.
		@return				The value returned is an formatted string.
	*/
	template< typename TChar, typename TTraits, typename TAllocator, typename... TArguments >
	inline std::basic_string<TChar, TTraits, TAllocator> FormatString(
		const std::basic_string<TChar, TTraits, TAllocator>& format,
		const TArguments&... arguments
	);

	/**
		@brief	Format the arguments into string.
		Uses formatting syntax similar to `str.format` from Python.
		Syntax documentation : http://cppformat.github.io/latest/syntax.html
		@param	buffer		Storage buffer for formatted string.
		@param	format		Declares the format, how `arguments` must be placed in output string.
		@param	arguments	The arguments to be formatted.
		@tparam	TChar		Type of string character.
		@tparam	TArguments	Types of passed arguments.
		@return				The value returned is an string view into `buffer` with formatted arguments.
	*/
	template< typename TChar, typename TTraits, typename TAllocator, typename... TArguments >
	inline Black::RegularStringView<TChar> FormatString(
		Black::PlainView<TChar> buffer,
		const std::basic_string<TChar, TTraits, TAllocator>& format,
		const TArguments&... arguments
	);

	/**
		@brief	Replace some string pattern with given replacement inside string buffer.
		@param	string_buffer	The string to be modified.
		@param	pattern			String pattern to search.
		@param	replacement		String to replace the `pattern`.
		@tparam	TChar			Type of string character.
		@tparam	TTraits			String traits.
		@tparam	TAllocator		String allocator.
	*/
	template< typename TChar, typename TTraits, typename TAllocator >
	inline void ReplaceSubstring(
		std::basic_string<TChar, TTraits, TAllocator>& string_buffer,
		Black::RegularStringView<TChar> pattern,
		Black::RegularStringView<TChar> replacement
	);

	/**
		@brief	Convert the string into its upper-case form.
		@param	string_buffer	Input string to be converted.
		@tparam TChar			Type of string character.
		@return					The value returned is and converted string.
	*/
	template< typename TChar >
	inline std::basic_string<TChar> GetUpperCase( Black::RegularStringView<TChar> string_buffer );

	/**
		@brief	Convert each char of string into upper-case form.
		@param	string_buffer	Input string to be converted.
		@tparam TChar			Type of string character.
		@tparam	TTraits			String traits.
		@tparam	TAllocator		String allocator.
	*/
	template< typename TChar, typename TTraits, typename TAllocator >
	inline void MakeUpperCase( std::basic_string<TChar, TTraits, TAllocator>& string_buffer );

	/**
		@brief	Convert the string into its lower-case form.
		@param	string_buffer	Input string to be converted.
		@tparam TChar			Type of string character.
		@return					The value returned is and converted string.
	*/
	template< typename TChar >
	inline std::basic_string<TChar> GetLowerCase( Black::RegularStringView<TChar> string_buffer );

	/**
		@brief	Convert each char of string into lower-case form.
		@param	string_buffer	Input string to be converted.
		@tparam TChar			Type of string character.
		@tparam	TTraits			String traits.
		@tparam	TAllocator		String allocator.
	*/
	template< typename TChar, typename TTraits, typename TAllocator >
	inline void MakeLowerCase( std::basic_string<TChar, TTraits, TAllocator>& string_buffer );

	/**
		@brief	Get the trimmed (without non-printable chars at left and right) form of string.
		@param	string_buffer	Input string to be trimmed.
		@tparam TChar			Type of string character.
		@return					The value returned is and trimmed string.
	*/
	template< typename TChar >
	inline std::basic_string<TChar> GetTrimmedString( Black::RegularStringView<TChar> string_buffer );

	/**
		@brief	Remove the non-printable chars from left and right of string.
		The function accepts any type of rearrangeable string, e.g. `std::string` or `Black::StringView`.

		@param	string_buffer	Input string to be trimmed.
		@tparam TStringBuffer	Acceptable type of regular rearrangeable string.
	*/
	template< typename TStringBuffer >
	inline void MakeTrimmedString( TStringBuffer& string_buffer );

	/**
		@brief	Join the string parts into single string using pattern.
		@param	parts				Given parts to join.
		@param	pattern				Joining pattern.
		@param	flags				Joining flags.
		@tparam	TPartStorage		Type of storage, where the given parts stored.
		@tparam	TPattern			Type of given pattern. Any type of string char or string are accepted.
		@tparam	TOutStorage			Type of result string, where the joined parts will be stored.
		@return						The value returned is an joined parts into single string.
	*/
	template< typename TPartStorage, typename TPattern, typename TOutStorage = Internal::StringStorage<typename TPartStorage::value_type> >
	inline TOutStorage JoinString( const TPartStorage& parts, const TPattern& pattern, const TextJoiningFlags flags = { TextJoiningFlag::DropEmpty } );

	/**
		@brief	Splits input string buffer into fragments, which will be stored into storage according to split options.
		@param	fragments_storage	Storage, where fragments will be stored.
		@param	string_buffer		Input string to be splitted.
		@param	split_pattern		Pattern, that will break string buffer into fragments.
		@param	split_options		Split options, that describes what fragments must be stored and how it must be prepared.
		@tparam	TChar			Type of string character.
		@tparam	TTraits			String traits.
		@tparam	TAllocator	String allocator.
		@tparam	TStorageAllocator	Allocator for `fragments_storage`.
		@tparam	TStorage	Type of `fragments_storage`, `std::vector`, `std::list` or `std::deque` may be used here.
		@return
	*/
	template< typename TStorage, typename TStringBuffer, typename TPattern >
	inline const size_t SplitString(
		TStorage& parts,
		const TStringBuffer& string_buffer,
		const TPattern& pattern,
		const TextSplittingFlags flags = { TextSplittingFlag::DropEmpty, TextSplittingFlag::Trim }
	);
}
}
}
