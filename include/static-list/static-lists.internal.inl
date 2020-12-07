#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
namespace Internal
{
	template< typename TInterface >
	inline void StaticListBasicNode<TInterface>::PlugIntoList()
	{
		m_next_node = std::exchange( Black::StaticList<TInterface>::GetRootNode(), this );
	}
}
}
}
}
