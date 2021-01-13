#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
	/**
		@brief	The implementation of static list.

		@tparam	TInterface	The interface type of objects stored in static list.
	*/
	template< typename TInterface >
	class StaticList final : private Internal::BasicStaticList<Internal::InterfaceTag<TInterface>>
	{
	// Friendship and public types.
	public:
		// Type of list interface.
		using Interface = TInterface;

		// Regular node of list.
		template< typename TImplementation >
		using Node = Internal::StaticListNode<TInterface, TImplementation>;

		// Regular iterator for list.
		using Iterator			= Internal::StaticListIterator<TInterface>;
		using ConstIterator		= Internal::StaticListIterator<const TInterface>;
		using iterator			= Iterator;
		using const_iterator	= ConstIterator;


		// Ranged for-loop interface.
		friend inline Iterator begin( StaticList& static_list )					{ return static_list.GetBegin(); };
		friend inline Iterator end( StaticList& static_list )					{ return static_list.GetEnd(); };

		friend inline ConstIterator begin( const StaticList& static_list )		{ return static_list.GetBegin(); };
		friend inline ConstIterator end( const StaticList& static_list )		{ return static_list.GetEnd(); };

	// Public interface.
	public:
		// Get the stored implementation. Implementation will be created if not stored yet.
		template< typename TImplementation >
		static inline TImplementation& Get();

		// Destroy all instances stored in list. All nodes of list will remains linked.
		inline void DestroyStoredInstances();


		// Whether the list is empty.
		inline const bool IsEmpty() const;


		// Get the iterator to the head of list.
		inline Iterator GetBegin()					{ return Iterator{ GetRootNode() }; };

		// Get the iterator to the end of list.
		inline Iterator GetEnd()					{ return Iterator{ nullptr }; };

		// Get the iterator to the head of list.
		inline ConstIterator GetBegin() const		{ return ConstIterator{ GetRootNode() }; };

		// Get the iterator to the end of list.
		inline ConstIterator GetEnd() const			{ return ConstIterator{ nullptr }; };

	// Private inner types.
	private:
		// Type of basic static list.
		using Parent = Internal::BasicStaticList<Internal::InterfaceTag<TInterface>>;

		// Type of list node.
		using CommonNode = Internal::StaticListCommonNode<TInterface>;

	// Private state.
	private:
		// Get the root node.
		static CommonNode* GetRootNode();
	};
}
}
}
