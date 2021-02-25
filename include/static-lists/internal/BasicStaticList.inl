#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
namespace Internal
{
	template< typename TStorageTag >
	inline typename BasicStaticList<TStorageTag>::Node* BasicStaticList<TStorageTag>::GetRootNode()
	{
		return AccessRootNode();
	}

	template< typename TStorageTag >
	template< typename TFunction >
	inline void BasicStaticList<TStorageTag>::EnumerateNodes( TFunction consumer )
	{
		static_assert( std::is_invocable_v<TFunction, Node*>, "The given function should be safe to accept the enumerated nodes." );
		static_assert( std::is_same_v<std::invoke_result_t<TFunction, Node*>, void>, "The given function may not return any value." );

		for( Node* node = GetRootNode(); node != nullptr; node = node->m_next_node )
		{
			consumer( node );
		}
	}

	template< typename TStorageTag >
	inline void BasicStaticList<TStorageTag>::Clear()
	{
		Node* node = std::exchange( AccessRootNode(), nullptr );
		while( node != nullptr )
		{
			node = std::exchange( node->m_next_node, nullptr );
		}
	}

	template< typename TStorageTag >
	inline const bool BasicStaticList<TStorageTag>::IsEmpty()
	{
		return AccessRootNode() == nullptr;
	}

	template< typename TStorageTag >
	inline const Black::Mutex& BasicStaticList<TStorageTag>::GetMutex()
	{
		static Black::SpinLock mutex;
		return mutex;
	}

	template< typename TStorageTag >
	inline typename BasicStaticList<TStorageTag>::Node*& BasicStaticList<TStorageTag>::AccessRootNode()
	{
		// Escaping the 'static initialization order fiasco'.
		static Node* root_node = nullptr;
		return root_node;
	}
}
}
}
}
