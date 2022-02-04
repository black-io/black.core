#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
	/**
		@brief	Check that the item storage contains the item.
		@param	storage		The storage to check.
		@param	item		The item to check.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if storage contain the item.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool IsItemPresent( const TStorage<TItem, TAllocator>& storage, const TItem& item );

	/**
		@brief	Check that the item storage contains the item.
		@param	storage			The storage to check.
		@param	item			The item to check.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	ARRAY_LENGTH	Number of elements in storage.
		@return					`true` if storage contain the item.
	*/
	template< typename TItem, size_t ARRAY_LENGTH >
	inline const bool IsItemPresent( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item );

	/**
		@brief	Check that the item storage contains the item.
		@param	storage			The storage to check.
		@param	item			The item to check.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					`true` if storage contain the item.
	*/
	template< typename TItem >
	inline const bool IsItemPresent( const PlainView<TItem>& storage, const TItem& item );

	/**
		@brief	Check that the item storage contains the item.
		@param	storage			The storage to check.
		@param	item			The item to check.
		@tparam	TItem		Type of storage content and type of item as well.
		@return					`true` if storage contain the item.
	*/
	template< typename TItem >
	inline const bool IsItemPresent( const PlainVector<TItem>& storage, const TItem& item );

	/**
		@brief	Check that the item storage contains the item.
		@param	storage		The storage to check.
		@param	item		The item to check.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if storage contain the item.
	*/
	template< typename TItem, typename TPredicate, typename TAllocator >
	inline const bool IsItemPresent( const std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item );

	/**
		@brief	Check that the item storage contains the item.
		@param	storage		The storage to check.
		@param	item		The item to check.
		@tparam	TKey		Type of keys used by storage.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if storage contain the item.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline const bool IsItemPresent( const std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Check that the item storage contains the item.
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
	inline const bool IsItemPresent( const std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Uniquely insert the item into storage.
		@param	storage		The storage to add.
		@param	item		The item to add.
		@tparam	TStoredItem	Type of items stored by storage.
		@tparam	TNewItem	Type of item to be added uniquely. The type may be only cv-qualified version of `TStoredItem`.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TStoredItem, typename TNewItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool UniqueAdd( TStorage<TStoredItem, TAllocator>& storage, TNewItem&& item );

	/**
		@brief	Uniquely insert the item into presorted storage keeping the storage sorted.
		@param	storage		The storage to add.
		@param	item		The item to add.
		@tparam	TStoredItem	Type of items stored by storage.
		@tparam	TNewItem	Type of item to be added uniquely. The type may be only cv-qualified version of `TStoredItem`.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TStoredItem, typename TNewItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool UniqueAddSorted( TStorage<TStoredItem, TAllocator>& storage, TNewItem&& item );

	/**
		@brief	Uniquely insert the item into presorted storage keeping the storage sorted.
		@param	storage		The storage to add.
		@param	item		The item to add.
		@param	predicate	Binary predicate that return `true` if left argument is ordered before right.
		@tparam	TStoredItem	Type of items stored by storage.
		@tparam	TNewItem	Type of item to be added uniquely. The type may be only cv-qualified version of `TStoredItem`.
		@tparam	TPredicate	Type of used predicate. Should fit the signature `const bool ( const TStoredItem&, const TNewItem& )`.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TStoredItem, typename TNewItem, typename TPredicate, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool UniqueAddSorted( TStorage<TStoredItem, TAllocator>& storage, TNewItem&& item, const TPredicate& predicate );

	/**
		@brief	Uniquely insert the item into storage.
		@param	storage		The storage to add.
		@param	item		The item to add.
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
		@param	storage		The storage to add.
		@param	key			The key for item to add.
		@param	item		The item to add.
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
		@param	storage		The storage to add.
		@param	key			The key for item to add.
		@param	item		The item to add.
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
		@note	Unlike the `UniqueAdd` function, this one will return the positional number of item in storage.
		@param	storage		The storage to add.
		@param	item		The item to add.
		@tparam	TStoredItem	Type of items stored in storage.
		@tparam	TNewItem	Type of item to be added.
		@tparam	TAllocator	Allocator used by storage.
		@return				index of item in storage.
	*/
	template< typename TStoredItem, typename TNewItem, typename TAllocator >
	inline const size_t UniqueAddIndexed( std::vector<TStoredItem, TAllocator>& storage, TNewItem&& item );

	/**
		@brief	Uniquely insert the item into presorted storage, keeping the storage sorted.
		Requires the `operator ==` defined between entities of `TStoredItem` and `TNewItem`.

		@note	Unlike the `UniqueAddSorted` function, this one will return the positional number of item in storage.
		@param	storage		The storage to add.
		@param	item		The item to add.
		@tparam	TStoredItem	Type of items stored in storage.
		@tparam	TNewItem	Type of item to be added.
		@tparam	TAllocator	Allocator used by storage.
		@return				index of item in storage.
	*/
	template< typename TStoredItem, typename TNewItem, typename TAllocator >
	inline const size_t UniqueAddSortedIndexed( std::vector<TStoredItem, TAllocator>& storage, TNewItem&& item );

	/**
		@brief	Uniquely insert the item into presorted storage, keeping the storage sorted.
		@note	Unlike the `UniqueAddSorted` function, this one will return the positional number of item in storage.
		@param	storage		The storage to add.
		@param	item		The item to add.
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
		@brief	Removes the single item from storage.
		@param	storage		The storage to remove.
		@param	item		The item to remove.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item was removed.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool RemoveItem( TStorage<TItem, TAllocator>& storage, const TItem& item );

	/**
		@brief	Removes the single item from presorted storage, keeping the storage sorted.
		@param	storage		The storage to remove.
		@param	item		The item to remove.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item was removed.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool RemoveItemSorted( TStorage<TItem, TAllocator>& storage, const TItem& item );

	/**
		@brief	Removes the single item from presorted storage, keeping the storage sorted.
		@param	storage		The storage to remove.
		@param	item		The item to remove.
		@param	predicate	The predicate to search the `item` in storage.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TPredicate	Type of predicate for searching the `item`.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item was removed.
	*/
	template< typename TItem, typename TPredicate, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool RemoveItemSorted( TStorage<TItem, TAllocator>& storage, const TItem& item, const TPredicate& predicate );

	/**
		@brief	Removes the single item from storage.
		@param	storage		The storage to remove.
		@param	item		The item to remove.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if item was removed.
	*/
	template< typename TItem, typename TPredicate, typename TAllocator >
	inline const bool RemoveItem( std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item );

	/**
		@brief	Removes the single item from storage.
		@param	storage		The storage to remove.
		@param	key			The key for item to remove.
		@tparam	TKey		Type of keys used by storage.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if item was removed.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline const bool RemoveItem( std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Removes the single item from storage.
		@param	storage		The storage to remove.
		@param	key			The key for item to remove.
		@tparam	TKey		Type of keys used by storage.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	THash		Hash used by storage.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if item was removed.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline const bool RemoveItem( std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Clear the storage, deleting the stored content.
		This function may be used for cases if container used to store plain pointers.
		@param	storage		The storage to clear.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline void DeletePointersAndClear( TStorage<TItem*, TAllocator>& storage );

	/**
		@brief	Clear the storage, deleting the stored content.
		This function may be used for cases if container used to store plain pointers.
		@param	storage		The storage to clear.
		@tparam	TItem		Type of storage content and type of item as well.
	*/
	template< typename TItem >
	inline void DeletePointersAndClear( PlainVector<TItem*>& storage );

	/**
		@brief	Clear the storage, deleting the stored content.
		This function may be used for cases if container used to store plain pointers.
		@param	storage		The storage to clear.
		@tparam	TKey		Type of keys used by storage.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline void DeletePointersAndClear( std::map<TKey, TItem*, TPredicate, TAllocator>& storage );

	/**
		@brief	Clear the storage, deleting the stored content.
		This function may be used for cases if container used to store plain pointers.
		@param	storage		The storage to clear.
		@tparam	TKey		Type of keys used by storage.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	THash		Hash used by storage.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline void DeletePointersAndClear( std::unordered_map<TKey, TItem*, THash, TPredicate, TAllocator>& storage );

	/**
		@brief	Look for `key` in `storage` and return the stored item or `default_result`.
		@param	storage			The storage to remove.
		@param	key				The key for item to remove.
		@param	default_result	The 'default' item to be used as result in case the `key` not found.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is an item by `key` in `storage` or `default_result`.
		@retval	default_result	In case of no `key` found in `storage`.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline TItem& FindItem( std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key, TItem& default_result );

	/**
		@brief	Look for `key` in `storage` and return the stored item or `default_result`.
		@param	storage			The storage to remove.
		@param	key				The key for item to remove.
		@param	default_result	The 'default' item to be used as result in case the `key` not found.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is an item by `key` in `storage` or `default_result`.
		@retval	default_result	In case of no `key` found in `storage`.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline const TItem& FindItem( const std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key, const TItem& default_result );

	/**
		@brief	Look for `key` in `storage` and call `on_found` only with found item.
		@param	storage			The storage to remove.
		@param	key				The key for item to remove.
		@param	on_found		The function-like object to be called on stored item.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@tparam	TFunction		Type of function-acceptor of found item.
		@return					`true` only when the item was found and `on_found` was called.
		@retval	false			In case the given `key` does not exist in storage.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator, typename TFunction >
	inline const bool FindItem( std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key, TFunction on_found );

	/**
		@brief	Look for `key` in `storage` and call `on_found` only with found item.
		@param	storage			The storage to remove.
		@param	key				The key for item to remove.
		@param	on_found		The function-like object to be called on stored item.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@tparam	TFunction		Type of function-acceptor of found item.
		@return					`true` only when the item was found and `on_found` was called.
		@retval	false			In case the given `key` does not exist in storage.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator, typename TFunction >
	inline const bool FindItem( const std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key, TFunction on_found );

	/**
		@brief	Look for `key` in `storage` and return the stored item or `default_result`.
		@param	storage			The storage to remove.
		@param	key				The key for item to remove.
		@param	default_result	The 'default' item to be used as result in case the `key` not found.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	THash			Hash used by storage.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is an item by `key` in `storage` or `default_result`.
		@retval	default_result	In case of no `key` found in `storage`.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline TItem& FindItem( std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, TItem& default_result );

	/**
		@brief	Look for `key` in `storage` and return the stored item or `default_result`.
		@param	storage			The storage to remove.
		@param	key				The key for item to remove.
		@param	default_result	The 'default' item to be used as result in case the `key` not found.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	THash			Hash used by storage.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@return					The value returned is an item by `key` in `storage` or `default_result`.
		@retval	default_result	In case of no `key` found in `storage`.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline const TItem& FindItem( const std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, const TItem& default_result );

	/**
		@brief	Look for `key` in `storage` and call `on_found` only with found item.
		@param	storage			The storage to remove.
		@param	key				The key for item to remove.
		@param	on_found		The function-like object to be called on stored item.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	THash			Hash used by storage.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@tparam	TFunction		Type of function-acceptor of found item.
		@return					`true` only when the item was found and `on_found` was called.
		@retval	false			In case the given `key` does not exist in storage.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator, typename TFunction >
	inline const bool FindItem( std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, TFunction on_found );

	/**
		@brief	Look for `key` in `storage` and call `on_found` only with found item.
		@param	storage			The storage to remove.
		@param	key				The key for item to remove.
		@param	on_found		The function-like object to be called on stored item.
		@tparam	TKey			Type of keys used by storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	THash			Hash used by storage.
		@tparam	TPredicate		Predicate used by storage.
		@tparam	TAllocator		Allocator used by storage.
		@tparam	TFunction		Type of function-acceptor of found item.
		@return					`true` only when the item was found and `on_found` was called.
		@retval	false			In case the given `key` does not exist in storage.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator, typename TFunction >
	inline const bool FindItem( const std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, TFunction on_found );

	/**
		@brief	Get the position of `item` in `storage`.
		@param	storage			The storage to check.
		@param	item			The item to check.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	TAllocator		Allocator used by storage.
		@tparam	TStorage		Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return					The value returned is an position of `item` in `storage` or `UNDEFINED_INDEX`.
		@retval	UNDEFINED_INDEX	Returned if no `item` was found inside `storage`.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const size_t GetItemIndex( const TStorage<TItem, TAllocator>& storage, const TItem& item );

	/**
		@brief	Get the position of `item` in `storage`.
		@param	storage			The storage to check.
		@param	item			The item to check.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	ARRAY_LENGTH	Number of elements in storage.
		@return					The value returned is an position of `item` in `storage` or `UNDEFINED_INDEX`.
		@retval	UNDEFINED_INDEX	Returned if no `item` was found inside `storage`.
	*/
	template< typename TItem, size_t ARRAY_LENGTH >
	inline const size_t GetItemIndex( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item );

	/**
		@brief	Get the position of `item` in `storage`.
		@param	storage			The storage to check.
		@param	item			The item to check.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					The value returned is an position of `item` in `storage` or `UNDEFINED_INDEX`.
		@retval	UNDEFINED_INDEX	Returned if no `item` was found inside `storage`.
	*/
	template< typename TItem >
	inline const size_t GetItemIndex( const PlainView<TItem>& storage, const TItem& item );

	/**
		@brief	Get the position of `item` in `storage`.
		@param	storage			The storage to check.
		@param	item			The item to check.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					The value returned is an position of `item` in `storage` or `UNDEFINED_INDEX`.
		@retval	UNDEFINED_INDEX	Returned if no `item` was found inside `storage`.
	*/
	template< typename TItem >
	inline const size_t GetItemIndex( const PlainVector<TItem>& storage, const TItem& item );
}
}
}
