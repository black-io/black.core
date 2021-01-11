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
	}

	template< typename TStorageTag >
	template< typename TService >
	inline TService& StaticStorage<TStorageTag>::GetService()
	{
	}
}
}
}
