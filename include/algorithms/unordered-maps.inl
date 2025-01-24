#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline const bool HasItem( const std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key )
	{
		return storage.find( key ) != storage.end();
	}

	template< typename TStoredKey, typename TNewKey, typename TStoredItem, typename TNewItem, typename THash, typename TPredicate, typename TAllocator >
	inline const bool UniqueAdd( std::unordered_map<TStoredKey, TStoredItem, THash, TPredicate, TAllocator>& storage, TNewKey&& key, TNewItem&& item )
	{
		static_assert( std::is_same_v<std::decay_t<TStoredKey>, std::decay_t<TNewKey>>, "Key of such type is unusable for storage." );
		static_assert( std::is_same_v<std::decay_t<TStoredItem>, std::decay_t<TNewItem>>, "Item of such type can't be added into storage." );
		return std::get<1>( storage.emplace( std::forward<TNewKey>( key ), std::forward<TNewItem>( item ) ) );
	}

	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline const bool RemoveItem( std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key )
	{
		auto found_item = storage.find( key );
		CRET( found_item == storage.end(), false );
		storage.erase( found_item );
		return true;
	}

	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline void DeletePointersAndClear( std::unordered_map<TKey, TItem*, THash, TPredicate, TAllocator>& storage )
	{
		using MappedItem = typename std::unordered_map<TKey, TItem*, THash, TPredicate, TAllocator>::value_type;

		CRET( storage.empty() );
		std::for_each( storage.begin(), storage.end(), []( const MappedItem& value ){ delete value.second; } );
		storage.clear();
	}

	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline TItem& FindItem( std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, TItem& default_result )
	{
		auto found_item = storage.find( key );
		return ( found_item != storage.end() )? found_item->second : default_result;
	}

	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline const TItem& FindItem( const std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, const TItem& default_result )
	{
		auto found_item = storage.find( key );
		return ( found_item != storage.end() )? found_item->second : default_result;
	}

	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator, typename TFunction >
	inline const bool FindItem( std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, TFunction on_found )
	{
		static_assert( std::is_invocable_v<TFunction, TItem&>, "The callback `on_found` can't be used with given storage." );

		auto found_item = storage.find( key );
		CRET( found_item == storage.end(), false );

		on_found( found_item->second );
		return true;
	}

	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator, typename TFunction >
	inline const bool FindItem( const std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, TFunction on_found )
	{
		static_assert( std::is_invocable_v<TFunction, const TItem&>, "The callback `on_found` can't be used with given storage." );

		auto found_item = storage.find( key );
		CRET( found_item == storage.end(), false );

		on_found( found_item->second );
		return true;
	}
}
}
}
