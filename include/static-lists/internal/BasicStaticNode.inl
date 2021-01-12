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
	inline BasicStaticNode<TStorageTag>* const BasicStaticNode<TStorageTag>::GetNextNode() const
	{
		return m_next_node;
	}

	template< typename TStorageTag >
	inline void BasicStaticNode<TStorageTag>::PlugIntoList()
	{
		EXPECTS_DEBUG( m_next_node == nullptr );
		m_next_node = std::exchange( BasicStaticList<TStorageTag>::AccessRootNode(), this );
	}
}
}
}
}
