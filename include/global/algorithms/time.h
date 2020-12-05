#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Algorithms
{
	/**
		@brief	Translation from `std::chrono` time into `Black::Time` seconds.
		@param	duration	Time interval, represented in `std::chrono` format.
		@return				Return value is an equivalent amount of seconds, including fractions of second.
	*/
	template< typename TCounterType, typename TPeriodType >
	inline const Black::Time GetTimeFromDuration( const std::chrono::duration<TCounterType, TPeriodType>& duration )
	{
		return std::chrono::duration_cast<TimeDuration>( duration ).count();
	}

	/**
		@brief	Translation from `Black::Time` seconds into `std::chrono` time.
		@param	seconds		Time interval, represented by amount of seconds.
		@return				Return value is an `std::chrono::nanoseconds` equivalent of `seconds`.
	*/
	template< typename TCounterType = int64_t, typename TPeriodType = std::nano >
	inline auto GetDurationFromSeconds( const Black::Time seconds )
	{
		return std::chrono::duration_cast<std::chrono::duration<TCounterType, TPeriodType>>( TimeDuration{ seconds } );
	}
}
}
}
}
