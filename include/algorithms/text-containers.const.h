#pragma once


namespace Black
{
inline namespace Core
{
inline namespace TextUtils
{
	// Text splitting variant specification.
	enum class TextSplittingFlag : uint32_t
	{
		Trim			= 0x01UL,	// Trim the parts before storing.
		DropEmpty		= 0x02UL,	// Drop empty splitted parts.
		OnlyUnique		= 0x04UL,	// Store only unique parts.
		OnlySplitted	= 0x08UL,	// Don't store any value if input string can not be splitted.
	};

	// Text splitting options.
	using TextSplittingFlags = Black::EnumFlags<TextSplittingFlag>;

	// Text joining variant specification.
	enum class TextJoiningFlag : uint32_t
	{
		Trim			= 0x01UL,	// Join the trimmed parts.
		DropEmpty		= 0x02UL,	// Drop empty parts out of joining.
	};

	// Text joining options.
	using TextJoiningFlags = Black::EnumFlags<TextJoiningFlag>;
}
}
}
