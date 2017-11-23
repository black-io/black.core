#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Utils
{
	/**
		@brief	Checks if `item` exists in `items_storage`.
		@param	items_storage	Items container.
		@param	item			Item for check.
		@tparam	TItemType		Type of `item` and type of `items_storage` content as well.
		@tparam	TContainerType	Type of `items_storage`. `std::vector`, `std::list` or `std::deque` may be used as such container.
		@return					Returns `true` if item already exists in `items_storage`.
	*/
	template< template< typename TStoredItem, typename TAllocator > class TContainerType, typename TItemType, typename TAllocator >
	inline const bool IsItemExists( const TContainerType<TItemType, TAllocator>& items_storage, const TItemType& item );

	/**
		@brief	Checks if `item` exists in `items_storage`.
		@param	items_storage	Items container.
		@param	item			Item for check.
		@tparam	TItemType		Type of `item` and type of `items_storage` content as well.
		@tparam	TContainerType	Type of `items_storage`. `std::vector`, `std::list` or `std::deque` may be used as such container.
		@return					Returns `true` if item already exists in `items_storage`.
	*/
	template< typename TItemType, size_t ARRAY_LENGTH >
	inline const bool IsItemExists( const TItemType (&items_storage)[ ARRAY_LENGTH ], const TItemType& item );

	/**
		@brief	Checks if `item` exists in `items_storage`.
		@param	items_storage	Items container.
		@param	item			Item for check.
		@tparam	TItemType		Type of `item` and type of `items_storage` content as well.
		@tparam	TContainerType	Type of `items_storage`. `std::vector`, `std::list` or `std::deque` may be used as such container.
		@return					Returns `true` if item already exists in `items_storage`.
	*/
	template< typename TItemType >
	inline const bool IsItemExists( const PlainView<TItemType>& items_storage, const TItemType& item );

	/**
		@brief	Checks if `item` exists in `items_storage`.
		@param	items_storage	Items container.
		@param	item			Item for check.
		@tparam	TItemType		Type of `item` and type of `items_storage` content as well.
		@tparam	TContainerType	Type of `items_storage`. `std::vector`, `std::list` or `std::deque` may be used as such container.
		@return					Returns `true` if item already exists in `items_storage`.
	*/
	template< typename TItemType >
	inline const bool IsItemExists( const PlainVector<TItemType>& items_storage, const TItemType& item );

	/**
		@brief	Checks if item with `key` exists in `items_set`.
		@param	items_set		Items container.
		@param	item			Item for check.
		@tparam	TItemType		Type of items in `items_set`
		@tparam	TSetPredicate	Part of `items_set` type instantiation, placed here for flexible template auto deducing.
		@tparam	TSetAllocator	Part of `items_set` type instantiation, placed here for flexible template auto deducing.
		@return					Returns `true` if item already exists in `items_set`.
	*/
	template< typename TItemType, typename TSetPredicate, typename TSetAllocator >
	inline const bool IsItemExists( const std::set<TItemType, TSetPredicate, TSetAllocator>& items_set, const TItemType& item );

	/**
		@brief	Checks if item with `key` exists in `items_map`.
		@param	items_map		Items container.
		@param	key				Key for check.
		@tparam	TKeyType		Type of keys in `items_map`.
		@tparam	TItemType		Type of items in `items_map`
		@tparam	TMapPredicate	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapAllocator	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@return					Returns `true` if item already exists in `items_map`.
	*/
	template< typename TKeyType, typename TItemType, typename TMapPredicate, typename TMapAllocator >
	inline const bool IsItemExists( const std::map<TKeyType, TItemType, TMapPredicate, TMapAllocator>& items_map, const TKeyType& key );

	/**
		@brief	Checks if item with `key` exists in `items_map`.
		@param	items_map		Items container.
		@param	key				Key for check.
		@tparam	TKeyType		Type of keys in `items_map`.
		@tparam	TItemType		Type of items in `items_map`.
		@tparam	TMapHash		Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapPredicate	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapAllocator	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@return					Returns `true` if item already exists in `items_map`.
	*/
	template< typename TKeyType, typename TItemType, typename TMapHash, typename TMapPredicate, typename TMapAllocator >
	inline const bool IsItemExists( const std::unordered_map<TKeyType, TItemType, TMapHash, TMapPredicate, TMapAllocator>& items_map, const TKeyType& key );

	/**
		@brief	Inserts `item` into `items_storage`, as last item, if no same `item` contains in `items_storage` before.
		@param	items_storage	Items storage, where needs to check `item` existence and insert it if not found.
		@param	item			Item, that needs to insert into `items_storage`.
		@tparam	TItemType		Type of `item` and type of `items_storage` content as well.
		@tparam	TContainerType	Type of `items_storage`. `std::vector`, `std::list` or `std::deque` may be used as such container.
		@return					Returns `true` if `item` just inserted or `false` if `item` already exists in container.
	*/
	template< template< typename TStoredItem, typename TAllocator > class TContainerType, typename TItemType, typename TAllocator >
	inline const bool UniqueAdd( TContainerType<TItemType, TAllocator>& items_storage, const TItemType& item );

	/**
		@brief	Inserts `item` into `items_storage`, as last item, if no same `item` contains in `items_storage` before.
		@param	items_storage	Items storage, where needs to check `item` existence and insert it if not found.
		@param	item			Item, that needs to insert into `items_storage`.
		@tparam	TItemType		Type of `item` and type of `items_storage` content as well.
		@tparam	TContainerType	Type of `items_storage`. `std::vector`, `std::list` or `std::deque` may be used as such container.
		@return					Returns `true` if `item` just inserted or `false` if `item` already exists in container.
	*/
	template< typename TItemType >
	inline const bool UniqueAdd( PlainVector<TItemType>& items_storage, const TItemType& item );

	/**
		@brief	Inserts `item` into `items_set` if no such item placed there yet.
		@param	items_set		Set to store items.
		@param	item			Item, that will be placed into `items_set` if no `key` exists there yet.
		@tparam	TItemType		Type of items in `items_set`
		@tparam	TSetPredicate	Part of `items_set` type instantiation, placed here for flexible template auto deducing.
		@tparam	TSetAllocator	Part of `items_set` type instantiation, placed here for flexible template auto deducing.
		@return					Returns `true` if `item` just inserted or `false` if `item` already exists in `items_set`.
	*/
	template< typename TItemType, typename TSetPredicate, typename TSetAllocator >
	inline const bool UniqueAdd( std::set<TItemType, TSetPredicate, TSetAllocator>& items_set, const TItemType& item );

	/**
		@brief	Inserts `item` into `items_map` with some `key` if this key not used yet.
		@param	items_map		Map, where items stored by keys.
		@param	key				Key, that needs to be checked in `items_map`.
		@param	item			Item, that will be placed into `items_map` if no `key` exists there yet.
		@tparam	TKeyType		Type of keys in `items_map`.
		@tparam	TItemType		Type of items in `items_map`
		@tparam	TMapPredicate	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapAllocator	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@return					Returns `true` if `item` just inserted or `false` if `item` already exists in `items_map`.
	*/
	template< typename TKeyType, typename TItemType, typename TMapPredicate, typename TMapAllocator >
	inline const bool UniqueAdd( std::map<TKeyType, TItemType, TMapPredicate, TMapAllocator>& items_map, const TKeyType& key, const TItemType& item );

	/**
		@brief	Inserts `item` into `items_map` with some `key` if this key not used yet.
		@param	items_map		Map, where items stored by keys.
		@param	key				Key, that needs to be checked in `items_map`.
		@param	item			Item, that will be placed into `items_map` if no `key` exists there yet.
		@tparam	TKeyType		Type of keys in `items_map`.
		@tparam	TItemType		Type of items in `items_map`.
		@tparam	TMapHash		Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapPredicate	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapAllocator	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@return					Returns `true` if `item` just inserted or `false` if `item` already exists in `items_map`.
	*/
	template< typename TKeyType, typename TItemType, typename TMapHash, typename TMapPredicate, typename TMapAllocator >
	inline const bool UniqueAdd( std::unordered_map<TKeyType, TItemType, TMapHash, TMapPredicate, TMapAllocator>& items_map, const TKeyType& key, const TItemType& item );

	/**
		@brief	Inserts `item` into `items_storage`, as last item, if no same `item` contains in `items_storage` before.
		@param	items_storage	Items storage, where needs to check `item` existence and insert it if not found.
		@param	item			Item, that needs to insert into `items_storage`.
		@tparam	TItemType		Type of `item` and type of `items_storage` content as well.
		@return					Returns position of `item` in storage regardless it already exists or just inserted.
	*/
	template< typename TItemType, typename TAllocator >
	inline const size_t UniqueAddIndexed( std::vector<TItemType, TAllocator>& items_storage, const TItemType& item );

	/**
		@brief	Inserts `item` into `items_storage`, as last item, if no same `item` contains in `items_storage` before.
		@param	items_storage	Items storage, where needs to check `item` existence and insert it if not found.
		@param	item			Item, that needs to insert into `items_storage`.
		@tparam	TItemType		Type of `item` and type of `items_storage` content as well.
		@return					Returns position of `item` in storage regardless it already exists or just inserted.
	*/
	template< typename TItemType >
	inline const size_t UniqueAddIndexed( PlainVector<TItemType>& items_storage, const TItemType& item );

	/**
		@brief	Looks for `item` inside `items_storage` and removes it if found.
		@param	items_storage	Items storage, where `item` needs to be found and deleted.
		@param	item			Item, that needs to be removed from `items_storage`.
		@tparam	TItemType		Type of `item` and type of `items_storage` content as well.
		@tparam	TContainerType	Type of `items_storage`. `std::vector`, `std::list` or `std::deque` may be used as such container.
		@return					Returns `true` if items was found and deleted, `false` in other case.
	*/
	template< template< typename TStoredItem, typename TAllocator > class TContainerType, typename TItemType, typename TAllocator >
	inline const bool RemoveItem( TContainerType<TItemType, TAllocator>& items_storage, const TItemType& item );

	/**
		@brief	Looks for `item` inside `items_storage` and removes it if found.
		@param	items_storage	Items storage, where `item` needs to be found and deleted.
		@param	item			Item, that needs to be removed from `items_storage`.
		@tparam	TItemType		Type of `item` and type of `items_storage` content as well.
		@tparam	TContainerType	Type of `items_storage`. `std::vector`, `std::list` or `std::deque` may be used as such container.
		@return					Returns `true` if items was found and deleted, `false` in other case.
	*/
	template< typename TItemType >
	inline const bool RemoveItem( PlainVector<TItemType>& items_storage, const TItemType& item );

	/**
		@brief	Removes `item` from `items_set` if it exists.
		@param	items_set		Set, where `item` needs to be removed.
		@param	item			Item to be removed at `items_set`.
		@tparam	TItemType		Type of items in `items_set`
		@tparam	TSetPredicate	Part of `items_set` type instantiation, placed here for flexible template auto deducing.
		@tparam	TSetAllocator	Part of `items_set` type instantiation, placed here for flexible template auto deducing.
		@return
	*/
	template< typename TItemType, typename TSetPredicate, typename TSetAllocator >
	inline const bool RemoveItem( std::set<TItemType, TSetPredicate, TSetAllocator>& items_set, const TItemType& item );

	/**
		@brief	Removes item from `items_map` by it's key.
		@param	items_map		Map, where items stored by keys.
		@param	key				Key, that needs to be removed from `items_map`.
		@tparam	TKeyType		Type of keys in `items_map`.
		@tparam	TItemType		Type of items in `items_map`
		@tparam	TMapPredicate	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapAllocator	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@return					Returns `true` if `key` was found and removed from `items_map`, `false` in other keys.
	*/
	template< typename TKeyType, typename TItemType, typename TMapPredicate, typename TMapAllocator >
	inline const bool RemoveItem( std::map<TKeyType, TItemType, TMapPredicate, TMapAllocator>& items_map, const TKeyType& key );

	/**
		@brief	Removes item from `items_map` by it's key.
		@param	items_map		Map, where items stored by keys.
		@param	key				Key, that needs to be removed from `items_map`.
		@tparam	TKeyType		Type of keys in `items_map`.
		@tparam	TItemType		Type of items in `items_map`.
		@tparam	TMapHash		Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapPredicate	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapAllocator	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@return					Returns `true` if `item` just inserted or `false` if `item` already exists in `items_map`.
	*/
	template< typename TKeyType, typename TItemType, typename TMapHash, typename TMapPredicate, typename TMapAllocator >
	inline const bool RemoveItem( std::unordered_map<TKeyType, TItemType, TMapHash, TMapPredicate, TMapAllocator>& items_map, const TKeyType& key );

	/**
		@brief	Deletes content of `items_storage` and clears it after.
		This function may be used for cases if container used to store plain pointers.
		@param	items_storage	Items storage, that needs to be cleared.
		@tparam	TItemType		Type of items, whos pointers placed in `items_storage`.
		@tparam	TContainerType	Type of `items_storage`. `std::vector`, `std::list` or `std::deque` may be used as such container.
	*/
	template< template< typename TStoredItem, typename TAllocator > class TContainerType, typename TItemType, typename TAllocator >
	inline void DeletePointersAndClear( TContainerType<TItemType*, TAllocator>& items_storage );

	/**
		@brief	Deletes content of `items_storage` and clears it after.
		This function may be used for cases if container used to store plain pointers.
		@param	items_storage	Items storage, that needs to be cleared.
		@tparam	TItemType		Type of items, whos pointers placed in `items_storage`.
		@tparam	TContainerType	Type of `items_storage`. `std::vector`, `std::list` or `std::deque` may be used as such container.
	*/
	template< typename TItemType >
	inline void DeletePointersAndClear( PlainVector<TItemType*>& items_storage );

	/**
		@brief	Deletes content of `items_map` and clears it after.
		@param	items_map		Items map, that needs to be cleared.
		@tparam	TKeyType		Type of keys in `items_map`.
		@tparam	TItemType		Type of items in `items_map`
		@tparam	TMapPredicate	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapAllocator	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
	*/
	template< typename TKeyType, typename TItemType, typename TMapPredicate, typename TMapAllocator >
	inline void DeletePointersAndClear( std::map<TKeyType, TItemType*, TMapPredicate, TMapAllocator>& items_map );

	/**
		@brief	Deletes content of `items_map` and clears it after.
		@param	items_map		Items map, that needs to be cleared.
		@tparam	TKeyType		Type of keys in `items_map`.
		@tparam	TItemType		Type of items in `items_map`
		@tparam	TMapPredicate	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapAllocator	Part of `items_map` type instantiation, placed here for flexible template auto deducing.
	*/
	template< typename TKeyType, typename TItemType, typename TMapHash, typename TMapPredicate, typename TMapAllocator >
	inline void DeletePointersAndClear( std::unordered_map<TKeyType, TItemType*, TMapHash, TMapPredicate, TMapAllocator>& items_map );

	/**
		@brief	Looks for `key` in `items_map` and returns corresponded value or `default_result` if `key` not found.
		@param	items_map			Items container.
		@param	key					Key for check.
		@tparam	TKeyType			Type of keys in `items_map`.
		@tparam	TItemType			Type of items in `items_map`
		@tparam	TMapPredicate		Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapAllocator		Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@return						Returns value, that stored in `items_map` with `key`.
		@retval	`default_result`	Returned if no value stored in `items_map` with `key`.
	*/
	template< typename TKeyType, typename TItemType, typename TMapPredicate, typename TMapAllocator >
	inline TItemType& FindItem( std::map<TKeyType, TItemType, TMapPredicate, TMapAllocator>& items_map, const TKeyType& key, TItemType& default_result );

	/**
		@brief	Looks for `key` in `items_map` and returns corresponded value or `default_result` if `key` not found.
		@param	items_map			Items container.
		@param	key					Key for check.
		@tparam	TKeyType			Type of keys in `items_map`.
		@tparam	TItemType			Type of items in `items_map`
		@tparam	TMapPredicate		Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapAllocator		Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@return						Returns value, that stored in `items_map` with `key`.
		@retval	`default_result`	Returned if no value stored in `items_map` with `key`.
	*/
	template< typename TKeyType, typename TItemType, typename TMapPredicate, typename TMapAllocator >
	inline const TItemType& FindItem( const std::map<TKeyType, TItemType, TMapPredicate, TMapAllocator>& items_map, const TKeyType& key, const TItemType& default_result );

	/**
		@brief	Looks for `key` in `items_map` and returns corresponded value or `default_result` if `key` not found.
		@param	items_map			Items container.
		@param	key					Key for check.
		@tparam	TKeyType			Type of keys in `items_map`.
		@tparam	TItemType			Type of items in `items_map`.
		@tparam	TMapHash			Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapPredicate		Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapAllocator		Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@return						Returns value, that stored in `items_map` with `key`.
		@retval	`default_result`	Returned if no value stored in `items_map` with `key`.
	*/
	template< typename TKeyType, typename TItemType, typename TMapHash, typename TMapPredicate, typename TMapAllocator >
	inline TItemType& FindItem( std::unordered_map<TKeyType, TItemType, TMapHash, TMapPredicate, TMapAllocator>& items_map, const TKeyType& key, TItemType& default_result );

	/**
		@brief	Looks for `key` in `items_map` and returns corresponded value or `default_result` if `key` not found.
		@param	items_map			Items container.
		@param	key					Key for check.
		@tparam	TKeyType			Type of keys in `items_map`.
		@tparam	TItemType			Type of items in `items_map`.
		@tparam	TMapHash			Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapPredicate		Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@tparam	TMapAllocator		Part of `items_map` type instantiation, placed here for flexible template auto deducing.
		@return						Returns value, that stored in `items_map` with `key`.
		@retval	`default_result`	Returned if no value stored in `items_map` with `key`.
	*/
	template< typename TKeyType, typename TItemType, typename TMapHash, typename TMapPredicate, typename TMapAllocator >
	inline const TItemType& FindItem(
		const std::unordered_map<TKeyType, TItemType, TMapHash, TMapPredicate, TMapAllocator>& items_map,
		const TKeyType& key,
		const TItemType& default_result
	);

	/**
		@brief	Looks for `item` in `items_storage` and returns index of its position.
		@param	items_storage	Storage of items.
		@param	item			Item for searching.
		@return					Returns index where `item` stored inside `items_storage`.
		@retval	UNDEFINED_INDEX	Returned if no `item` was found inside `items_storage`.
	*/
	template< template< typename TStoredItem, typename TAllocator > class TContainerType, typename TItemType, typename TAllocator >
	inline const size_t GetItemIndex( const TContainerType<TItemType, TAllocator>& items_storage, const TItemType& item );

	/**
		@brief	Looks for `item` in `items_storage` and returns index of its position.
		@param	items_storage	Storage of items.
		@param	item			Item for searching.
		@return					Returns index where `item` stored inside `items_storage`.
		@retval	UNDEFINED_INDEX	Returned if no `item` was found inside `items_storage`.
	*/
	template< typename TItemType, size_t ARRAY_SIZE >
	inline const size_t GetItemIndex( const TItemType (&items_storage)[ ARRAY_SIZE ], const TItemType& item );

	/**
		@brief	Looks for `item` in `items_storage` and returns index of its position.
		@param	items_storage	Storage of items.
		@param	item			Item for searching.
		@return					Returns index where `item` stored inside `items_storage`.
		@retval	UNDEFINED_INDEX	Returned if no `item` was found inside `items_storage`.
	*/
	template< typename TItemType >
	inline const size_t GetItemIndex( const PlainView<TItemType>& items_storage, const TItemType& item );

	/**
		@brief	Looks for `item` in `items_storage` and returns index of its position.
		@param	items_storage	Storage of items.
		@param	item			Item for searching.
		@return					Returns index where `item` stored inside `items_storage`.
		@retval	UNDEFINED_INDEX	Returned if no `item` was found inside `items_storage`.
	*/
	template< typename TItemType >
	inline const size_t GetItemIndex( const PlainVector<TItemType>& items_storage, const TItemType& item );
}
}
}
