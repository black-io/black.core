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
	PlainVector<TValue>::PlainVector( const PlainVector& other )
	{
		CRET( other.IsEmpty() );
		SetLength( other.GetLength() );
		Black::CopyMemory( m_memory, other.m_memory, GetUsedBytes() );
	}

	template< typename TValue >
	PlainVector<TValue>::PlainVector( PlainVector&& other )
	{
		Swap( other );
	}

	template< typename TValue >
	PlainVector<TValue>::PlainVector( const size_t length )
	{
		SetLength( length );
	}

	template< typename TValue >
	PlainVector<TValue>::PlainVector( const size_t length, ConstValueReference prototype )
	{
		SetCapacity( length );
		ConstructValues( length, prototype );
	}

	template< typename TValue >
	PlainVector<TValue>::PlainVector( ConstIterator begin, ConstIterator end )
	{
		EXPECTS_DEBUG( ( !begin && !end ) || ( end >= begin ) );
		CopyValues( begin, end - begin );
	}

	template< typename TValue >
	PlainVector<TValue>::~PlainVector()
	{
		Invalidate();
	}

	template< typename TValue >
	inline PlainVector<TValue>& PlainVector<TValue>::operator=( const PlainVector<TValue>& other )
	{
		CRET( &other == this, *this );

		Invalidate();
		SetLength( other.GetLength() );
		Black::CopyMemory( m_memory, other.m_memory, GetUsedBytes() );

		return *this;
	}

	template< typename TValue >
	inline PlainVector<TValue>& PlainVector<TValue>::operator=( PlainVector<TValue>&& other )
	{
		CRET( &other == this, *this );

		Invalidate();
		Swap( other );

		return *this;
	}

	template< typename TValue >
	inline void PlainVector<TValue>::Invalidate()
	{
		Black::SafeVectorDelete( m_memory );
		m_length	= 0;
		m_capacity	= 0;
	}

	template< typename TValue >
	inline void PlainVector<TValue>::SetLength( const size_t length )
	{
		CRET( length == m_length );

		if( length > m_capacity )
		{
			ReserveCapacity( length );
		}

		m_length = length;
	}

	template< typename TValue >
	inline void PlainVector<TValue>::ReserveCapacity( const size_t capacity )
	{
		CRET( capacity <= m_capacity );
		SetCapacity( capacity );
	}

	template< typename TValue >
	inline void PlainVector<TValue>::SetCapacity( const size_t capacity )
	{
		CRET( capacity == m_capacity );

		if( capacity == 0 )
		{
			Invalidate();
			return;
		}

		std::unique_ptr<Value[]> old_memory{ std::move( m_memory ) };

		m_capacity	= capacity;
		m_length	= std::min( m_length, m_capacity );
		m_memory	= new( std::nothrow ) Value[ m_capacity ];
		ENSURES( m_memory != nullptr );

		CRET( !old_memory || !m_length );
		Black::CopyMemory( m_memory, old_memory.get(), GetUsedBytes() );
	}

	template< typename TValue >
	inline void PlainVector<TValue>::ShrinkToFitLength()
	{
		CRET( m_length == m_capacity );
		SetCapacity( m_length );
	}

	template< typename TValue >
	inline void PlainVector<TValue>::FillWith( ConstValueReference value )
	{
		for( TValue* cursor = m_memory; cursor < ( m_memory + m_length ); ++cursor )
		{
			new( cursor ) TValue{ value };
		}
	}

	template< typename TValue >
	inline void PlainVector<TValue>::Swap( PlainVector<TValue>& other )
	{
		using std::swap;
		swap( m_memory, other.m_memory );
		swap( m_capacity, other.m_capacity );
		swap( m_length, other.m_length );
	}

	template< typename TValue >
	inline const bool PlainVector<TValue>::IsEmpty() const
	{
		return m_length == 0;
	}

	template< typename TValue >
	inline const bool PlainVector<TValue>::IsInside( ConstIterator value ) const
	{
		return ( value >= GetBegin() ) && ( value < GetEnd() );
	}

	template< typename TValue >
	inline TValue& PlainVector<TValue>::GetValueAt( const size_t index )
	{
		EXPECTS_DEBUG( index < m_length );
		return m_memory[ index ];
	}

	template< typename TValue >
	inline const TValue& PlainVector<TValue>::GetValueAt( const size_t index ) const
	{
		EXPECTS_DEBUG( index < m_length );
		return m_memory[ index ];
	}

	template< typename TValue >
	template< typename... TArguments >
	inline void PlainVector<TValue>::ConstructValues( const size_t length, const TArguments&... arguments )
	{
		EXPECTS_DEBUG( length != 0 );

		const size_t old_length = m_length;
		SetLength( old_length + length );

		for( TValue* cursor = m_memory + old_length; cursor < ( m_memory + m_length ); ++cursor )
		{
			new( cursor ) TValue{ arguments... };
		}
	}

	template< typename TValue >
	inline void PlainVector<TValue>::CopyValues( ConstValuePointer elements, const size_t elements_length )
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
}
