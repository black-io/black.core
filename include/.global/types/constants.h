#pragma once


namespace Black
{
	// 'Undefined' state of any index.
	inline constexpr size_t UNDEFINED_INDEX = static_cast<size_t>( -1 );

	// Type of common result for some regular function which indicates the failure or success of job the function performs.
	enum class BooleanStatus : bool
	{
		Failure = false,	// The function didn't perform its job well.
		Success = true,		// The function completed successfully.
	};
}
