#pragma once


namespace Black
{
inline namespace Core
{
inline namespace BitViews
{
namespace Internal
{
	// Some traits for bits.
	struct BitTraits final
	{
		// Get the number of bits to store values up to given one.
		static constexpr const size_t GetSuitableBitsFor( const size_t value )
		{
			// The inner implementation is simple `ln2` function.
			return ( value > 1 )? ( 1 + GetSuitableBitsFor( value >> 1 ) ) : 0;
		}
	};

	// Bit storage traits.
	template< typename TBitStorage >
	struct BitStorageTraits final
	{
		static_assert( std::is_integral_v<TBitStorage> || std::is_enum_v<TBitStorage>, "`TBitStorage` should be of integer or enumeration type." );


		// Storage length in bytes.
		static constexpr const size_t	BYTE_LENGTH				= sizeof( TBitStorage );

		// Storage length in bits.
		static constexpr const size_t	BIT_LENGTH				= BYTE_LENGTH * 8;

		// Number of most significant bit in storage.
		static constexpr const size_t	MAX_BIT_INDEX			= BIT_LENGTH - 1;

		// Length of bit index field.
		static constexpr const size_t	BIT_INDEX_LENGTH		= BitTraits::GetSuitableBitsFor( BYTE_LENGTH ) + 3;

		// Length of storage index field.
		static constexpr const size_t	STORAGE_INDEX_LENGTH	= ( sizeof( size_t ) * 8 ) - BIT_INDEX_LENGTH;


		// Endianness-dependent index of bit.
		template< Black::PlatformEndianness, typename >
		union EndiannessBitIndex;

		// Little-endian implementation of bit index.
		template< typename TDummy >
		union EndiannessBitIndex<Black::PlatformEndianness::LittleEndian, TDummy> final
		{
			size_t		value;									// Index of bit inside of bit view stream.

			struct
			{
				size_t	bit_index		: BIT_INDEX_LENGTH;		// Index of bit inside of storage element.
				size_t	storage_index	: STORAGE_INDEX_LENGTH;	// Index of storage element which contain the bit.
			};


			inline const bool operator == ( const size_t right ) const	{ return value == right; };
			inline const bool operator != ( const size_t right ) const	{ return value != right; };
			inline const bool operator > ( const size_t right ) const	{ return value > right; };
			inline const bool operator >= ( const size_t right ) const	{ return value >= right; };
			inline const bool operator < ( const size_t right ) const	{ return value < right; };
			inline const bool operator <= ( const size_t right ) const	{ return value <= right; };


			inline operator size_t& ()				{ return value; };
			inline operator const size_t& () const	{ return value; };
		};

		// Big-endian implementation of bit index.
		template< typename TDummy >
		union EndiannessBitIndex<Black::PlatformEndianness::BigEndian, TDummy> final
		{
			size_t		value;									// Index of bit inside of bit view stream.

			struct
			{
				size_t	storage_index	: STORAGE_INDEX_LENGTH;	// Index of storage element which contain the bit.
				size_t	bit_index		: BIT_INDEX_LENGTH;		// Index of bit inside of storage element.
			};


			inline const bool operator == ( const size_t right ) const	{ return value == right; };
			inline const bool operator != ( const size_t right ) const	{ return value != right; };
			inline const bool operator > ( const size_t right ) const	{ return value > right; };
			inline const bool operator >= ( const size_t right ) const	{ return value >= right; };
			inline const bool operator < ( const size_t right ) const	{ return value < right; };
			inline const bool operator <= ( const size_t right ) const	{ return value <= right; };


			inline operator size_t& ()				{ return value; };
			inline operator const size_t& () const	{ return value; };
		};
	};

	// Regular index of bit.
	template< typename TBitStorage >
	using BitStorageIndex = typename BitStorageTraits<TBitStorage>::template EndiannessBitIndex<Black::BUILD_ENDIANNESS, void>;

	// Regular adapter for concrete stored bit.
	template< typename TBitStorage >
	class BitAdapter final
	{
	// Friendship interface.
	public:
		friend void swap( BitAdapter& left, BitAdapter& right )	{ left.Swap( right ); };

	// Construction and assignment.
	public:
		BitAdapter()							= default;
		BitAdapter( std::nullptr_t )			{};
		BitAdapter( const BitAdapter& other )	= default;
		BitAdapter( BitAdapter&& other );
		BitAdapter( TBitStorage* storage, const size_t bit_index );


		inline BitAdapter& operator = ( const BitAdapter& other ) = default;
		inline BitAdapter& operator = ( BitAdapter&& other );
		inline BitAdapter& operator = ( const bool value );

	// Public interface.
	public:
		// Invalidate the state of bit index.
		inline void Invalidate();

		// Whether the bit index is valid.
		inline const bool IsValid() const;


		inline operator const bool () const;
		inline const bool operator ! () const;


		inline const bool operator == ( const BitAdapter& other ) const;
		inline const bool operator != ( const BitAdapter& other ) const;

	// Private interface.
	private:
		// Mutable type of bit storage.
		using MutableBitStorage = std::remove_const_t<TBitStorage>;


		// Swap the state with other adapter.
		inline void Swap( BitAdapter& other );

		// Validate the given bit index via storage restrictions.
		static inline const size_t ValidateBitIndex( const size_t bit_index );

	// Private state.
	private:
		static constexpr const MutableBitStorage FIRST_BIT_MASK = 1;

		TBitStorage*		m_storage	= nullptr;	// The storage element containing the bit.
		MutableBitStorage	m_bit_mask	= 0;		// The bit mask for stored bit.
	};
}
}
}
}
