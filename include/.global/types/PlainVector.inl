#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
	template< typename TStoredType >
	PlainVector<TStoredType>::PlainVector( const PlainVector& other )
	{
		CRET( other.IsEmpty() );
		SetLength( other.GetLength() );
		Black::CopyMemory( m_memory, other.m_memory, GetUsedBytes() );
	}

	template< typename TStoredType >
	PlainVector<TStoredType>::PlainVector( PlainVector&& other )
	{
		Swap( other );
	}

	template< typename TStoredType >
	PlainVector<TStoredType>::PlainVector( const size_t length )
	{
		SetLength( length );
	}

	template< typename TStoredType >
	PlainVector<TStoredType>::PlainVector( const size_t length, const TStoredType& proto )
	{
		SetCapacity( length );
		ConstructElements( length, proto );
	}

	template< typename TStoredType >
	PlainVector<TStoredType>::PlainVector( ConstIterator head, ConstIterator tail )
	{
		EXPECTS_DEBUG( ( !head && !tail ) || ( tail >= head ) );
		CopyElements( head, tail - head );
	}

	template< typename TStoredType >
	PlainVector<TStoredType>::~PlainVector()
	{
		Invalidate();
	}

	template< typename TStoredType >
	inline PlainVector<TStoredType>& PlainVector<TStoredType>::operator=( const PlainVector<TStoredType>& other )
	{
		CRET( other == *this, *this );

		Invalidate();
		SetLength( other.GetLength() );
		Black::CopyMemory( m_memory, other.m_memory, GetUsedBytes() );

		return *this;
	}

	template< typename TStoredType >
	inline PlainVector<TStoredType>& PlainVector<TStoredType>::operator=( PlainVector<TStoredType>&& other )
	{
		CRET( other == *this, *this );

		Invalidate();
		Swap( other );

		return *this;
	}

	template< typename TStoredType >
	inline void PlainVector<TStoredType>::Invalidate()
	{
		Black::SafeVectorDelete( m_memory );
		m_length	= 0;
		m_capacity	= 0;
	}

	template< typename TStoredType >
	inline void PlainVector<TStoredType>::Swap( PlainVector<TStoredType>& other )
	{
		using std::swap;
		swap( m_memory, other.m_memory );
		swap( m_capacity, other.m_capacity );
		swap( m_length, other.m_length );
	}

	template< typename TStoredType >
	inline void PlainVector<TStoredType>::SetLength( const size_t length )
	{
		CRET( length == m_length );

		if( length > m_capacity )
		{
			ReserveCapacity( length );
		}

		m_length = length;
	}

	template< typename TStoredType >
	inline void PlainVector<TStoredType>::ReserveCapacity( const size_t capacity )
	{
		CRET( capacity <= m_capacity );
		SetCapacity( capacity );
	}

	template< typename TStoredType >
	inline void PlainVector<TStoredType>::SetCapacity( const size_t capacity )
	{
		CRET( capacity == m_capacity );

		if( capacity == 0 )
		{
			Invalidate();
			return;
		}

		std::unique_ptr<Element[]> old_memory{ std::move( m_memory ) };

		m_capacity	= capacity;
		m_length	= std::min( m_length, m_capacity );
		m_memory	= new( std::nothrow ) Element[ m_capacity ];
		ENSURES( m_memory != nullptr );

		CRET( !old_memory || !m_length );
		Black::CopyMemory( m_memory, old_memory.get(), GetUsedBytes() );
	}

	template< typename TStoredType >
	inline void PlainVector<TStoredType>::ShrinkToFitLength()
	{
		CRET( m_length == m_capacity );
		SetCapacity( m_length );
	}

	template< typename TStoredType >
	inline const bool PlainVector<TStoredType>::IsEmpty() const
	{
		return m_length == 0;
	}

	template< typename TStoredType >
	inline const bool PlainVector<TStoredType>::IsInside( ConstIterator value ) const
	{
		return ( value >= GetHead() ) && ( value < GetTail() );
	}

	template< typename TStoredType >
	inline TStoredType& PlainVector<TStoredType>::GetElement( const size_t index )
	{
		EXPECTS_DEBUG( index < m_length );
		return m_memory[ index ];
	}

	template< typename TStoredType >
	inline const TStoredType& PlainVector<TStoredType>::GetElement( const size_t index ) const
	{
		EXPECTS_DEBUG( index < m_length );
		return m_memory[ index ];
	}

	template< typename TStoredType >
	template< typename... TArguments >
	inline void PlainVector<TStoredType>::ConstructElements( const size_t length, TArguments... arguments )
	{
		EXPECTS_DEBUG( length != 0 );

		const size_t old_length = m_length;
		SetLength( old_length + length );

		for( auto& place : PlainView<TStoredType>{ m_memory + old_length, length } )
		{
			new( &place ) TStoredType{ std::forward<TArguments>( arguments )... };
		}
	}

	template< typename TStoredType >
	inline void PlainVector<TStoredType>::CopyElements( const TStoredType* elements, const size_t elements_length )
	{
		EXPECTS_DEBUG( ( elements_length != 0 ) || !elements );

		SetLength( elements_length );
		CRET( elements_length == 0 );
		Black::CopyMemory( m_memory, elements, GetUsedBytes() );
	}
}
}
}
}
