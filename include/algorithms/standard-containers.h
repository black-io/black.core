#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
	/**
		@brief	Check that the given `storage` contains the `item`.
		@param	storage		The storage to check.
		@param	item		The item to check.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Template of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if storage contain the item.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool HasItem( const TStorage<TItem, TAllocator>& storage, const TItem& item );

	/**
		@brief	Check that the given `storage` contains the `item`.
		@param	storage		The storage to check.
		@param	item		The item to check.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if storage contain the item.
	*/
	template< typename TItem, typename TPredicate, typename TAllocator >
	inline const bool HasItem( const std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item );

	/**
		@brief	Check that the given `storage` contains the `item`.
		@param	storage		The storage to check.
		@param	item		The item to check.
		@tparam	TKey		Type of keys used by storage.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if storage contain the item.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline const bool HasItem( const std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Check that the given `storage` contains the `item`.
		@param	storage		The storage to check.
		@param	item		The item to check.
		@tparam	TKey		Type of keys used by storage.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	THash		Hash used by storage.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if storage contain the item.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline const bool HasItem( const std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Uniquely insert the item into storage.
		Does nothing if `item` already in `storage`.
		@param	storage		The storage to add.
		@param	item		The item to be added.
		@tparam	TStoredItem	Type of items stored by storage.
		@tparam	TNewItem	Type of item to be added uniquely. The type may be only cv-qualified version of `TStoredItem`.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Template of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TStoredItem, typename TNewItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool UniqueAdd( TStorage<TStoredItem, TAllocator>& storage, TNewItem&& item );

	/**
		@brief	Uniquely insert the item into presorted storage keeping the storage sorted.
		Does nothing if `item` already in `storage`.
		@param	storage		The storage to add.
		@param	item		The item to be added.
		@tparam	TStoredItem	Type of items stored by storage.
		@tparam	TNewItem	Type of item to be added uniquely. The type may be only cv-qualified version of `TStoredItem`.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Template of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TStoredItem, typename TNewItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool UniqueAddSorted( TStorage<TStoredItem, TAllocator>& storage, TNewItem&& item );

	/**
		@brief	Uniquely insert the item into presorted storage keeping the storage sorted.
		Does nothing if `item` already in `storage`.
		@param	storage		The storage to add.
		@param	item		The item to be added.
		@param	predicate	Binary predicate that return `true` if left argument is ordered before right.
		@tparam	TStoredItem	Type of items stored by storage.
		@tparam	TNewItem	Type of item to be added uniquely. The type may be only cv-qualified version of `TStoredItem`.
		@tparam	TPredicate	Type of used predicate. Should fit the signature `const bool ( const TStoredItem&, const TNewItem& )`.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Template of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TStoredItem, typename TNewItem, typename TPredicate, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool UniqueAddSorted( TStorage<TStoredItem, TAllocator>& storage, TNewItem&& item, const TPredicate& predicate );

	/**
		@brief	Uniquely insert the item into storage.
		Does nothing if `item` already in `storage`.
		@param	storage		The storage to add.
		@param	item		The item to be added.
		@tparam	TStoredItem	Type of items stored by storage.
		@tparam	TNewItem	Type of item to be added uniquely. The type may be only cv-qualified version of `TStoredItem`.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TStoredItem, typename TNewItem, typename TPredicate, typename TAllocator >
	inline const bool UniqueAdd( std::set<TStoredItem, TPredicate, TAllocator>& storage, TNewItem&& item );

	/**
		@brief	Uniquely insert the item into storage.
		Does nothing if `key` already in `storage`.
		@param	storage		The storage to add.
		@param	key			The key for item to add.
		@param	item		The item to be added.
		@tparam	TStoredKey	Type of keys stored by storage.
		@tparam	TNewKey		Type of key to be added uniquely. The type may be only cv-qualified version of `TStoredKey`.
		@tparam	TStoredItem	Type of items stored by storage.
		@tparam	TNewItem	Type of item to be added uniquely. The type may be only cv-qualified version of `TStoredItem`.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TStoredKey, typename TNewKey, typename TStoredItem, typename TNewItem, typename TPredicate, typename TAllocator >
	inline const bool UniqueAdd( std::map<TStoredKey, TStoredItem, TPredicate, TAllocator>& storage, TNewKey&& key, TNewItem&& item );

	/**
		@brief	Uniquely insert the item into storage.
		Does nothing if `key` already in `storage`.
		@param	storage		The storage to add.
		@param	key			The key for item to add.
		@param	item		The item to be added.
		@tparam	TStoredKey	Type of keys stored by storage.
		@tparam	TNewKey		Type of key to be added uniquely. The type may be only cv-qualified version of `TStoredKey`.
		@tparam	TStoredItem	Type of items stored by storage.
		@tparam	TNewItem	Type of item to be added uniquely. The type may be only cv-qualified version of `TStoredItem`.
		@tparam	THash		Hash used by storage.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TStoredKey, typename TNewKey, typename TStoredItem, typename TNewItem, typename THash, typename TPredicate, typename TAllocator >
	inline const bool UniqueAdd( std::unordered_map<TStoredKey, TStoredItem, THash, TPredicate, TAllocator>& storage, TNewKey&& key, TNewItem&& item );

	/**
		@brief	Uniquely insert the item into storage.
		Does nothing if `item` already in `storage`.
		@note	Unlike the `UniqueAdd` function, this one will return the ordinal index of item in storage.
		@param	storage		The storage to add.
		@param	item		The item to be added.
		@tparam	TStoredItem	Type of items stored in storage.
		@tparam	TNewItem	Type of item to be added.
		@tparam	TAllocator	Allocator used by storage.
		@return				index of item in storage.
	*/
	template< typename TStoredItem, typename TNewItem, typename TAllocator >
	inline const size_t UniqueAddIndexed( std::vector<TStoredItem, TAllocator>& storage, TNewItem&& item );

	/**
		@brief	Uniquely insert the item into presorted storage, keeping the storage sorted.
		Does nothing if `item` already in `storage`.
		Requires the `operator ==` defined between entities of `TStoredItem` and `TNewItem`.
		@note	Unlike the `UniqueAddSorted` function, this one will return the ordinal index of item in storage.
		@param	storage		The storage to add.
		@param	item		The item to be added.
		@tparam	TStoredItem	Type of items stored in storage.
		@tparam	TNewItem	Type of item to be added.
		@tparam	TAllocator	Allocator used by storage.
		@return				index of item in storage.
	*/
	template< typename TStoredItem, typename TNewItem, typename TAllocator >
	inline const size_t UniqueAddSortedIndexed( std::vector<TStoredItem, TAllocator>& storage, TNewItem&& item );

	/**
		@brief	Uniquely insert the item into presorted storage, keeping the storage sorted.
		Does nothing if `item` already in `storage`.
		@note	Unlike the `UniqueAddSorted` function, this one will return the ordinal index of item in storage.
		@param	storage		The storage to add.
		@param	item		The item to be added.
		@param	predicate	The predicate to compare the stored items with new one.
		@tparam	TStoredItem	Type of items stored in storage.
		@tparam	TNewItem	Type of item to be added.
		@tparam	TPredicate	Type of predicate to be used in search.
		@tparam	TAllocator	Allocator used by storage.
		@return				index of item in storage.
	*/
	template< typename TStoredItem, typename TNewItem, typename TPredicate, typename TAllocator >
	inline const size_t UniqueAddSortedIndexed( std::vector<TStoredItem, TAllocator>& storage, TNewItem&& item, const TPredicate& predicate );

	/**
		@brief	Removes the first found item from storage.
		@param	storage		The storage to inspect.
		@param	item		The item to be removed.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Template of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item was removed.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool RemoveItem( TStorage<TItem, TAllocator>& storage, const TItem& item );

	/**
		@brief	Removes the first found item from storage.
		@param	storage		The storage to inspect.
		@param	item		The item to be removed.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Template of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item was removed.
	*/
	template< typename TItem, typename TAllocator, typename TCriteria, template< typename, typename > class TStorage >
	inline auto RemoveItem(
		TStorage<TItem, TAllocator>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, const bool>;

	/**
		@brief	Removes the first found item from presorted storage, keeping the storage sorted.
		@param	storage		The storage to inspect.
		@param	item		The item to be removed.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Template of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item was removed.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool RemoveItemSorted( TStorage<TItem, TAllocator>& storage, const TItem& item );

	/**
		@brief	Removes the first found item from presorted storage, keeping the storage sorted.
		@param	storage		The storage to inspect.
		@param	item		The item to be removed.
		@param	predicate	The predicate to search the `item` in storage.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TPredicate	Type of predicate for searching the `item`.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Template of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item was removed.
	*/
	template< typename TItem, typename TPredicate, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool RemoveItemSorted( TStorage<TItem, TAllocator>& storage, const TItem& item, const TPredicate& predicate );

	/**
		@brief	Removes the item from storage, if exists.
		@param	storage		The storage to inspect.
		@param	item		The item to be removed.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if item was removed.
	*/
	template< typename TItem, typename TPredicate, typename TAllocator >
	inline const bool RemoveItem( std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item );

	/**
		@brief	Removes the item from storage by given key.
		@param	storage		The storage to inspect.
		@param	key			The key for item to be removed.
		@tparam	TKey		Type of keys used by storage.
		@tparam	TItem		Type of storage content.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if item was removed.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline const bool RemoveItem( std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Removes the item from storage by given key.
		@param	storage		The storage to inspect.
		@param	key			The key for item to be removed.
		@tparam	TKey		Type of keys used by storage.
		@tparam	TItem		Type of storage content.
		@tparam	THash		Hash used by storage.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if item was removed.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline const bool RemoveItem( std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Clear the storage, deleting the stored content.
		This function may be used for cases if container used to store raw pointers.
		@param	storage		The storage to clear.
		@tparam	TItem		Type of storage content.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Template of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline void DeletePointersAndClear( TStorage<TItem*, TAllocator>& storage );

	/**
		@brief	Clear the storage, deleting the stored content.
		This function may be used for cases if container used to store raw pointers.
		@param	storage		The storage to clear.
		@tparam	TKey		Type of keys used by storage.
		@tparam	TItem		Type of storage content.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline void DeletePointersAndClear( std::map<TKey, TItem*, TPredicate, TAllocator>& storage );

	/**
		@brief	Clear the storage, deleting the stored content.
		This function may be used for cases if container used to store raw pointers.
		@param	storage		The storage to clear.
		@tparam	TKey		Type of keys used by storage.
		@tparam	TItem		Type of storage content.
		@tparam	THash		Hash used by storage.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline void DeletePointersAndClear( std::unordered_map<TKey, TItem*, THash, TPredicate, TAllocator>& storage );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@param	default_result	Value to be returned in case the item not found in storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	TAllocator		Allocator used by storage.
		@tparam	TStorage		Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return					The value returned is first found in storage.
		@retval	default_value	In case of no `item` found in `storage`.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline TItem& FindItem( TStorage<TItem, TAllocator>& storage, const TItem& item, TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@param	default_result	Value to be returned in case the item not found in storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	TAllocator		Allocator used by storage.
		@tparam	TStorage		Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return					The value returned is first found in storage.
		@retval	default_value	In case of no `item` found in `storage`.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const TItem& FindItem( const TStorage<TItem, TAllocator>& storage, const TItem& item, const TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@param	default_result	Value to be returned in case the item not found in storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is first found in storage.
		@retval	default_value	In case of no `item` found in `storage`.
	*/
	template< typename TItem, typename TPredicate, typename TAllocator >
	inline const TItem& FindItem( const std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item, const TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function looks for `key` in `storage` and return the item associated with key.
		@param	storage			The storage to look up.
		@param	key				The key for item to be found.
		@param	default_result	The 'default' item to be used as result in case the `key` not found.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is an item by `key` in `storage` or `default_result`.
		@retval	default_result	In case of no `key` found in `storage`.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline TItem& FindItem( std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key, TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function looks for `key` in `storage` and return the item associated with key.
		@param	storage			The storage to look up.
		@param	key				The key for item to be found.
		@param	default_result	The 'default' item to be used as result in case the `key` not found.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is an item by `key` in `storage` or `default_result`.
		@retval	default_result	In case of no `key` found in `storage`.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline const TItem& FindItem( const std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key, const TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function looks for `key` in `storage` and return the item associated with key.
		@param	storage			The storage to look up.
		@param	key				The key for item to be found.
		@param	default_result	The 'default' item to be used as result in case the `key` not found.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content.
		@tparam	THash			Hash used by storage.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is an item by `key` in `storage` or `default_result`.
		@retval	default_result	In case of no `key` found in `storage`.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline TItem& FindItem( std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function looks for `key` in `storage` and return the item associated with key.
		@param	storage			The storage to look up.
		@param	key				The key for item to be found.
		@param	default_result	The 'default' item to be used as result in case the `key` not found.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content.
		@tparam	THash			Hash used by storage.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is an item by `key` in `storage` or `default_result`.
		@retval	default_result	In case of no `key` found in `storage`.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline const TItem& FindItem( const std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, const TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	TAllocator		Allocator used by storage.
		@tparam	TStorage		Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline Hypothetical<TItem&> FindItem( TStorage<TItem, TAllocator>& storage, const TItem& item );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	TAllocator		Allocator used by storage.
		@tparam	TStorage		Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline Hypothetical<const TItem&> FindItem( const TStorage<TItem, TAllocator>& storage, const TItem& item );

	/**
		@brief	Find the item in given storage.
		This function uses the `criteria` predicate to find the item to be found.
		@param	storage			The storage to look up.
		@param	criteria		Function-like predicate, used as criteria to determine the item to be found.
		@tparam	TItem			Type of storage content.
		@tparam	TAllocator		Allocator used by storage.
		@tparam	TCriteria		Type of criteria function.
		@tparam	TStorage		Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, typename TAllocator, typename TCriteria, template< typename, typename > class TStorage >
	inline auto FindItem(
		TStorage<TItem, TAllocator>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<TItem&>>;

	/**
		@brief	Find the item in given storage.
		This function uses the `criteria` predicate to find the item to be found.
		@param	storage			The storage to look up.
		@param	criteria		Function-like predicate, used as criteria to determine the item to be found.
		@tparam	TItem			Type of storage content.
		@tparam	TAllocator		Allocator used by storage.
		@tparam	TCriteria		Type of criteria function.
		@tparam	TStorage		Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, typename TAllocator, typename TCriteria, template< typename, typename > class TStorage >
	inline auto FindItem(
		const TStorage<TItem, TAllocator>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<const TItem&>>;

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, typename TPredicate, typename TAllocator >
	inline Hypothetical<const TItem&> FindItem( const std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item );

	/**
		@brief	Find the item in given storage.
		This function looks for `key` in `storage` and represents the result as Hypothetical.
		@param	storage			The storage to look up.
		@param	key				The key for item to be found.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline Hypothetical<TItem&> FindItem( std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Find the item in given storage.
		This function looks for `key` in `storage` and represents the result as Hypothetical.
		@param	storage			The storage to look up.
		@param	key				The key for item to be found.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline Hypothetical<const TItem&> FindItem( const std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Find the item in given storage.
		This function looks for `key` in `storage` and represents the result as Hypothetical.
		@param	storage			The storage to look up.
		@param	key				The key for item to be found.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content.
		@tparam	THash			Hash used by storage.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline Hypothetical<TItem&> FindItem( std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Find the item in given storage.
		This function looks for `key` in `storage` and represents the result as Hypothetical.
		@param	storage			The storage to look up.
		@param	key				The key for item to find.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content.
		@tparam	THash			Hash used by storage.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is Hypothetical with reference to found value or empty Hypothetical.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline Hypothetical<const TItem&> FindItem( const std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Get the position of `item` in `storage`.
		@param	storage			The storage to inspect.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	TAllocator		Allocator used by storage.
		@tparam	TStorage		Template of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return					The value returned is an position of `item` in `storage` or `UNDEFINED_INDEX`.
		@retval	UNDEFINED_INDEX	Returned if no `item` was found inside `storage`.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const size_t GetItemIndex( const TStorage<TItem, TAllocator>& storage, const TItem& item );
}
}
}
