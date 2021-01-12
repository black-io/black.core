#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
namespace Internal
{
	template< typename TInterface >
	inline BasicStaticNode<TInterface>* const BasicStaticNode<TInterface>::GetNextNode() const
	{
		return m_next_node;
	}

	template< typename TInterface >
	inline void BasicStaticNode<TInterface>::PlugIntoList()
	{
		EXPECTS_DEBUG( m_next_node == nullptr );
		m_next_node = std::exchange( Black::StaticList<TInterface>::GetRootNode(), this );
	}
}
}
}
}
