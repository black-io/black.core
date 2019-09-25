#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
namespace Internal
{
	// Helper class to detect the bit storage type for some enumeration with ordinal values.
	template< typename TEnumeration, typename = int >
	struct OrdinalEnumBitStorage;

	// Terminal branch. Detect the bit storage via `MAX_BITS` constant of enumeration.
	template< typename TEnumeration >
	struct OrdinalEnumBitStorage<TEnumeration, decltype( TEnumeration::MAX_BITS, 0 )>
	{
		static constexpr size_t	MAX_BITS = Black::GetEnumValue( TEnumeration::MAX_BITS );
		static_assert( MAX_BITS > 0, "The maximum number of bits should be above 0." );
		static_assert( MAX_BITS <= 64, "The maximum number of bits may not be below 64." );

		// Bit storage type for given enumeration.
		using Bits = typename Black::BitStorage<Black::GetAlignedSize( MAX_BITS, 8 )>::Bits;
	};

	// Terminal branch. Detect the bit storage via `MAX_VALUE` constant of enumeration.
	template< typename TEnumeration >
	struct OrdinalEnumBitStorage<TEnumeration, decltype( TEnumeration::MAX_VALUE, 0 )>
	{
		static constexpr size_t	MAX_VALUE	= Black::GetEnumValue( TEnumeration::MAX_VALUE );
		static_assert( MAX_VALUE > 0, "The maximum value should be above 0." );

		static constexpr bool	IS_UINT64	= MAX_VALUE > std::numeric_limits<uint32_t>::max();
		static constexpr bool	IS_UINT32	= MAX_VALUE > std::numeric_limits<uint16_t>::max();
		static constexpr bool	IS_UINT16	= MAX_VALUE > std::numeric_limits<uint8_t>::max();
		static constexpr size_t	MAX_BITS	= ( IS_UINT64 )? 64 : ( IS_UINT32 )? 32 : ( IS_UINT16 )? 16 : 8;

		// Bit storage type for given enumeration.
		using Bits = typename Black::BitStorage<MAX_BITS>::Bits;
	};

	// Some traits for enumeration types with ordinal values.
	template< typename TEnumeration >
	struct OrdinalEnumTraits
	{
		// Given enumeration type.
		using Enumeration	= TEnumeration;

		// Bit storage type for given enumeration.
		using BitStorage	= typename OrdinalEnumBitStorage<TEnumeration>::Bits;


		// Get the bit of given enumeration value.
		static constexpr BitStorage GetBit( const Enumeration flag )								{ return BitStorage( 1 ) << Black::GetEnumValue( flag ); };

		// Get the bit mask for given enumeration value.
		static constexpr BitStorage GetMask( const Enumeration flag )								{ return ~GetBit( flag ); };

		// Get the inverted state of bit storage.
		static constexpr BitStorage GetInverted( const BitStorage bits )							{ return static_cast<const BitStorage>( ~bits ); };

		// Set the bit of given flag in given bit storage.
		static constexpr BitStorage SetBit( const BitStorage bits, const Enumeration flag )			{ return bits | GetBit( flag ); };

		// Unset the bit of given flag in given bit storage.
		static constexpr BitStorage UnsetBit( const BitStorage bits, const Enumeration flag )		{ return bits & GetMask( flag ); };

		// Conjunction of bit storages.
		static constexpr BitStorage Conjunction( const BitStorage left, const BitStorage right )	{ return static_cast<const BitStorage>( left & right ); };

		// Disjunction of bit storages.
		static constexpr BitStorage Disjunction( const BitStorage left, const BitStorage right )	{ return static_cast<const BitStorage>( left | right ); };

		// Material non-implication of bit storages.
		static constexpr BitStorage Nonimplication( const BitStorage left, const BitStorage right )	{ return static_cast<const BitStorage>( left & ~right ); };
	};

	// Some traits for enumeration types with bit-mask values.
	template< typename TEnumeration >
	struct BitmaskEnumTraits
	{
		// Given enumeration type.
		using Enumeration	= TEnumeration;

		// Bit storage type for given enumeration.
		using BitStorage	= Black::UnderlyingType<TEnumeration>;


		// Get the bit of given enumeration value.
		static constexpr BitStorage GetBit( const TEnumeration flag )								{ return Black::GetEnumValue( flag ); };

		// Get the bit mask for given enumeration value.
		static constexpr BitStorage GetMask( const TEnumeration flag )								{ return ~GetBit( flag ); };

		// Get the inverted state of bit storage.
		static constexpr BitStorage GetInverted( const BitStorage bits )							{ return static_cast<const BitStorage>( ~bits ); };

		// Set the bit of given flag in given bit storage.
		static constexpr BitStorage SetBit( const BitStorage bits, const Enumeration flag )			{ return bits | GetBit( flag ); };

		// Unset the bit of given flag in given bit storage.
		static constexpr BitStorage UnsetBit( const BitStorage bits, const Enumeration flag )		{ return bits & GetMask( flag ); };

		// Conjunction of bit storages.
		static constexpr BitStorage Conjunction( const BitStorage left, const BitStorage right )	{ return static_cast<const BitStorage>( left & right ); };

		// Disjunction of bit storages.
		static constexpr BitStorage Disjunction( const BitStorage left, const BitStorage right )	{ return static_cast<const BitStorage>( left | right ); };

		// Material non-implication of bit storages.
		static constexpr BitStorage Nonimplication( const BitStorage left, const BitStorage right )	{ return static_cast<const BitStorage>( left & ~right ); };
	};

	// Regular traits for given enumeration type.
	template< typename TEnumeration >
	struct EnumTraits;

	// Terminal branch. Traits for enumeration type with ordinal values.
	template< typename TEnumeration >
	struct EnumTraits<Black::OrdinalEnumeration<TEnumeration>> final : OrdinalEnumTraits<TEnumeration> {};

	// Terminal branch. Traits for enumeration type with bit-mask values.
	template< typename TEnumeration >
	struct EnumTraits<Black::BitmaskEnumeration<TEnumeration>> final : BitmaskEnumTraits<TEnumeration> {};

	// Regular interface for bit flags storage.
	template< typename TEnumeration >
	class EnumFlagsStorage
	{
	// Inner types.
	public:
		using Traits		= EnumTraits<TEnumeration>;
		using Enumeration	= typename Traits::Enumeration;
		using Bits			= typename Traits::BitStorage;


		static constexpr Bits NONE_BITS	= Bits{};
		static constexpr Bits ALL_BITS	= ~NONE_BITS;

	// Public regular interface.
	public:
		// Clear the bit storage.
		inline void Clear()													{ m_bits = NONE_BITS; };

		// Inverse the state of bit storage.
		inline void Inverse()												{ m_bits = Traits::GetInverted( m_bits ); };

		// Set the bit for given flag.
		inline void SetFlag( const Enumeration flag )						{ m_bits |= Traits::GetBit( flag ); };

		// Unset the bit for given flag.
		inline void UnsetFlag( const Enumeration flag )						{ m_bits &= Traits::GetMask( flag ); };

		// Set or unset the bit for given flag.
		inline void SetFlag( const Enumeration flag, const bool is_set )	{ if( is_set ) SetFlag( flag ); else UnsetFlag( flag ); };


		// Whether the some bits are set in storage.
		inline const bool IsEmpty() const									{ return m_bits == NONE_BITS; };

		// Whether the storage contains the bit for given flag.
		inline const bool HasFlag( const Enumeration flag ) const			{ return ( m_bits & Traits::GetBit( flag ) ) == Traits::GetBit( flag ); };


		// Set the bits for given number of flags.
		inline void SetFlags( std::initializer_list<Enumeration> flags )
		{
			m_bits = std::accumulate( flags.begin(), flags.end(), m_bits, Traits::SetBit );
		}

		// Unset the bits for given number of flags.
		inline void UnsetFlags( std::initializer_list<Enumeration> flags )
		{
			m_bits = std::accumulate( flags.begin(), flags.end(), m_bits, Traits::UnsetBit );
		}

		// Whether the storage contains the bits for all of given flags.
		inline const bool HasAllFlags( std::initializer_list<Enumeration> flags ) const
		{
			return std::all_of( flags.begin(), flags.end(), [this]( const Enumeration flag ) { return HasFlag( flag ); } );
		}

		// Whether the storage contains the bits for some of given flags.
		inline const bool HasAnyFlag( std::initializer_list<Enumeration> flags ) const
		{
			return std::any_of( flags.begin(), flags.end(), [this]( const Enumeration flag ) { return HasFlag( flag ); } );
		}

	// Public template interface.
	public:
		// Set the bit for given flag.
		template< Enumeration FLAG >
		inline void SetFlag()												{ m_bits |= Traits::GetBit( FLAG ); };

		// Unset the bit for given flag.
		template< Enumeration FLAG >
		inline void UnsetFlag()												{ m_bits &= Traits::GetMask( FLAG ); };

		// Set or unset the bit for given flag.
		template< Enumeration FLAG >
		inline void SetFlag( const bool is_set )							{ if( is_set ) SetFlag<FLAG>(); else UnsetFlag<FLAG>(); };

		// Whether the storage contains the bit for given flag.
		template< Enumeration FLAG >
		inline const bool HasFlag() const									{ return ( m_bits & Traits::GetBit( FLAG ) ) == Traits::GetBit( FLAG ); };

	// Heirs interface.
	protected:
		// Set the number of bits.
		inline void SetBits( const Bits bits )								{ m_bits = m_bits | bits; };

		// Unset the number of bits.
		inline void UnsetBits( const Bits bits )							{ m_bits = m_bits & Traits::GetInverted( bits ); };

		// Whether the number of bits is set.
		inline const bool HasAnyBits( const Bits bits ) const				{ return ( m_bits & bits ) != NONE_BITS; };

		// Whether the all bits are set.
		inline const bool HasAllBits( const Bits bits ) const				{ return ( m_bits & bits ) == bits; };

	// Heirs state.
	protected:
		Bits	m_bits = NONE_BITS;	// The storage for bits.
	};

	// Policy to allow the bit storage projection through the type of bit-field structure.
	template< typename TEnumeration, typename TProjection >
	class EnumProjectionPolicy : public EnumFlagsStorage<TEnumeration>
	{
	public:
		static_assert( sizeof( TProjection ) <= sizeof( typename EnumFlagsStorage<TEnumeration>::Bits ), "`TProjection` should fits the bit storage." );
		static_assert( alignof( TProjection ) <= alignof( typename EnumFlagsStorage<TEnumeration>::Bits ), "`TProjection` have improper alignment." );

		inline TProjection* const operator -> ()				{ return GetProjection(); };
		inline const TProjection* const operator -> () const	{ return GetProjection(); };

		inline TProjection& operator * ()						{ return *GetProjection(); };
		inline const TProjection& operator * () const			{ return *GetProjection(); };

	private:
		inline TProjection* const GetProjection()				{ return reinterpret_cast<TProjection*>( &this->m_bits ); };
		inline const TProjection* const GetProjection() const	{ return reinterpret_cast<const TProjection*>( &this->m_bits ); };
	};

	// Terminal branch. No projection allowed.
	template< typename TEnumeration >
	class EnumProjectionPolicy<TEnumeration, void> : public EnumFlagsStorage<TEnumeration> {};

	// Adapter for bit storage and its projection. Common deduction branch guesses that enumeration consists of bit-mask values.
	template< typename TEnumeration, typename TProjection >
	class EnumFlagsAdaptor : public EnumProjectionPolicy<Black::BitmaskEnumeration<TEnumeration>, TProjection>
	{
	public:
		// Interface of bit storage for given enumeration.
		using Storage = EnumFlagsStorage<BitmaskEnumeration<TEnumeration>>;
	};

	// Terminal branch. The enumeration consists of ordinal values.
	template< typename TEnumeration, typename TProjection >
	class EnumFlagsAdaptor<Black::OrdinalEnumeration<TEnumeration>, TProjection> : public EnumProjectionPolicy<Black::OrdinalEnumeration<TEnumeration>, TProjection>
	{
	public:
		// Interface of bit storage for given enumeration.
		using Storage = EnumFlagsStorage<OrdinalEnumeration<TEnumeration>>;
	};

	// Terminal branch. The enumeration consists of bit-mask values.
	template< typename TEnumeration, typename TProjection >
	class EnumFlagsAdaptor<Black::BitmaskEnumeration<TEnumeration>, TProjection> : public EnumProjectionPolicy<Black::BitmaskEnumeration<TEnumeration>, TProjection>
	{
	public:
		// Interface of bit storage for given enumeration.
		using Storage = EnumFlagsStorage<BitmaskEnumeration<TEnumeration>>;
	};
}
}
}
}
