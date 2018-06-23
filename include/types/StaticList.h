#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	// The implementation of static list.
	template< typename TInterface >
	class StaticList final
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
		using iterator			= Iterator;
		using const_iterator	= Iterator;

		// Ranged for-loop interface.
		friend inline Iterator begin( const StaticList& static_list )	{ return static_list.GetHead(); };
		friend inline Iterator end( const StaticList& static_list )		{ return static_list.GetTail(); };

		// Grant access to root of list.
		friend class Internal::StaticListBasicNode<TInterface>;

	// Public interface.
	public:
		// Get the implementation.
		template< typename TImplementation >
		static inline TImplementation& Get();

		// Clear the list. All stored implementations will be destroyed at this moment.
		void Clear();

		// Get the head of list.
		inline Iterator GetHead() const									{ return Iterator{ GetRootNode() }; };

		// Get the tail f list.
		inline Iterator GetTail() const									{ return Iterator{ nullptr }; };

	// Private state.
	private:
		// Get the root node.
		static Internal::StaticListBasicNode<TInterface>*& GetRootNode();
	};
}
}
}
