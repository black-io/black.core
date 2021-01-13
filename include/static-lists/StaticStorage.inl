#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
	template< typename TStorageTag >
	inline void StaticStorage<TStorageTag>::Clear()
	{
		Parent::EnumerateNodes( []( CommonNode* node ) { node->Invalidate(); } );
		Parent::Clear();
	}

	template< typename TStorageTag >
	template< typename TService >
	inline TService& StaticStorage<TStorageTag>::Get()
	{
		static Node<TService> storage{};
		return *storage;
	}
}
}
}
