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
	inline void BasicStaticNode<TInterface>::PlugIntoList()
	{
		m_next_node = std::exchange( Black::StaticList<TInterface>::GetRootNode(), this );
	}
}
}
}
}
