#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool HasItem( const TStorage<TItem, TAllocator>& storage, const TItem& item )
	{
		return std::find( std::begin( storage ), std::end( storage ), item ) != std::end( storage );
	}

	template< typename TItem, size_t ARRAY_LENGTH >
	inline const bool HasItem( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item )
	{
		return std::find( std::begin( storage ), std::end( storage ), item ) != std::end( storage );
	}

	template< typename TItem >
	inline const bool HasItem( const PlainView<TItem>& storage, const TItem& item )
	{
		return std::find( std::begin( storage ), std::end( storage ), item ) != std::end( storage );
	}

	template< typename TItem >
	inline const bool HasItem( const PlainVector<TItem>& storage, const TItem& item )
	{
		return std::find( std::begin( storage ), std::end( storage ), item ) != std::end( storage );
	}

	template< typename TStoredItem, typename TNewItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool UniqueAdd( TStorage<TStoredItem, TAllocator>& storage, TNewItem&& item )
	{
		static_assert( std::is_same_v<std::decay_t<TStoredItem>, std::decay_t<TNewItem>>, "Item of such type can't be added into storage." );
		CRET( HasItem( storage, item ), false );
		storage.emplace_back( std::forward<TNewItem>( item ) );
		return true;
	}

	template< typename TStoredItem, typename TNewItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool UniqueAddSorted( TStorage<TStoredItem, TAllocator>& storage, TNewItem&& item )
	{
		static_assert( std::is_same_v<std::decay_t<TStoredItem>, std::decay_t<TNewItem>>, "Item of such type can't be added into storage." );
		auto found_slot = std::upper_bound( std::begin( storage ), std::end( storage ), item );
		CRET( ( found_slot > std::begin( storage ) ) && !( *std::prev( found_slot ) < item ), false );

		storage.insert( found_slot, std::forward<TNewItem>( item ) );
		return true;
	}

	template< typename TStoredItem, typename TNewItem, typename TPredicate, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool UniqueAddSorted( TStorage<TStoredItem, TAllocator>& storage, TNewItem&& item, const TPredicate& predicate )
	{
		static_assert( std::is_same_v<std::decay_t<TStoredItem>, std::decay_t<TNewItem>>, "Item of such type can't be added into storage." );
		static_assert(
			std::is_invocable_r_v<const bool, TPredicate, const std::decay_t<TStoredItem>&, const std::decay_t<TNewItem>&>,
			"Used predicate should meet the requirement of signature `const bool ( const TStoredItem&, const TNewItem& )`."
		);

		auto found_slot = std::upper_bound( std::begin( storage ), std::end( storage ), item, predicate );
		CRET( ( found_slot > std::begin( storage ) ) && !predicate( *std::prev( found_slot ), item ), false );

		found_slot = storage.insert( found_slot, std::forward<TNewItem>( item ) );
		return true;
	}

	template< typename TStoredItem, typename TNewItem, typename TAllocator >
	inline const size_t UniqueAddIndexed( std::vector<TStoredItem, TAllocator>& storage, TNewItem&& item )
	{
		static_assert( std::is_same_v<std::decay_t<TStoredItem>, std::decay_t<TNewItem>>, "Item of such type can't be added into storage." );
		auto found_item = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_item != std::end( storage ), std::distance( std::begin( storage ), found_item ) );
		storage.emplace_back( std::forward<TNewItem>( item ) );
		return storage.size() - 1;
	}

	template< typename TStoredItem, typename TNewItem, typename TAllocator >
	inline const size_t UniqueAddSortedIndexed( std::vector<TStoredItem, TAllocator>& storage, TNewItem&& item )
	{
		static_assert( std::is_same_v<std::decay_t<TStoredItem>, std::decay_t<TNewItem>>, "Item of such type can't be added into storage." );
		auto found_slot = std::upper_bound( std::begin( storage ), std::end( storage ), item );
		CRET( ( found_slot > std::begin( storage ) ) && !( *std::prev( found_slot ) < item ), std::distance( std::begin( storage ), found_slot ) - 1 );

		found_slot = storage.insert( found_slot, std::forward<TNewItem>( item ) );
		return std::distance( std::begin( storage ), found_slot );
	}

	template< typename TStoredItem, typename TNewItem, typename TPredicate, typename TAllocator >
	inline const size_t UniqueAddSortedIndexed( std::vector<TStoredItem, TAllocator>& storage, TNewItem&& item, const TPredicate& predicate )
	{
		static_assert( std::is_same_v<std::decay_t<TStoredItem>, std::decay_t<TNewItem>>, "Item of such type can't be added into storage." );
		static_assert(
			std::is_invocable_r_v<const bool, TPredicate, const std::decay_t<TStoredItem>&, const std::decay_t<TNewItem>&>,
			"Used predicate should meet the requirement of signature `const bool ( const TStoredItem&, const TNewItem& )`."
		);

		auto found_slot = std::upper_bound( std::begin( storage ), std::end( storage ), item, predicate );
		CRET( ( found_slot > std::begin( storage ) ) && !predicate( *std::prev( found_slot ), item ), std::distance( std::begin( storage ), found_slot ) - 1 );

		found_slot = storage.insert( found_slot, std::forward<TNewItem>( item ) );
		return std::distance( std::begin( storage ), found_slot );
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
	inline const bool RemoveItemSorted( TStorage<TItem, TAllocator>& storage, const TItem& item )
	{
		CRET( storage.empty(), false );
		auto found_candidate = std::lower_bound( std::begin( storage ), std::end( storage ), item );
		CRET( found_candidate == std::end( storage ), false );
		CRET( ( item < *found_candidate ), false );

		storage.erase( found_candidate );
		return true;
	}

	template< typename TItem, typename TPredicate, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool RemoveItemSorted( TStorage<TItem, TAllocator>& storage, const TItem& item, const TPredicate& predicate )
	{
		CRET( storage.empty(), false );
		auto found_candidate = std::lower_bound( std::begin( storage ), std::end( storage ), item, predicate );
		CRET( found_candidate == std::end( storage ), false );
		CRET( predicate( item, *found_candidate ), false );

		storage.erase( found_candidate );
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
	inline TItem& FindItem( TStorage<TItem, TAllocator>& storage, const TItem& item, TItem& default_result )
	{
		CRET( std::empty( storage ), default_result );
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		return ( found_slot != std::end( storage ) )? *found_slot : default_result;
	}

	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const TItem& FindItem( const TStorage<TItem, TAllocator>& storage, const TItem& item, const TItem& default_result )
	{
		CRET( std::empty( storage ), default_result );
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		return ( found_slot != std::end( storage ) )? *found_slot : default_result;
	}

	template< typename TItem, size_t ARRAY_LENGTH >
	inline TItem& FindItem( TItem (&storage)[ ARRAY_LENGTH ], const TItem& item, TItem& default_result )
	{
		CRET( std::empty( storage ), default_result );
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		return ( found_slot != std::end( storage ) )? *found_slot : default_result;
	}

	template< typename TItem, size_t ARRAY_LENGTH >
	inline const TItem& FindItem( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item, const TItem& default_result )
	{
		CRET( std::empty( storage ), default_result );
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		return ( found_slot != std::end( storage ) )? *found_slot : default_result;
	}

	template< typename TItem >
	inline TItem& FindItem( PlainView<TItem>& storage, const TItem& item, TItem& default_result )
	{
		CRET( std::empty( storage ), default_result );
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		return ( found_slot != std::end( storage ) )? *found_slot : default_result;
	}

	template< typename TItem >
	inline const TItem& FindItem( const PlainView<TItem>& storage, const TItem& item, const TItem& default_result )
	{
		CRET( std::empty( storage ), default_result );
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		return ( found_slot != std::end( storage ) )? *found_slot : default_result;
	}

	template< typename TItem >
	inline TItem& FindItem( PlainVector<TItem>& storage, const TItem& item, TItem& default_result )
	{
		CRET( std::empty( storage ), default_result );
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		return ( found_slot != std::end( storage ) )? *found_slot : default_result;
	}

	template< typename TItem >
	inline const TItem& FindItem( const PlainVector<TItem>& storage, const TItem& item, const TItem& default_result )
	{
		CRET( std::empty( storage ), default_result );
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		return ( found_slot != std::end( storage ) )? *found_slot : default_result;
	}

	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline Monad<TItem&> FindItem( TStorage<TItem, TAllocator>& storage, const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<TItem&>{ *found_slot };
	}

	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline Monad<const TItem&> FindItem( const TStorage<TItem, TAllocator>& storage, const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<const TItem&>{ *found_slot };
	}

	template< typename TItem, typename TAllocator, typename TCriteria, template< typename, typename > class TStorage >
	inline auto FindItem(
		TStorage<TItem, TAllocator>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Monad<TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<TItem&>{ *found_slot };
	}

	template< typename TItem, typename TAllocator, typename TCriteria, template< typename, typename > class TStorage >
	inline auto FindItem(
		const TStorage<TItem, TAllocator>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Monad<const TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<const TItem&>{ *found_slot };
	}

	template< typename TItem, size_t ARRAY_LENGTH >
	inline Monad<TItem&> FindItem( TItem (&storage)[ ARRAY_LENGTH ], const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<TItem&>{ *found_slot };
	}

	template< typename TItem, size_t ARRAY_LENGTH >
	inline Monad<const TItem&> FindItem( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<const TItem&>{ *found_slot };
	}

	template< typename TItem, size_t ARRAY_LENGTH, typename TCriteria >
	inline auto FindItem(
		TItem (&storage)[ ARRAY_LENGTH ],
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Monad<TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<TItem&>{ *found_slot };
	}

	template< typename TItem, size_t ARRAY_LENGTH, typename TCriteria >
	inline auto FindItem(
		const TItem (&storage)[ ARRAY_LENGTH ],
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Monad<const TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<const TItem&>{ *found_slot };
	}

	template< typename TItem >
	inline Monad<TItem&> FindItem( PlainView<TItem>& storage, const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<TItem&>{ *found_slot };
	}

	template< typename TItem >
	inline Monad<const TItem&> FindItem( const PlainView<TItem>& storage, const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<const TItem&>{ *found_slot };
	}

	template< typename TItem, typename TCriteria >
	inline auto FindItem(
		PlainView<TItem>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Monad<TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<TItem&>{ *found_slot };
	}

	template< typename TItem, typename TCriteria >
	inline auto FindItem(
		const PlainView<TItem>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Monad<const TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<const TItem&>{ *found_slot };
	}

	template< typename TItem >
	inline Monad<TItem&> FindItem( PlainVector<TItem>& storage, const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<TItem&>{ *found_slot };
	}

	template< typename TItem >
	inline Monad<const TItem&> FindItem( const PlainVector<TItem>& storage, const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<const TItem&>{ *found_slot };
	}

	template< typename TItem, typename TCriteria >
	inline auto FindItem(
		PlainVector<TItem>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Monad<TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<TItem&>{ *found_slot };
	}

	template< typename TItem, typename TCriteria >
	inline auto FindItem(
		const PlainVector<TItem>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Monad<const TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Monad<const TItem&>{ *found_slot };
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
