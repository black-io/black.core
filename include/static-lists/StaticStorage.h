#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
	/**
		@brief	Implementation of universal static storage.

		Static storage is implementation of Service Locator pattern for group of arbitrary types.
		It carries all memory for all stored objects and may destroy all stored content via request. So, the crucial rule is not to store the pointers to
		services out of storage. This storage has outstanding performance on service access, so one does not ever need to store the service pointer out of storage.
		One just can't know the rules and time the particular storage will be cleared.

		The other crucial thing is that the only one instance could be stored in one storage.

		@tparam	TStorageTag		Tagging type to implement the functional separation between different storages.
	*/
	template< typename TStorageTag >
	class StaticStorage final : private Black::NonTransferable
	{
	// Construction and initialization.
	public:
		StaticStorage()		= delete;
		~StaticStorage()	= delete;

	// Public static interface.
	public:
		// Clear the static storage, destroying all the stored services.
		static inline void Clear();

		// Get the particular service.
		template< typename TService >
		static inline TService& GetService();

	// Private static state.
	private:
	};
}
}
}
