#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	template< typename TInterface >
	template< typename TImplementation >
	inline TImplementation& StaticList<TInterface>::Get()
	{
		static_assert( Black::IS_BASE_OF<TInterface, TImplementation>, "`TImplementation` should be derived from `TInterface`." );

		static Node<TImplementation> storage{ TImplementation::GetDebugName(), Black::CONSTRUCT_INPLACE };
		return *storage;
	}

	template< typename TInterface >
	void StaticList<TInterface>::Clear()
	{
		 auto node = std::exchange( GetRootNode(), nullptr );
		 while( node != nullptr )
		 {
			node->Invalidate();
			node = std::exchange( node->m_next_node, nullptr );
		 }
	}

	template< typename TInterface >
	Internal::StaticListBasicNode<TInterface>*& StaticList<TInterface>::GetRootNode()
	{
		// Escaping the 'static initialization order fiasco'.
		static Internal::StaticListBasicNode<TInterface>* s_root_node = nullptr;
		return s_root_node;
	}
}
}
}