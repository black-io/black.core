#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Utils
{
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline const bool IsItemExists( const std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key )
	{
		return storage.find( key ) != storage.end();
	}

	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline const bool UniqueAdd( std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, const TItem& item )
	{
		return std::get<1>( storage.insert( std::make_pair( key, item ) ) );
	}

	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline const bool UniqueAdd( std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, TItem&& item )
	{
		return std::get<1>( storage.insert( std::make_pair( key, std::move( item ) ) ) );
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
}
}
}
