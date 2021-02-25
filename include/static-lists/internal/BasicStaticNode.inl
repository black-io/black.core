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
		const Black::MutexLock lock{ BasicStaticList<TStorageTag>::GetMutex() };
		// Early exit due to the node is already in the static list.
		CRET( m_next_node != nullptr );

		m_next_node = std::exchange( BasicStaticList<TStorageTag>::AccessRootNode(), this );
	}
}
}
}
}
