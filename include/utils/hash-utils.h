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
	inline const uint32_t GetUnreliableHash( Black::PlainView<const uint8_t> data, const uint32_t seed = 0 );

	/**
		@brief	Hash the given data using reliable function.
		Results of reliable hash functions may be freely used over application, including the file operations and network interactions.
		@note			'Reliable' means here that the result of hash function depends only on input data and seed.
		@param	data	The data stream to be hashed.
		@param	seed	Initial value of hash.
		@return			The value returned is an has of given data, considering the given seed.
	*/
	//const uint32_t GetReliableHash( Black::PlainView<const uint8_t> data, const uint32_t seed = 0 );

	/**
		@brief	Hash the given data using reliable function.
		Results of reliable hash functions may be freely used over application, including the file operations and network interactions.
		@note			'Reliable' means here that the result of hash function depends only on input data and seed.
		@param	data	The data stream to be hashed.
		@param	seed	Initial value of hash.
		@return			The value returned is an has of given data, considering the given seed.
	*/
	//const uint64_t GetReliableLongHash( Black::PlainView<const uint8_t> data, const uint64_t seed = 0 );
}
}
}
