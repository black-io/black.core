#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Utils
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
	inline const bool IsItemExists( const TStorage<TItem, TAllocator>& storage, const TItem& item );

	/**
		@brief	Check that the item storage contains the item.
		@param	storage			The storage to check.
		@param	item			The item to check.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	ARRAY_LENGTH	Number of elements in storage.
		@return					`true` if storage contain the item.
	*/
	template< typename TItem, size_t ARRAY_LENGTH >
	inline const bool IsItemExists( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item );

	/**
		@brief	Check that the item storage contains the item.
		@param	storage			The storage to check.
		@param	item			The item to check.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					`true` if storage contain the item.
	*/
	template< typename TItem >
	inline const bool IsItemExists( const PlainView<TItem>& storage, const TItem& item );

	/**
		@brief	Check that the item storage contains the item.
		@param	storage			The storage to check.
		@param	item			The item to check.
		@tparam	TItem		Type of storage content and type of item as well.
		@return					`true` if storage contain the item.
	*/
	template< typename TItem >
	inline const bool IsItemExists( const PlainVector<TItem>& storage, const TItem& item );

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
	inline const bool IsItemExists( const std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item );

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
	inline const bool IsItemExists( const std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key );

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
	inline const bool IsItemExists( const std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key );

	/**
		@brief	Uniquely insert the item into storage.
		@param	storage		The storage to add.
		@param	item		The item to add.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TAllocator	Allocator used by storage.
		@tparam	TStorage	Type of storage implementation (compatible with `std::vector`, `std::list` and `std::deque`).
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TItem, typename TAllocator, template< typename, typename > class TStorage >
	inline const bool UniqueAdd( TStorage<TItem, TAllocator>& storage, const TItem& item );

	/**
		@brief	Uniquely insert the item into storage.
		@param	storage		The storage to add.
		@param	item		The item to add.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TItem, typename TPredicate, typename TAllocator >
	inline const bool UniqueAdd( std::set<TItem, TPredicate, TAllocator>& storage, const TItem& item );

	/**
		@brief	Uniquely insert the item into storage.
		@param	storage		The storage to add.
		@param	key			The key for item to add.
		@param	item		The item to add.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TKey, typename TItem, typename TPredicate, typename TAllocator >
	inline const bool UniqueAdd( std::map<TKey, TItem, TPredicate, TAllocator>& storage, const TKey& key, const TItem& item );

	/**
		@brief	Uniquely insert the item into storage.
		@param	storage		The storage to add.
		@param	key			The key for item to add.
		@param	item		The item to add.
		@tparam	TKey		Type of keys used by storage.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	THash		Hash used by storage.
		@tparam	TPredicate	Predicate used by storage.
		@tparam	TAllocator	Allocator used by storage.
		@return				`true` if item successfully inserted into storage.
	*/
	template< typename TKey, typename TItem, typename THash, typename TPredicate, typename TAllocator >
	inline const bool UniqueAdd( std::unordered_map<TKey, TItem, THash, TPredicate, TAllocator>& storage, const TKey& key, const TItem& item );

	/**
		@brief	Uniquely insert the item into storage.
		@note	Unlike the `UniqueAdd` function, this one will return the positional number of item in storage.
		@param	storage		The storage to add.
		@param	item		The item to add.
		@tparam	TItem		Type of storage content and type of item as well.
		@tparam	TAllocator	Allocator used by storage.
		@return				index of item in storage.
	*/
	template< typename TItem, typename TAllocator >
	inline const size_t UniqueAddIndexed( std::vector<TItem, TAllocator>& storage, const TItem& item );

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
