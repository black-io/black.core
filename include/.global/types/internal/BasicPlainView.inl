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
	inline BasicPlainView<TValue>::BasicPlainView( BasicPlainView<TValue>&& other ) noexcept
		: m_memory{ std::exchange( other.m_memory, nullptr ) }
		, m_length{ std::exchange( other.m_length, 0 ) }
	{
	}

	template< typename TValue >
	BasicPlainView<TValue>::BasicPlainView( ValuePointer memory, const size_t length )
		: m_memory{ memory }
		, m_length{ length }
	{
		EXPECTS( ( memory != nullptr ) || ( length == 0 ) );
	}

	template< typename TValue >
	inline BasicPlainView<TValue>& BasicPlainView<TValue>::operator=( BasicPlainView<TValue>&& other ) noexcept
	{
		CRET( &other == this, *this );

		Invalidate();
		Swap( other );

		return *this;
	}

	template< typename TValue >
	inline void BasicPlainView<TValue>::Invalidate()
	{
		m_memory	= nullptr;
		m_length	= 0;
	}

	template< typename TValue >
	inline void BasicPlainView<TValue>::Swap( BasicPlainView& other )
	{
		Black::Swap( m_memory, other.m_memory );
		Black::Swap( m_length, other.m_length );
	}

	template< typename TValue >
	inline const bool BasicPlainView<TValue>::IsEmpty() const
	{
		return m_length == 0;
	}

	template< typename TValue >
	inline const bool BasicPlainView<TValue>::IsInside( Iterator value ) const
	{
		return ( value >= GetBegin() ) && ( value < GetEnd() );
	}

	template< typename TValue >
	inline TValue& BasicPlainView<TValue>::GetValueAt( const size_t index ) const
	{
		EXPECTS( index < m_length );
		return m_memory[ index ];
	}
}
}
}
}
}
