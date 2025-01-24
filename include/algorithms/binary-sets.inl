#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
	template< typename TItem, typename TPredicate, typename TAllocator >
	inline const bool HasItem( const std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item )
	{
		return storage.find( item ) != storage.end();
	}

	template< typename TStoredItem, typename TNewItem, typename TPredicate, typename TAllocator >
	inline const bool UniqueAdd( std::set<TStoredItem, TPredicate, TAllocator>& storage, TNewItem&& item )
	{
		static_assert( std::is_same_v<std::decay_t<TStoredItem>, std::decay_t<TNewItem>>, "Item of such type can't be added into storage." );
		return std::get<1>( storage.emplace( std::forward<TNewItem>( item ) ) );
	}

	template< typename TItem, typename TPredicate, typename TAllocator >
	inline const bool RemoveItem( std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item )
	{
		auto found_item = storage.find( item );
		CRET( found_item == storage.end(), false );
		storage.erase( found_item );
		return true;
	}
}
}
}
