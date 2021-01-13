#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
	template< typename TInterface >
	template< typename TImplementation >
	inline TImplementation& StaticList<TInterface>::Get()
	{
		static_assert( std::is_base_of_v<TInterface, TImplementation>, "`TImplementation` should be derived from `TInterface`." );

		static Node<TImplementation> storage{ Black::CONSTRUCT_INPLACE };
		return *storage;
	}

	template< typename TInterface >
	inline void StaticList<TInterface>::DestroyStoredInstances()
	{
		 Parent::template EnumerateNodes( []( typename Parent::Node* node ) { node->Invalidate(); } );
	}

	template< typename TInterface >
	inline const bool StaticList<TInterface>::IsEmpty() const
	{
		return Parent::IsEmpty();
	}

	template< typename TInterface >
	typename StaticList<TInterface>::CommonNode* StaticList<TInterface>::GetRootNode()
	{
		return static_cast<CommonNode*>( Parent::GetRootNode() );
	}
}
}
}
