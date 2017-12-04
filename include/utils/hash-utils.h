#pragma once


namespace Black
{
inline namespace Core
{
inline namespace HashUtils
{
	/**
		@brief	Hash the given data using unreliable function.
		The unreliable hash function is fast, but is limited in usage.
		@note			'Unreliable' means here that the result of hash function is platform-dependent.
		@warning		Unreliable hashes may not be stored in files or sent over network.
		@param	data	The data stream to be hashed.
		@param	seed	Initial value of hash.
		@return			The value returned is an has of given data, considering the given seed.
	*/
	inline const uint32_t GetUnreliableHash( const void* const memory, const size_t length, const uint32_t seed = 0 );
}
}
}
