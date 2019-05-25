#pragma once


namespace Black
{
	/**
		@brief	Translation from `std::chrono` time into `double` seconds.
		@param	duration	Time interval, represented in `std::chrono` format.
		@return				Return value is an equivalent amount of seconds, including fractions of second.
	*/
	template< typename TCounterType, typename TPeriodType >
	inline const Time GetSecondsFromDuration( const std::chrono::duration<TCounterType, TPeriodType>& duration )
	{
		return std::chrono::duration_cast<TimeDuration>( duration ).count();
	}

	/**
		@brief	Translation from `Time` seconds into `std::chrono` time.
		@param	seconds		Time interval, represented by amount of seconds.
		@return				Return value is an `std::chrono::nanoseconds` equivalent of `seconds`.
	*/
	template< typename TCounterType = int64_t, typename TPeriodType = std::nano >
	inline auto GetDurationFromSeconds( const Time seconds )
	{
		return std::chrono::duration_cast<std::chrono::duration<TCounterType, TPeriodType>>( TimeDuration{ seconds } );
	}
}
