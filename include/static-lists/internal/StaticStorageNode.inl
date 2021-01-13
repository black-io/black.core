#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
namespace Internal
{
	template< typename TStorageTag, typename TImplementation >
	inline TImplementation& StaticStorageNode<TStorageTag, TImplementation>::ConstructImplementation()
	{
		EXPECTS_DEBUG( m_implementation == nullptr );
		m_implementation = ConstructionProxy<TImplementation>::Construct( m_storage );

		ENSURES_DEBUG( m_implementation != nullptr );
		BasicStaticNode<TStorageTag>::PlugIntoList();
		return *m_implementation;
	}

	template< typename TStorageTag, typename TImplementation >
	inline TImplementation& StaticStorageNode<TStorageTag, TImplementation>::GetImplementation()
	{
		return ( m_implementation == nullptr )? ConstructImplementation() : *m_implementation;
	}

	template< typename TStorageTag, typename TImplementation >
	void StaticStorageNode<TStorageTag, TImplementation>::Invalidate()
	{
		CRET( m_implementation == nullptr );
		std::exchange(m_implementation, nullptr)->~TImplementation();
	}
}
}
}
}
