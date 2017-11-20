#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	/**
		@brief	Storage for bit flags based on corresponded enumeration type.
		Some restrictions are imposed for enumeration type in order to be used as template parameter for `EnumFlags`.
		* Each element of enumeration type have to be a bit mask, but not the number of bit.

		Each flag may be set/unset/checked using various functions and operators.
		`operator +`/`operator +=` can be used to set some flag, like `SetFlag` functions.
		`operator -`/`operator -=` can be used to unset some flag, lake `UnsetFlag` functions.
		`operator &` can be used to check that the bit flags are masked by other bit flags or some bit is set.
		`operator []` can be used for easy check that the some flag is set.
		`Bits` inner type is an alias to underlying type of flags enumeration type.
		The instance of `EnumFlags` can be implicitly converted into `Bits` type for future usage.
		`explicit operator bool` and `operator !` can be used to check that some flags are set or the instance is empty.

		@tparam	TEnumeration	Enumeration type, which is supposed to use as bit flags.
	*/
	template< typename TEnumeration >
	class EnumFlags final
	{
	// Inner entities.
	public:
		static_assert( std::is_enum<TFlagsEnum>::value, "`TEnumeration` have to be enumeration type." );


		// The underlying type of enumeration.
		using Bits = Black::UnderlyingType<TEnumeration>;


		// 'None bits set' state specification.
		static constexpr Bits NONE_BITS	= Bits( 0 );

		// 'All bits set' state specification.
		static constexpr Bits ALL_BITS	= ~NONE_BITS;

	// Construction interface.
	public:
		EnumFlags()						= default;
		EnumFlags( const EnumFlags& )	= default;
		EnumFlags( EnumFlags&& )		= default;
		explicit EnumFlags( const Bits flags ) : m_flags{ flags } {};
		EnumFlags( std::initializer_list<TEnumeration> flags )
		{
			std::for_each( flags.begin(), flags.end(), [this]( const TEnumeration flag ) { SetFlag( flag ); } );
		}


		inline EnumFlags& operator = ( const EnumFlags& )							= default;
		inline EnumFlags& operator = ( EnumFlags&& )								= default;
		inline EnumFlags& operator = ( const TEnumeration flag )					{ m_flags = GetBits( flag ); return *this; };
		inline EnumFlags& operator = ( std::initializer_list<TEnumeration> flags )	{ return Black::CopyAndSwap( *this, flags ); };

	// Public interface.
	public:
		// Clear the flags.
		inline void Clear()													{ m_flags = 0; };

		// Inverse the flags.
		inline void Inverse()												{ m_flags = ~m_flags; };

		// Get the state of inversed flags.
		inline EnumFlags GetInverted() const								{ return EnumFlags<TEnumeration>{ ~m_flags }; };

		// Set the flag.
		inline void SetFlag( const TEnumeration flag )						{ m_flags |= GetBits( flag ); };

		// Unset the flag.
		inline void UnsetFlag( const TEnumeration flag )					{ m_flags &= ~GetBits( flag ); };

		// Set the flag.
		template< TEnumeration FLAG >
		inline void SetFlag()												{ m_flags |= GetBits( FLAG ); };

		// Unset the flag.
		template< TEnumeration FLAG >
		inline void UnsetFlag()												{ m_flags &= ~GetBits( FLAG ); };


		// Check that all flags are unset.
		inline const bool IsEmpty() const									{ return m_flags != 0; };

		// Check that the flag is set.
		inline const bool IsFlagSet( const TEnumeration flag ) const		{ return ( m_flags & GetBits( flag ) ) != 0; };

		// Check that the flag is set.
		template< TEnumeration FLAG >
		inline const bool IsFlagSet() const									{ return ( m_flags & GetBits( FLAG ) ) != 0; };


		inline const bool operator [] ( const TEnumeration flag ) const		{ return IsFlagSet( flag ); };

		inline operator const Bits& () const								{ return m_flags; };

		inline explicit operator const bool () const						{ return m_flags != 0; };
		inline const bool operator ! () const								{ return m_flags == 0; };

		inline const bool operator == ( const TEnumeration flag ) const		{ return m_flags == GetBits( flag ); };
		inline const bool operator == ( const EnumFlags& other ) const		{ return m_flags == other.m_flags; };
		inline const bool operator != ( const TEnumeration flag ) const		{ return m_flags != GetBits( flag ); };
		inline const bool operator != ( const EnumFlags& other ) const		{ return m_flags != other.m_flags; };

		inline const bool operator && ( const TEnumeration flag ) const		{ return IsFlagSet( flag ); };
		inline const bool operator && ( const EnumFlags& other ) const		{ return ( m_flags & other.m_flags ) == other.m_flags; };

		inline EnumFlags operator + ( const EnumFlags& other ) const		{ return EnumFlags{ m_flags | other.m_flags }; };
		inline EnumFlags operator - ( const EnumFlags& other ) const		{ return EnumFlags{ m_flags & ~other.m_flags }; };
		inline EnumFlags operator + ( const TEnumeration flag ) const		{ return EnumFlags{ m_flags | GetBits( flag ) }; };
		inline EnumFlags operator - ( const TEnumeration flag ) const		{ return EnumFlags{ m_flags & ~GetBits( flag ) }; };

		inline EnumFlags& operator += ( const EnumFlags& other ) const		{ m_flags = m_flags | other.m_flags; return *this; };
		inline EnumFlags& operator -= ( const EnumFlags& other ) const		{ m_flags = m_flags & ~other.m_flags; return *this; };
		inline EnumFlags& operator += ( const TEnumeration flag ) const		{ m_flags = m_flags | GetBits( flag ); return *this; };
		inline EnumFlags& operator -= ( const TEnumeration flag ) const		{ m_flags = m_flags & ~GetBits( flag ); return *this; };

	private:
		// Transform the enumeration value into bits.
		static constexpr Bits GetBits( const TEnumeration flag )			{ return Black::GetEnumValue( flag ); };

	private:
		Bits m_flags;	// Bits for enumeration flags.
	};
}
}
}
