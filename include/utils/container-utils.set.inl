#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Utils
{
	template< typename TItem, typename TPredicate, typename TAllocator >
	inline const bool IsItemExists( const std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item )
	{
		return storage.find( item ) != storage.end();
	}

	template< typename TItem, typename TPredicate, typename TAllocator >
	inline const bool UniqueAdd( std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item )
	{
		return std::get<1>( storage.insert( item ) );
	}

	template< typename TItem, typename TPredicate, typename TAllocator >
	inline const bool RemoveItem( std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item )
	{
		auto found_item = storage.find( item );
		CRET( storage.end() == found_item, false );
		storage.erase( found_item );
		return true;
	}
}
}
}
