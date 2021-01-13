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
	StaticListIterator<TInterface>::StaticListIterator( StaticListIterator&& other )
		: m_current_node{ std::exchange( other.m_current_node, nullptr ) }
	{

	}

	template< typename TInterface >
	StaticListIterator<TInterface>::StaticListIterator( StaticListCommonNode<TInterface>* root_node )
		: m_current_node{ root_node }
	{

	}

	template< typename TInterface >
	inline StaticListIterator<TInterface>& StaticListIterator<TInterface>::operator=( StaticListCommonNode<TInterface>* root_node )
	{
		m_current_node = root_node;
		return *this;
	}

	template< typename TInterface >
	inline StaticListIterator<TInterface>& StaticListIterator<TInterface>::operator=( StaticListIterator&& other )
	{
		m_current_node = std::exchange( other.m_current_node, nullptr );
		return *this;
	}

	template< typename TInterface >
	inline StaticListIterator<TInterface>& StaticListIterator<TInterface>::operator=( std::nullptr_t )
	{
		m_current_node = nullptr;
		return *this;
	}

	template< typename TInterface >
	inline StaticListCommonNode<TInterface>* StaticListIterator<TInterface>::GetNode() const
	{
		EXPECTS_DEBUG( m_current_node != nullptr );
		return m_current_node;
	}

	template< typename TInterface >
	inline typename StaticListIterator<TInterface>::self_type& StaticListIterator<TInterface>::operator++()
	{
		GoNextNode();
		return *this;
	}

	template< typename TInterface >
	inline typename StaticListIterator<TInterface>::self_type StaticListIterator<TInterface>::operator++( int )
	{
		self_type result{ m_current_node };
		GoNextNode();

		return result;
	}

	template< typename TInterface >
	inline typename StaticListIterator<TInterface>::reference StaticListIterator<TInterface>::operator*() const
	{
		return GetNode()->GetInterface();
	}

	template< typename TInterface >
	inline typename StaticListIterator<TInterface>::pointer StaticListIterator<TInterface>::operator->() const
	{
		return &GetNode()->GetInterface();
	}

	template< typename TInterface >
	inline void StaticListIterator<TInterface>::GoNextNode()
	{
		EXPECTS_DEBUG( m_current_node != nullptr );
		m_current_node = m_current_node->GetNextNode();
	}
}
}
}
}
