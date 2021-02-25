#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
namespace Internal
{
	template< typename TInterface, typename TImplementation >
	template< typename... TArguments >
	inline StaticListNode<TInterface, TImplementation>::StaticListNode( Black::ConstructInplace, TArguments&&... arguments )
		: StaticListNode{ TImplementation::GetDebugName(), Black::CONSTRUCT_INPLACE, std::forward<TArguments>( arguments )... }
	{}

	template< typename TInterface, typename TImplementation >
	template< typename... TArguments >
	inline StaticListNode<TInterface, TImplementation>::StaticListNode( Black::DebugName&& name, Black::ConstructInplace, TArguments&&... arguments )
		: StaticListNode{ std::move( name ) }
	{
		Construct( std::forward<TArguments>( arguments )... );
	}

	template< typename TInterface, typename TImplementation >
	StaticListNode<TInterface, TImplementation>::~StaticListNode()
	{
		Destroy();
	}

	template< typename TInterface, typename TImplementation >
	template< typename... TArguments >
	inline TImplementation& StaticListNode<TInterface, TImplementation>::Construct( TArguments&&... arguments ) const
	{
		static_assert( std::is_base_of_v<TInterface, TImplementation>, "`TImplementation` should be derived from `TInterface`." );

		const Black::MutexLock lock{ m_lock };
		// It may happen after synchronization that the implementation is already created.
		CRET( m_implementation != nullptr, *m_implementation );

		m_implementation = ConstructionProxy<TImplementation>::Construct( m_storage, std::forward<TArguments>( arguments )... );

		ENSURES_DEBUG( m_implementation != nullptr );
		return *m_implementation;
	}

	template< typename TInterface, typename TImplementation >
	inline void StaticListNode<TInterface, TImplementation>::Destroy()
	{
		CRET( m_implementation == nullptr );
		std::exchange( m_implementation, nullptr )->~TImplementation();
	}

	template< typename TInterface, typename TImplementation >
	inline TImplementation& StaticListNode<TInterface, TImplementation>::GetImplementation() const
	{
		return ( m_implementation == nullptr )? Construct() : *m_implementation;
	}
}
}
}
}
