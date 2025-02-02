#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
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

	template< size_t ARRAY_LENGTH >
	inline const bool AllOf( const bool (&storage)[ ARRAY_LENGTH ] )
	{
		return std::all_of( std::begin( storage ), std::end( storage ), []( const bool value ) { return value; } );
	}

	template< typename TItem, typename TPredicate, size_t ARRAY_LENGTH >
	inline const bool AllOf( const TItem (&storage)[ ARRAY_LENGTH ], TPredicate&& predicate )
	{
		return std::all_of( std::begin( storage ), std::end( storage ), std::forward<TPredicate>( predicate ) );
	}

	inline const bool AllOf( const PlainView<bool>& storage )
	{
		return std::all_of( storage.begin(), storage.end(), []( const bool value ) { return value; } );
	}

	template< typename TItem, typename TPredicate >
	inline const bool AllOf( const PlainView<TItem>& storage, TPredicate&& predicate )
	{
		return std::all_of( storage.begin(), storage.end(), std::forward<TPredicate>( predicate ) );
	}

	inline const bool AllOf( const PlainVector<bool>& storage )
	{
		return std::all_of( storage.begin(), storage.end(), []( const bool value ) { return value; } );
	}

	template< typename TItem, typename TPredicate >
	inline const bool AllOf( const PlainVector<TItem>& storage, TPredicate&& predicate )
	{
		return std::all_of( storage.begin(), storage.end(), std::forward<TPredicate>( predicate ) );
	}

	template< size_t ARRAY_LENGTH >
	inline const bool AnyOf( const bool (&storage)[ ARRAY_LENGTH ] )
	{
		return std::any_of( std::begin( storage ), std::end( storage ), []( const bool value ) { return value; } );
	}

	template< typename TItem, typename TPredicate, size_t ARRAY_LENGTH >
	inline const bool AnyOf( const TItem (&storage)[ ARRAY_LENGTH ], TPredicate&& predicate )
	{
		return std::any_of( std::begin( storage ), std::end( storage ), std::forward<TPredicate>( predicate ) );
	}

	inline const bool AnyOf( const PlainView<bool>& storage )
	{
		return std::any_of( storage.begin(), storage.end(), []( const bool value ) { return value; } );
	}

	template< typename TItem, typename TPredicate >
	inline const bool AnyOf( const PlainView<TItem>& storage, TPredicate&& predicate )
	{
		return std::any_of( storage.begin(), storage.end(), std::forward<TPredicate>( predicate ) );
	}

	inline const bool AnyOf( const PlainVector<bool>& storage )
	{
		return std::any_of( storage.begin(), storage.end(), []( const bool value ) { return value; } );
	}

	template< typename TItem, typename TPredicate >
	inline const bool AnyOf( const PlainVector<TItem>& storage, TPredicate&& predicate )
	{
		return std::any_of( storage.begin(), storage.end(), std::forward<TPredicate>( predicate ) );
	}

	template< size_t ARRAY_LENGTH >
	inline const bool NoneOf( const bool (&storage)[ ARRAY_LENGTH ] )
	{
		return std::none_of( std::begin( storage ), std::end( storage ), []( const bool value ) { return value; } );
	}

	template< typename TItem, typename TPredicate, size_t ARRAY_LENGTH >
	inline const bool NoneOf( const TItem (&storage)[ ARRAY_LENGTH ], TPredicate&& predicate )
	{
		return std::none_of( std::begin( storage ), std::end( storage ), std::forward<TPredicate>( predicate ) );
	}

	inline const bool NoneOf( const PlainView<bool>& storage )
	{
		return std::none_of( storage.begin(), storage.end(), []( const bool value ) { return value; } );
	}

	template< typename TItem, typename TPredicate >
	inline const bool NoneOf( const PlainView<TItem>& storage, TPredicate&& predicate )
	{
		return std::none_of( storage.begin(), storage.end(), std::forward<TPredicate>( predicate ) );
	}

	inline const bool NoneOf( const PlainVector<bool>& storage )
	{
		return std::none_of( storage.begin(), storage.end(), []( const bool value ) { return value; } );
	}

	template< typename TItem, typename TPredicate >
	inline const bool NoneOf( const PlainVector<TItem>& storage, TPredicate&& predicate )
	{
		return std::none_of( storage.begin(), storage.end(), std::forward<TPredicate>( predicate ) );
	}

	template< typename TItem >
	inline void DeletePointersAndClear( PlainVector<TItem*>& storage )
	{
		CRET( storage.IsEmpty() );
		std::for_each( std::begin( storage ), std::end( storage ), []( TItem* item ){ delete item; } );
		storage.clear();
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

	template< typename TItem, size_t ARRAY_LENGTH >
	inline Hypothetical<TItem&> FindItem( TItem (&storage)[ ARRAY_LENGTH ], const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Hypothetical<TItem&>{ *found_slot };
	}

	template< typename TItem, size_t ARRAY_LENGTH >
	inline Hypothetical<const TItem&> FindItem( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Hypothetical<const TItem&>{ *found_slot };
	}

	template< typename TItem, size_t ARRAY_LENGTH, typename TCriteria >
	inline auto FindItem(
		TItem (&storage)[ ARRAY_LENGTH ],
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Hypothetical<TItem&>{ *found_slot };
	}

	template< typename TItem, size_t ARRAY_LENGTH, typename TCriteria >
	inline auto FindItem(
		const TItem (&storage)[ ARRAY_LENGTH ],
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<const TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Hypothetical<const TItem&>{ *found_slot };
	}

	template< typename TItem >
	inline Hypothetical<TItem&> FindItem( PlainView<TItem>& storage, const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Hypothetical<TItem&>{ *found_slot };
	}

	template< typename TItem >
	inline Hypothetical<const TItem&> FindItem( const PlainView<TItem>& storage, const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Hypothetical<const TItem&>{ *found_slot };
	}

	template< typename TItem, typename TCriteria >
	inline auto FindItem(
		PlainView<TItem>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Hypothetical<TItem&>{ *found_slot };
	}

	template< typename TItem, typename TCriteria >
	inline auto FindItem(
		const PlainView<TItem>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<const TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Hypothetical<const TItem&>{ *found_slot };
	}

	template< typename TItem >
	inline Hypothetical<TItem&> FindItem( PlainVector<TItem>& storage, const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Hypothetical<TItem&>{ *found_slot };
	}

	template< typename TItem >
	inline Hypothetical<const TItem&> FindItem( const PlainVector<TItem>& storage, const TItem& item )
	{
		const auto found_slot = std::find( std::begin( storage ), std::end( storage ), item );
		CRET( found_slot == std::end( storage ), {} );
		return Hypothetical<const TItem&>{ *found_slot };
	}

	template< typename TItem, typename TCriteria >
	inline auto FindItem(
		PlainVector<TItem>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Hypothetical<TItem&>{ *found_slot };
	}

	template< typename TItem, typename TCriteria >
	inline auto FindItem(
		const PlainVector<TItem>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<const TItem&>>
	{
		static_assert(
			std::is_invocable_r_v<const bool, TCriteria, const std::decay_t<TItem>&>,
			"Used criteria should meet the requirement of signature `const bool ( const TItem& )`."
		);

		const auto found_slot = std::find_if( std::begin( storage ), std::end( storage ), std::forward<TCriteria>( criteria ) );
		CRET( found_slot == std::end( storage ), {} );
		return Hypothetical<const TItem&>{ *found_slot };
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
