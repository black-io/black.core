#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Algorithms
{
	/**
		@brief	Check that the given `storage` contains the `item`.
		@param	storage			The storage to check.
		@param	item			The item to check.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	ARRAY_LENGTH	Number of elements in storage.
		@return					`true` if storage contain the item.
	*/
	template< typename TItem, size_t ARRAY_LENGTH >
	inline const bool HasItem( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item );

	/**
		@brief	Check that the given `storage` contains the `item`.
		@param	storage		The storage to check.
		@param	item		The item to check.
		@tparam	TItem		Type of storage content and type of item as well.
		@return				`true` if storage contain the item.
	*/
	template< typename TItem >
	inline const bool HasItem( const PlainView<TItem>& storage, const TItem& item );

	/**
		@brief	Check that the given `storage` contains the `item`.
		@param	storage		The storage to check.
		@param	item		The item to check.
		@tparam	TItem		Type of storage content and type of item as well.
		@return				`true` if storage contain the item.
	*/
	template< typename TItem >
	inline const bool HasItem( const PlainVector<TItem>& storage, const TItem& item );

	/**
		@brief	Clear the storage, deleting the stored content.
		This function may be used for cases if container used to store raw pointers.
		@param	storage		The storage to clear.
		@tparam	TItem		Type of storage content.
	*/
	template< typename TItem >
	inline void DeletePointersAndClear( PlainVector<TItem*>& storage );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@param	default_result	Value to be returned in case the item not found in storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	ARRAY_LENGTH	Number of elements in storage.
		@return					The value returned is first found in storage.
		@retval	default_value	In case of no `item` found in `storage`.
	*/
	template< typename TItem, size_t ARRAY_LENGTH >
	inline TItem& FindItem( TItem (&storage)[ ARRAY_LENGTH ], const TItem& item, TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@param	default_result	Value to be returned in case the item not found in storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	ARRAY_LENGTH	Number of elements in storage.
		@return					The value returned is first found in storage.
		@retval	default_value	In case of no `item` found in `storage`.
	*/
	template< typename TItem, size_t ARRAY_LENGTH >
	inline const TItem& FindItem( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item, const TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@param	default_result	Value to be returned in case the item not found in storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					The value returned is first found in storage.
		@retval	default_value	In case of no `item` found in `storage`.
	*/
	template< typename TItem >
	inline TItem& FindItem( PlainView<TItem>& storage, const TItem& item, TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@param	default_result	Value to be returned in case the item not found in storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					The value returned is first found in storage.
		@retval	default_value	In case of no `item` found in `storage`.
	*/
	template< typename TItem >
	inline const TItem& FindItem( const PlainView<TItem>& storage, const TItem& item, const TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@param	default_result	Value to be returned in case the item not found in storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					The value returned is first found in storage.
		@retval	default_value	In case of no `item` found in `storage`.
	*/
	template< typename TItem >
	inline TItem& FindItem( PlainVector<TItem>& storage, const TItem& item, TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@param	default_result	Value to be returned in case the item not found in storage.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					The value returned is first found in storage.
		@retval	default_value	In case of no `item` found in `storage`.
	*/
	template< typename TItem >
	inline const TItem& FindItem( const PlainVector<TItem>& storage, const TItem& item, const TItem& default_result );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	ARRAY_LENGTH	Number of elements in storage.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, size_t ARRAY_LENGTH >
	inline Hypothetical<TItem&> FindItem( TItem (&storage)[ ARRAY_LENGTH ], const TItem& item );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	ARRAY_LENGTH	Number of elements in storage.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, size_t ARRAY_LENGTH >
	inline Hypothetical<const TItem&> FindItem( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item );

	/**
		@brief	Find the item in given storage.
		This function uses the `criteria` predicate to find the item to be found.
		@param	storage			The storage to look up.
		@param	criteria		Function-like predicate, used as criteria to determine the item to be found.
		@tparam	TItem			Type of storage content.
		@tparam	ARRAY_LENGTH	Number of elements in storage.
		@tparam	TCriteria		Type of criteria function.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, size_t ARRAY_LENGTH, typename TCriteria >
	inline auto FindItem(
		TItem (&storage)[ ARRAY_LENGTH ],
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<TItem&>>;

	/**
		@brief	Find the item in given storage.
		This function uses the `criteria` predicate to find the item to be found.
		@param	storage			The storage to look up.
		@param	criteria		Function-like predicate, used as criteria to determine the item to be found.
		@tparam	TItem			Type of storage content.
		@tparam	ARRAY_LENGTH	Number of elements in storage.
		@tparam	TCriteria		Type of criteria function.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, size_t ARRAY_LENGTH, typename TCriteria >
	inline auto FindItem(
		const TItem (&storage)[ ARRAY_LENGTH ],
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<const TItem&>>;

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem >
	inline Hypothetical<TItem&> FindItem( PlainView<TItem>& storage, const TItem& item );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem >
	inline Hypothetical<const TItem&> FindItem( const PlainView<TItem>& storage, const TItem& item );

	/**
		@brief	Find the item in given storage.
		This function uses the `criteria` predicate to find the item to be found.
		@param	storage			The storage to look up.
		@param	criteria		Function-like predicate, used as criteria to determine the item to be found.
		@tparam	TItem			Type of storage content.
		@tparam	TCriteria		Type of criteria function.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, typename TCriteria >
	inline auto FindItem(
		PlainView<TItem>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<TItem&>>;

	/**
		@brief	Find the item in given storage.
		This function uses the `criteria` predicate to find the item to be found.
		@param	storage			The storage to look up.
		@param	criteria		Function-like predicate, used as criteria to determine the item to be found.
		@tparam	TItem			Type of storage content.
		@tparam	TCriteria		Type of criteria function.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, typename TCriteria >
	inline auto FindItem(
		const PlainView<TItem>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<const TItem&>>;

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem >
	inline Hypothetical<TItem&> FindItem( PlainVector<TItem>& storage, const TItem& item );

	/**
		@brief	Find the item in given storage.
		This function uses the `item` to find the equivalent inside of storage.
		@param	storage			The storage to look up.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem >
	inline Hypothetical<const TItem&> FindItem( const PlainVector<TItem>& storage, const TItem& item );

	/**
		@brief	Find the item in given storage.
		This function uses the `criteria` predicate to find the item to be found.
		@param	storage			The storage to look up.
		@param	criteria		Function-like predicate, used as criteria to determine the item to be found.
		@tparam	TItem			Type of storage content.
		@tparam	TCriteria		Type of criteria function.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, typename TCriteria >
	inline auto FindItem(
		PlainVector<TItem>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<TItem&>>;

	/**
		@brief	Find the item in given storage.
		This function uses the `criteria` predicate to find the item to be found.
		@param	storage			The storage to look up.
		@param	criteria		Function-like predicate, used as criteria to determine the item to be found.
		@tparam	TItem			Type of storage content.
		@tparam	TCriteria		Type of criteria function.
		@return					The value returned is Hypothetical with reference to found value.
		@retval	{}				In case of no item found in storage.
	*/
	template< typename TItem, typename TCriteria >
	inline auto FindItem(
		const PlainVector<TItem>& storage,
		TCriteria&& criteria
	) -> std::enable_if_t<!std::is_same_v<std::decay_t<TItem>, std::decay_t<TCriteria>>, Hypothetical<const TItem&>>;

	/**
		@brief	Get the position of `item` in `storage`.
		@param	storage			The storage to inspect.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@tparam	ARRAY_LENGTH	Number of elements in storage.
		@return					The value returned is an position of `item` in `storage` or `UNDEFINED_INDEX`.
		@retval	UNDEFINED_INDEX	Returned if no `item` was found inside `storage`.
	*/
	template< typename TItem, size_t ARRAY_LENGTH >
	inline const size_t GetItemIndex( const TItem (&storage)[ ARRAY_LENGTH ], const TItem& item );

	/**
		@brief	Get the position of `item` in `storage`.
		@param	storage			The storage to inspect.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					The value returned is an position of `item` in `storage` or `UNDEFINED_INDEX`.
		@retval	UNDEFINED_INDEX	Returned if no `item` was found inside `storage`.
	*/
	template< typename TItem >
	inline const size_t GetItemIndex( const PlainView<TItem>& storage, const TItem& item );

	/**
		@brief	Get the position of `item` in `storage`.
		@param	storage			The storage to inspect.
		@param	item			The item to be found.
		@tparam	TItem			Type of storage content and type of item as well.
		@return					The value returned is an position of `item` in `storage` or `UNDEFINED_INDEX`.
		@retval	UNDEFINED_INDEX	Returned if no `item` was found inside `storage`.
	*/
	template< typename TItem >
	inline const size_t GetItemIndex( const PlainVector<TItem>& storage, const TItem& item );
}
}
}
