#pragma once


namespace Black
{
inline namespace Core
{
inline namespace BitViews
{
namespace Internal
{
	template< typename TBitStorage >
	BitAdapter<TBitStorage>::BitAdapter( BitAdapter<TBitStorage>&& other )
	{
		Swap( other );
	}

	template< typename TBitStorage >
	BitAdapter<TBitStorage>::BitAdapter( TBitStorage* storage, const size_t bit_index )
		: m_storage{ storage }
		, m_bit_mask( FIRST_BIT_MASK << ValidateBitIndex( bit_index ) )
	{

	}

	template< typename TBitStorage >
	inline BitAdapter<TBitStorage>& BitAdapter<TBitStorage>::operator=( BitAdapter<TBitStorage>&& other )
	{
		Invalidate();
		Swap( other );
		return *this;
	}

	template< typename TBitStorage >
	inline BitAdapter<TBitStorage>& BitAdapter<TBitStorage>::operator=( const bool value )
	{
		static_assert( !std::is_const_v<TBitStorage>, "The constant value may not be modified." );
		EXPECTS_DEBUG( IsValid() );
		CRET( !IsValid(), *this );

		*m_storage = ( value )? ( *m_storage | m_bit_mask ) : ( *m_storage & ~m_bit_mask );
		return *this;
	}

	template< typename TBitStorage >
	inline void BitAdapter<TBitStorage>::Invalidate()
	{
		m_storage	= nullptr;
		m_bit_mask	= 0;
	}

	template< typename TBitStorage >
	inline const bool BitAdapter<TBitStorage>::IsValid() const
	{
		return m_storage != nullptr;
	}

	template< typename TBitStorage >
	inline BitAdapter<TBitStorage>::operator const bool () const
	{
		EXPECTS_DEBUG( IsValid() );
		CRET( !IsValid(), false );

		return ( *m_storage & m_bit_mask ) != 0;
	}

	template< typename TBitStorage >
	inline const bool BitAdapter<TBitStorage>::operator!() const
	{
		EXPECTS_DEBUG( IsValid() );
		CRET( !IsValid(), false );

		return ( *m_storage & m_bit_mask ) == 0;
	}

	template< typename TBitStorage >
	inline const bool BitAdapter<TBitStorage>::operator == ( const BitAdapter<TBitStorage>& other ) const
	{
		return ( m_storage == other.m_storage ) && ( m_bit_mask == other.m_bit_mask );
	}

	template< typename TBitStorage >
	inline const bool BitAdapter<TBitStorage>::operator != ( const BitAdapter<TBitStorage>& other ) const
	{
		return ( m_storage != other.m_storage ) || ( m_bit_mask != other.m_bit_mask );
	}

	template< typename TBitStorage >
	inline void BitAdapter<TBitStorage>::Swap( BitAdapter<TBitStorage>& other )
	{
		using std::swap;
		swap( m_storage, other.m_storage );
		swap( m_bit_mask, other.m_bit_mask );
	}

	template< typename TBitStorage >
	inline const size_t BitAdapter<TBitStorage>::ValidateBitIndex( const size_t bit_index )
	{
		EXPECTS_DEBUG( bit_index <= BitStorageTraits<TBitStorage>::MAX_BIT_INDEX );
		return bit_index;
	}
}
}
}
}
