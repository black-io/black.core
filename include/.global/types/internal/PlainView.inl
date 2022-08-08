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
	inline PlainView<TValue>::PlainView( PlainView<TValue>&& other ) noexcept
		: m_memory{ std::exchange( other.m_memory, nullptr ) }
		, m_length{ std::exchange( other.m_length, 0 ) }
	{
	}

	template< typename TValue >
	PlainView<TValue>::PlainView( ValuePointer memory, const size_t length )
		: m_memory{ memory }
		, m_length{ length }
	{
		EXPECTS( ( memory != nullptr ) || ( length == 0 ) );
	}

	template< typename TValue >
	inline PlainView<TValue>& PlainView<TValue>::operator=( PlainView<TValue>&& other ) noexcept
	{
		CRET( &other == this, *this );

		Invalidate();
		Swap( other );

		return *this;
	}

	template< typename TValue >
	inline void PlainView<TValue>::Invalidate()
	{
		m_memory	= nullptr;
		m_length	= 0;
	}

	template< typename TValue >
	inline void PlainView<TValue>::Swap( PlainView& other )
	{
		using std::swap;
		swap( m_memory, other.m_memory );
		swap( m_length, other.m_length );
	}

	template< typename TValue >
	inline const bool PlainView<TValue>::IsEmpty() const
	{
		return m_length == 0;
	}

	template< typename TValue >
	inline const bool PlainView<TValue>::IsInside( Iterator value ) const
	{
		return ( value >= GetBegin() ) && ( value < GetEnd() );
	}

	template< typename TValue >
	inline TValue& PlainView<TValue>::GetValueAt( const size_t index ) const
	{
		EXPECTS( index < m_length );
		return m_memory[ index ];
	}
}
}
}
}
}
