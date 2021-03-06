#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
namespace Internal
{
	// Helper to determine the length of unknown string type. This branch helps to know the length of single char.
	template< typename TCandidate >
	inline auto GetStringLength( const TCandidate& candidate ) -> std::enable_if_t<IS_VALID_CHAR<TCandidate>, const size_t>
	{
		return 1;
	}

	// Helper to determine the length of unknown string type. This branch helps to know the length of string or string view.
	template< typename TCandidate >
	inline auto GetStringLength( const TCandidate& candidate ) -> decltype( candidate.length() )
	{
		return candidate.length();
	}
}
}
}
}
