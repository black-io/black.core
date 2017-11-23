#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Utils
{
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool IsItemExists( const TStorage<TItem, TAllocator>& storage, const TItem& item )
	{
		return std::find( std::begin( storage ), std::end( storage ), item ) != std::end( storage );
	}

	template< typename TItem, size_t ARRAY_LENGTH >
	inline const bool IsItemExists( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item )
	{
		return std::find( std::begin( storage ), std::end( storage ), item ) != std::end( storage );
	}

	template< typename TItem >
	inline const bool IsItemExists( const PlainView<TItem>& storage, const TItem& item )
	{
		return std::find( std::begin( storage ), std::end( storage ), item ) != std::end( storage );
	}

	template< typename TItem >
	inline const bool IsItemExists( const PlainVector<TItem>& storage, const TItem& item )
	{
		return std::find( std::begin( storage ), std::end( storage ), item ) != std::end( storage );
	}

	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool UniqueAdd( TStorage<TItem, TAllocator>& storage, const TItem& item )
	{
		CRET( IsItemExists( storage, item ), false );
		storage.push_back( item );
		return true;
	}

	template< typename TItem, typename TAllocator >
	inline const size_t UniqueAddIndexed( std::vector<TItem, TAllocator>& storage, const TItem& item )
	{
		auto found_item = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_item != std::end( storage ), std::distance( std::begin( storage ), found_item ) );
		storage.push_back( item );
		return storage.size() - 1;
	}

	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool RemoveItem( TStorage<TItem, TAllocator>& storage, const TItem& item )
	{
		CRET( storage.empty(), false );
		auto found_item = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_item == std::end( storage ), false );
		storage.erase( found_item );
		return true;
	}

	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline void DeletePointersAndClear( TStorage<TItem*, TAllocator>& storage )
	{
		CRET( storage.empty() );
		std::for_each( std::begin( storage ), std::end( storage ), []( const TItem* item ){ delete item; } );
		storage.clear();
	}

	template< typename TItem >
	inline void DeletePointersAndClear( PlainVector<TItem*>& storage )
	{
		CRET( storage.IsEmpty() );
		std::for_each( std::begin( storage ), std::end( storage ), []( const TItem* item ){ delete item; } );
		storage.clear();
	}

	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const size_t GetItemIndex( const TStorage<TItem, TAllocator>& storage, const TItem& item )
	{
		CRET( storage.empty(), Black::UNDEFINED_INDEX );
		auto found_item = std::find( std::begin( storage ), std::end( storage ), item );
		return ( found_item == std::end( storage ) )? Black::UNDEFINED_INDEX : std::distance( std::begin( storage ), found_item );
	}

	template< typename TItem, size_t ARRAY_LENGTH >
	inline const size_t GetItemIndex( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item )
	{
		auto found_item = std::find( std::begin( storage ), std::end( storage ), item );
		return ( found_item == std::end( storage ) )? Black::UNDEFINED_INDEX : std::distance( std::begin( storage ), found_item );
	}

	template< typename TItem >
	inline const size_t GetItemIndex( const PlainView<TItem>& storage, const TItem& item )
	{
		CRET( storage.IsEmpty(), Black::UNDEFINED_INDEX );
		auto found_item = std::find( std::begin( storage ), std::end( storage ), item );
		return ( found_item == std::end( storage ) )? Black::UNDEFINED_INDEX : std::distance( std::begin( storage ), found_item );
	}

	template< typename TItem >
	inline const size_t GetItemIndex( const PlainVector<TItem>& storage, const TItem& item )
	{
		CRET( storage.IsEmpty(), Black::UNDEFINED_INDEX );
		auto found_item = std::find( std::begin( storage ), std::end( storage ), item );
		return ( found_item == std::end( storage ) )? Black::UNDEFINED_INDEX : std::distance( std::begin( storage ), found_item );
	}
}
}
}
