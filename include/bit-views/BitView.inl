#pragma once


namespace Black
{
inline namespace Core
{
inline namespace BitViews
{
	template< typename TBitStorage >
	BitView<TBitStorage>::BitView( BitView&& other )
	{
		Swap( other );
	}

	template< typename TBitStorage >
	BitView<TBitStorage>::BitView( Element* head, const size_t bit_length )
		: m_head{ head }
		, m_bit_length{ bit_length }
	{
		EXPECTS_DEBUG( ( bit_length == 0 ) || head );
	}

	template< typename TBitStorage >
	inline BitView<TBitStorage>& BitView<TBitStorage>::operator = ( BitView<TBitStorage>&& other )
	{
		Invalidate();
		Swap( other );
		return *this;
	}

	template< typename TBitStorage >
	inline void BitView<TBitStorage>::Invalidate()
	{
		m_head			= nullptr;
		m_bit_length	= { 0 };
	}

	template< typename TBitStorage >
	inline void BitView<TBitStorage>::Swap( BitView<TBitStorage>& other )
	{
		Black::Swap( m_head, other.m_head );
		Black::Swap( m_bit_length, other.m_bit_length );
	}

	template< typename TBitStorage >
	inline const bool BitView<TBitStorage>::IsValid() const
	{
		return m_head != nullptr;
	}

	template< typename TBitStorage >
	inline const bool BitView<TBitStorage>::IsEmpty() const
	{
		return m_bit_length == size_t{};
	}

	template< typename TBitStorage >
	inline const bool BitView<TBitStorage>::IsInside( Iterator value ) const
	{
		const ptrdiff_t value_distance = value.GetCurrentStorage() - m_head;
		CRET( value_distance < 0, false );

		const size_t distance_bits = value_distance * Internal::BitStorageTraits<TBitStorage>::BIT_LENGTH;
		CRET( distance_bits >= m_bit_length, false );

		return ( distance_bits + value.GetCurrentBitIndex() ) < m_bit_length;
	}

	template< typename TBitStorage >
	inline typename BitView<TBitStorage>::BitAdapter BitView<TBitStorage>::GetElement( const size_t index ) const
	{
		EXPECTS_DEBUG( index < m_bit_length );

		BitIndex bit_index{ index };
		return { m_head + bit_index.storage_index, bit_index.bit_index };
	}

	template< typename TBitStorage >
	inline typename BitView<TBitStorage>::BitAdapter BitView<TBitStorage>::GetFront() const
	{
		EXPECTS_DEBUG( !IsEmpty() );
		return *GetHead();
	}

	template< typename TBitStorage >
	inline typename BitView<TBitStorage>::BitAdapter BitView<TBitStorage>::GetBack() const
	{
		EXPECTS_DEBUG( !IsEmpty() );
		return *std::prev( GetTail() );
	}

	template< typename TBitStorage >
	inline typename BitView<TBitStorage>::Iterator BitView<TBitStorage>::GetHead() const
	{
		return { m_head, m_bit_length.value, 0 };
	}

	template< typename TBitStorage >
	inline typename BitView<TBitStorage>::Iterator BitView<TBitStorage>::GetTail() const
	{
		return { m_head, m_bit_length.value, m_bit_length.value };
	}

	template< typename TBitStorage >
	inline typename BitView<TBitStorage>::Element* BitView<TBitStorage>::GetData() const
	{
		return m_head;
	}

	template< typename TBitStorage >
	inline const size_t BitView<TBitStorage>::GetLength() const
	{
		return m_bit_length;
	}

	template< typename TBitStorage >
	inline const size_t BitView<TBitStorage>::GetStorageLength() const
	{
		return m_bit_length.storage_index + ( m_bit_length.bit_index != 0 );
	}

	template< typename TBitStorage >
	inline const size_t BitView<TBitStorage>::GetUsedBytes() const
	{
		return GetStorageLength() * ELEMENT_SIZE;
	}

	template< typename TBitStorage >
	inline const bool BitView<TBitStorage>::operator == ( const BitView& other ) const
	{
		return ( m_head == other.m_head ) && ( m_bit_length == other.m_bit_length );
	}

	template< typename TBitStorage >
	inline const bool BitView<TBitStorage>::operator != ( const BitView& other ) const
	{
		return ( m_head != other.m_head ) || ( m_bit_length != other.m_bit_length );
	}
}
}
}
