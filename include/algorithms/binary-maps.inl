#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline const bool HasItem( const std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key )
	{
		return storage.find( key ) != storage.end();
	}

	template< typename TStoredKey, typename TNewKey, typename TStoredItem, typename TNewItem, typename TPredicate, typename TAllocator >
	inline const bool UniqueAdd( std::map<TStoredKey, TStoredItem, TPredicate, TAllocator>& storage, TNewKey&& key, TNewItem&& item )
	{
		static_assert( std::is_same_v<std::decay_t<TStoredKey>, std::decay_t<TNewKey>>, "Key of such type is unusable for storage." );
		static_assert( std::is_same_v<std::decay_t<TStoredItem>, std::decay_t<TNewItem>>, "Item of such type can't be added into storage." );
		return std::get<1>( storage.emplace( std::forward<TNewKey>( key ), std::forward<TNewItem>( item ) ) );
	}

	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline const bool RemoveItem( std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key )
	{
		auto found_item = storage.find( key );
		CRET( found_item == storage.end(), false );
		storage.erase( found_item );
		return true;
	}

	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline void DeletePointersAndClear( std::map<TKey, TItem*, TPredicate, TAllocator>& storage )
	{
		using MappedItem = typename std::map<TKey, TItem*, TPredicate, TAllocator>::value_type;

		CRET( storage.empty() );
		std::for_each( storage.begin(), storage.end(), []( const MappedItem& value ){ delete value.second; } );
		storage.clear();
	}

	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline TItem& FindItem( std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key, TItem& default_result )
	{
		const auto found_slot = storage.find( key );
		return ( found_slot != storage.end() )? found_slot->second : default_result;
	}

	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline const TItem& FindItem( const std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key, const TItem& default_result )
	{
		const auto found_slot = storage.find( key );
		return ( found_slot != storage.end() )? found_slot->second : default_result;
	}

	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline Monad<TItem&> FindItem( std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key )
	{
		const auto found_slot = storage.find( key );
		CRET( found_slot == storage.end(), {} );

		return Monad<TItem&>{ found_slot->second };
	}

	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline Monad<const TItem&> FindItem( const std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key )
	{
		const auto found_slot = storage.find( key );
		CRET( found_slot == storage.end(), {} );

		return Monad<const TItem&>{ found_slot->second };
	}
}
}
}
