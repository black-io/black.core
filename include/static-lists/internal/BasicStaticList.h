#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
namespace Internal
{
	/**
		@breif	Implementation of common functionality for arbitrary static list.

		This list carries the storage of root node for entire collection.
		Each collection may be accessed only using the particular tagging type. Such type identifies the collection and its nodes.

		@tparam	TStorageTag		Tagging type to indicate the unique static collection.
	*/
	template< typename TStorageTag >
	class BasicStaticList
	{
	// Friendship.
	public:
		friend class BasicStaticNode<TStorageTag>; // Grant access to `AccessRootNode` function.

	// Public inner types.
	public:
		// Type of stored node.
		using Node = BasicStaticNode<TStorageTag>;

	// Public interface.
	public:
		// Get the head of list.
		static inline Node* GetRootNode();


		// Whether the collection is empty.
		static inline const bool IsEmpty();

	// Private interface.
	private:
		// Access the root of current static list.
		static inline Node*& AccessRootNode();
	};
}
}
}
}
