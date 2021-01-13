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
	class StaticStorage final : private Internal::BasicStaticList<TStorageTag>
	{
	// Construction and initialization.
	public:
		StaticStorage()		= delete;
		~StaticStorage()	= delete;

	// Public static interface.
	public:
		// Get the particular service.
		template< typename TService >
		static inline TService& Get();

		// Clear the static storage, destroying all the stored services and decoupling the nodes.
		static inline void Clear();

	// Private inner types.
	private:
		// Type of basic static list.
		using Parent = Internal::BasicStaticList<TStorageTag>;

		// Type of nodes of storage.
		using CommonNode = typename Parent::Node;

		// Type of particular node.
		template< typename TImplementation >
		using Node = Internal::StaticStorageNode<TStorageTag, TImplementation>;
	};
}
}
}
