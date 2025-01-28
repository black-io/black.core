#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
namespace Internal
{
	template< typename TValue >
	inline HypotheticalValue<TValue>::HypotheticalValue( const HypotheticalValue& other ) noexcept
	{
		CRET( other.IsEmpty() );
		AllocateStorage( other.m_storage->value );
	}

	template< typename TValue >
	inline HypotheticalValue<TValue>::HypotheticalValue( HypotheticalValue&& other ) noexcept
	{
		CRET( other.IsEmpty() );
		AllocateStorage( std::forward<ForwardingValue>( other.m_storage->value ) );
		other.DisposeStorage();
	}

	template< typename TValue >
	inline HypotheticalValue<TValue>::~HypotheticalValue() noexcept
	{
		DisposeStorage();
	}

	template< typename TValue >
	inline HypotheticalValue<TValue>::HypotheticalValue( TValue value ) noexcept
	{
		AllocateStorage( std::forward<ForwardingValue>( value ) );
	}

	template< typename TValue >
	inline void HypotheticalValue<TValue>::Clear()
	{
		DisposeStorage();
	}

	template< typename TValue >
	inline void HypotheticalValue<TValue>::Swap( HypotheticalValue& other )
	{
		alignas( ValueStorage ) ValueBuffer	temporary_buffer;
		ValueStorage*						temporary_storage = nullptr;

		if( HasValue() )
		{
			temporary_storage = new( temporary_buffer ) ValueStorage{ std::forward<ForwardingValue>( m_storage->value ) };
			DisposeStorage();
		}

		if( other.HasValue() )
		{
			AllocateStorage( std::forward<ForwardingValue>( other.m_storage->value ) );
			other.DisposeStorage();
		}

		if( temporary_storage != nullptr )
		{
			other.AllocateStorage( std::forward<ForwardingValue>( temporary_storage->vlaue ) );
			temporary_storage->~ValueStorage();
		}
	}

	template< typename TValue >
	inline TValue& HypotheticalValue<TValue>::GetValue() &
	{
		ENSURES_DEBUG( HasValue() );
		return m_storage->value;
	}

	template< typename TValue >
	inline const TValue& HypotheticalValue<TValue>::GetValue() const &
	{
		ENSURES_DEBUG( HasValue() );
		return m_storage->value;
	}

	template< typename TValue >
	inline TValue HypotheticalValue<TValue>::GetValue() &&
	{
		ENSURES_DEBUG( HasValue() );
		TValue result{ std::forward<ForwardingValue>( m_storage->value ) };
		DisposeStorage();
		return result;
	}

	template< typename TValue >
	inline TValue& HypotheticalValue<TValue>::GetValue( TValue& default_value ) &
	{
		return ( HasValue() )? m_storage->value : default_value;
	}

	template< typename TValue >
	inline const TValue& HypotheticalValue<TValue>::GetValue( const TValue& default_value ) const &
	{
		return ( HasValue() )? m_storage->value : default_value;
	}

	template< typename TValue >
	inline TValue HypotheticalValue<TValue>::GetValue( TValue&& default_value ) &&
	{
		TValue result{ ( HasValue() )? std::forward<ForwardingValue>( m_storage->value ) : std::forward<ForwardingValue>( default_value ) };
		DisposeStorage();
		return result;
	}

	template< typename TValue >
	void HypotheticalValue<TValue>::AllocateStorage( TValue value )
	{
		DisposeStorage();
		m_storage = new( m_buffer ) ValueStorage{ std::forward<ForwardingValue>( value ) };
	}

	template< typename TValue >
	void HypotheticalValue<TValue>::DisposeStorage()
	{
		CRET( IsEmpty() );
		m_storage->~ValueStorage();
		m_storage = nullptr;
	}
}
}
}
}
}
