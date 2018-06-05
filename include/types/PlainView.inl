#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	template< typename TStoredType >
	PlainView<TStoredType>::PlainView( PlainView<TStoredType>&& other )
	{
		Swap( other );
	}

	template< typename TStoredType >
	PlainView<TStoredType>::PlainView( typename PlainView<TStoredType>::Element* head, typename PlainView<TStoredType>::Element* tail )
		: m_head{ head }
		, m_tail{ tail }
		, m_length{ static_cast<size_t>( tail - head ) }
	{
		EXPECTS( ( !head && !tail ) || ( tail >= head ) );
	}

	template< typename TStoredType >
	PlainView<TStoredType>::PlainView( typename PlainView<TStoredType>::Element* head, const size_t length )
		: m_head{ head }
		, m_tail{ head + length }
		, m_length{ length }
	{
		EXPECTS( ( head != nullptr ) || ( length == 0 ) );
	}

	template< typename TStoredType >
	inline PlainView<TStoredType>& PlainView<TStoredType>::operator=( PlainView<TStoredType>&& other )
	{
		CRET( *this == other, *this );

		Invalidate();
		Swap( other );

		return *this;
	}

	template< typename TStoredType >
	inline void PlainView<TStoredType>::Invalidate()
	{
		m_head		= nullptr;
		m_tail		= nullptr;
		m_length	= 0;
	}

	template< typename TStoredType >
	inline void PlainView<TStoredType>::Swap( PlainView& other )
	{
		using std::swap;
		swap( m_head, other.m_head );
		swap( m_tail, other.m_tail );
		swap( m_length, other.m_length );
	}

	template< typename TStoredType >
	inline const bool PlainView<TStoredType>::IsEmpty() const
	{
		return m_length == 0;
	}

	template< typename TStoredType >
	inline const bool PlainView<TStoredType>::IsInside( Iterator value ) const
	{
		return ( value >= m_head ) && ( value < m_tail );
	}

	template< typename TStoredType >
	inline TStoredType& PlainView<TStoredType>::GetElement( const size_t index ) const
	{
		EXPECTS( index < m_length );
		return m_head[ index ];
	}

	template< typename TStoredType >
	inline const bool PlainView<TStoredType>::operator==( const PlainView<TStoredType>& other ) const
	{
		return ( m_head == other.m_head ) && ( m_length == other.m_length );
	}

	template< typename TStoredType >
	inline const bool PlainView<TStoredType>::operator!=( const PlainView<TStoredType>& other ) const
	{
		return ( m_head != other.m_head ) || ( m_length != other.m_length );
	}
}
}
}
