#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	template< typename TLinkedType >
	IntrusiveLink<TLinkedType, true>::IntrusiveLink( const IntrusiveLink& other )
		: IntrusiveLink{ other.m_hook }
	{}

	template< typename TLinkedType >
	IntrusiveLink<TLinkedType, true>::IntrusiveLink( IntrusiveLink&& other )
		: m_hook{ other.m_hook }
	{
		RegisterLink();
		other.UnregisterLink();
		other.InvalidateIntrusiveLink();
	}

	template< typename TLinkedType >
	IntrusiveLink<TLinkedType, true>::IntrusiveLink( const TLinkedType* hook )
		: m_hook{ hook }
	{
		RegisterLink();
	}

	template< typename TLinkedType >
	IntrusiveLink<TLinkedType, true>::~IntrusiveLink()
	{
		UnregisterLink();
	}

	template< typename TLinkedType >
	void IntrusiveLink<TLinkedType, true>::SetHook( const TLinkedType* hook )
	{
		UnregisterLink();
		m_hook= hook;
		RegisterLink();
	}

	template< typename TLinkedType >
	void IntrusiveLink<TLinkedType, true>::InvalidateIntrusiveLink()
	{
		m_hook = nullptr;
	}

	template< typename TLinkedType >
	void IntrusiveLink<TLinkedType, true>::RegisterLink()
	{
		CRET( m_hook == nullptr );
		m_hook->AddIntrusiveLink( this );
	}

	template< typename TLinkedType >
	void IntrusiveLink<TLinkedType, true>::UnregisterLink()
	{
		CRET( m_hook == nullptr );
		m_hook->RemoveIntrusiveLink( this );
	}
}
}
}
