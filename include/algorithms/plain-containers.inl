#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool IsItemPresent( const TStorage<TItem, TAllocator>& storage, const TItem& item )
	{
		return std::find( std::begin( storage ), std::end( storage ), item ) != std::end( storage );
	}

	template< typename TItem, size_t ARRAY_LENGTH >
	inline const bool IsItemPresent( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item )
	{
		return std::find( std::begin( storage ), std::end( storage ), item ) != std::end( storage );
	}

	template< typename TItem >
	inline const bool IsItemPresent( const PlainView<TItem>& storage, const TItem& item )
	{
		return std::find( std::begin( storage ), std::end( storage ), item ) != std::end( storage );
	}

	template< typename TItem >
	inline const bool IsItemPresent( const PlainVector<TItem>& storage, const TItem& item )
	{
		return std::find( std::begin( storage ), std::end( storage ), item ) != std::end( storage );
	}

	template< typename TStoredItem, typename TNewItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool UniqueAdd( TStorage<TStoredItem, TAllocator>& storage, TNewItem&& item )
	{
		static_assert( std::is_same_v<std::remove_cv_t<TStoredItem>, std::remove_cv_t<TNewItem>>, "Item of such type can't be added into storage." );
		CRET( IsItemPresent( storage, item ), false );
		storage.emplace_back( std::forward<TNewItem>( item ) );
		return true;
	}

	template< typename TStoredItem, typename TNewItem, typename TAllocator >
	inline const size_t UniqueAddIndexed( std::vector<TStoredItem, TAllocator>& storage, TNewItem&& item )
	{
		static_assert( std::is_same_v<std::remove_cv_t<TStoredItem>, std::remove_cv_t<TNewItem>>, "Item of such type can't be added into storage." );
		auto found_item = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_item != std::end( storage ), std::distance( std::begin( storage ), found_item ) );
		storage.emplace_back( std::forward<TNewItem>( item ) );
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
		std::for_each( std::begin( storage ), std::end( storage ), []( TItem* item ){ delete item; } );
		storage.clear();
	}

	template< typename TItem >
	inline void DeletePointersAndClear( PlainVector<TItem*>& storage )
	{
		CRET( storage.IsEmpty() );
		std::for_each( std::begin( storage ), std::end( storage ), []( TItem* item ){ delete item; } );
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
