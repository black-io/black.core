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
	inline const bool BasicStaticList<TStorageTag>::IsEmpty()
	{
		return AccessRootNode() == nullptr;
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
