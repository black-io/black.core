#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
namespace Internal
{
	template< typename TBitStorage >
	BitIterator<TBitStorage>::BitIterator( self_type&& other )
	{
		Swap( other );
	}

	template< typename TBitStorage >
	BitIterator<TBitStorage>::BitIterator( TBitStorage* head, const size_t bit_length )
		: BitIterator{ head, bit_length, 0 }
	{

	}

	template< typename TBitStorage >
	BitIterator<TBitStorage>::BitIterator( TBitStorage* head, const size_t bit_length, const size_t start_bit_index )
		: m_head{ head }
		, m_bit_length{ bit_length }
		, m_bit_index{ start_bit_index }
	{

	}

	template< typename TBitStorage >
	inline BitIterator<TBitStorage>& BitIterator<TBitStorage>::operator = ( self_type&& other )
	{
		Invalidate();
		Swap( other );
		return *this;
	}

	template< typename TBitStorage >
	inline BitIterator<TBitStorage>& BitIterator<TBitStorage>::operator = ( std::nullptr_t )
	{
		Invalidate();
		return *this;
	}

	template< typename TBitStorage >
	inline TBitStorage* const BitIterator<TBitStorage>::GetStreamHead() const
	{
		return m_head;
	}

	template< typename TBitStorage >
	inline const size_t BitIterator<TBitStorage>::GetStreamBitIndex() const
	{
		return m_bit_index;
	}

	template< typename TBitStorage >
	inline TBitStorage* const BitIterator<TBitStorage>::GetCurrentStorage() const
	{
		return m_head + m_bit_index.storage_index;
	}

	template< typename TBitStorage >
	inline const size_t BitIterator<TBitStorage>::GetCurrentBitIndex() const
	{
		return m_bit_index.bit_index;
	}

	template< typename TBitStorage >
	inline const bool BitIterator<TBitStorage>::IsValid() const
	{
		return ( m_head != nullptr ) && ( m_bit_index < m_bit_length );
	}

	template< typename TBitStorage >
	inline typename BitIterator<TBitStorage>::value_type BitIterator<TBitStorage>::operator * () const
	{
		EXPECTS_DEBUG( m_head != nullptr );
		EXPECTS_DEBUG( m_bit_index < m_bit_length );
		return { GetCurrentStorage(), GetCurrentBitIndex() };
	}

	template< typename TBitStorage >
	inline BitIterator<TBitStorage>& BitIterator<TBitStorage>::operator ++ ()
	{
		EXPECTS_DEBUG( m_bit_index < m_bit_length );
		++m_bit_index.value;
		return *this;
	}

	template< typename TBitStorage >
	inline BitIterator<TBitStorage> BitIterator<TBitStorage>::operator ++ ( int )
	{
		EXPECTS_DEBUG( m_bit_index < m_bit_length );
		return { m_head, m_bit_length, m_bit_index.value++ };
	}

	template< typename TBitStorage >
	inline BitIterator<TBitStorage>& BitIterator<TBitStorage>::operator += ( const difference_type offset )
	{
		BLACK_NON_RELEASE_CODE( const difference_type next_value = m_bit_index + offset );
		ENSURES_DEBUG( next_value >= 0 );
		ENSURES_DEBUG( next_value <= difference_type( m_bit_length ) );
		m_bit_index.value += offset;
		return *this;
	}

	template< typename TBitStorage >
	inline BitIterator<TBitStorage> BitIterator<TBitStorage>::operator + ( const difference_type offset )
	{
		BLACK_NON_RELEASE_CODE( const difference_type next_value = m_bit_index + offset );
		ENSURES_DEBUG( next_value >= 0 );
		ENSURES_DEBUG( next_value <= difference_type( m_bit_length ) );
		return { m_head, m_bit_length, m_bit_index.value + offset };
	}

	template< typename TBitStorage >
	inline BitIterator<TBitStorage>& BitIterator<TBitStorage>::operator -- ()
	{
		EXPECTS_DEBUG( m_bit_index > size_type{ 0 } );
		--m_bit_index.value;
		return *this;
	}

	template< typename TBitStorage >
	inline BitIterator<TBitStorage> BitIterator<TBitStorage>::operator -- ( int )
	{
		EXPECTS_DEBUG( m_bit_index > size_type{ 0 } );
		return { m_head, m_bit_length, m_bit_index.value-- };
	}

	template< typename TBitStorage >
	inline BitIterator<TBitStorage>& BitIterator<TBitStorage>::operator -= ( const difference_type offset )
	{
		BLACK_NON_RELEASE_CODE( const difference_type next_value = m_bit_index - offset );
		ENSURES_DEBUG( next_value >= 0 );
		ENSURES_DEBUG( next_value <= difference_type( m_bit_length ) );
		m_bit_index.value -= offset;
		return *this;
	}

	template< typename TBitStorage >
	inline BitIterator<TBitStorage> BitIterator<TBitStorage>::operator - ( const difference_type offset )
	{
		BLACK_NON_RELEASE_CODE( const difference_type next_value = m_bit_index - offset );
		ENSURES_DEBUG( next_value >= 0 );
		ENSURES_DEBUG( next_value <= difference_type( m_bit_length ) );
		return { m_head, m_bit_length, m_bit_index.value - offset };
	}

	template< typename TBitStorage >
	inline const bool BitIterator<TBitStorage>::operator == ( const self_type& other ) const
	{
		return ( m_head == other.m_head ) && ( m_bit_index == other.m_bit_index );
	}

	template< typename TBitStorage >
	inline const bool BitIterator<TBitStorage>::operator != ( const self_type& other ) const
	{
		return ( m_head != other.m_head ) || ( m_bit_index != other.m_bit_index );
	}

	template< typename TBitStorage >
	inline const bool BitIterator<TBitStorage>::operator > ( const self_type& other ) const
	{
		return ( m_head == other.m_head ) && ( m_bit_index > other.m_bit_index );
	}

	template< typename TBitStorage >
	inline const bool BitIterator<TBitStorage>::operator >= ( const self_type& other ) const
	{
		return ( m_head == other.m_head ) && ( m_bit_index >= other.m_bit_index );
	}

	template< typename TBitStorage >
	inline const bool BitIterator<TBitStorage>::operator < ( const self_type& other ) const
	{
		return ( m_head == other.m_head ) && ( m_bit_index < other.m_bit_index );
	}

	template< typename TBitStorage >
	inline const bool BitIterator<TBitStorage>::operator <= ( const self_type& other ) const
	{
		return ( m_head == other.m_head ) && ( m_bit_index <= other.m_bit_index );
	}

	template< typename TBitStorage >
	inline void BitIterator<TBitStorage>::Swap( self_type& other )
	{
		using std::swap;
		swap( m_head, other.m_head );
		swap( m_bit_length, other.m_bit_length );
		swap( m_bit_index, other.m_bit_index );
	}

	template< typename TBitStorage >
	inline void BitIterator<TBitStorage>::Invalidate()
	{
		m_head			= nullptr;
		m_bit_length	= 0;
		m_bit_index		= { 0 };
	}
}
}
}
}
