#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
	/**
		@brief	Storage for bit flags based on corresponded enumeration type.
		The enumerations with bit-mask values may be passed to `TEnumeration` as is of via `Black::BitmaskEnumeration` template instantiation.
		The enumerations with ordinal values should be passed via `Black::OrdinalEnumeration` instantiation.

		The `TProjection` template parameter may be used to represent the bits as structured information.
		If the parameter is set, the `operator ->` and `operator *` may be used to access the bits like the value of `TProjection` type.
		It may be useful in case the enumeration represents the bits of bit-field structure.

		Each flag may be set/unset/checked using various functions and operators.
		`operator +`/`operator +=` can be used to set some flag, like `SetFlag` functions.
		`operator -`/`operator -=` can be used to unset some flag, lake `UnsetFlag` functions.
		`operator &` can be used to check that the bit flags are masked by other bit flags or some bit is set.
		`operator []` can be used for easy check that the some flag is set.
		`Bits` inner type is an alias to underlying type of flags enumeration type.
		The instance of `EnumFlags` can be implicitly converted into `Bits` type for future usage.
		`explicit operator bool` and `operator !` can be used to check that some flags are set or the instance is empty.

		@tparam	TEnumeration	Enumeration type, which is supposed to use as bit flags.
		@tparam	TProjection		The possible type to project the bit flags into some kind of bit-field structure.
	*/
	template< typename TEnumeration, typename TProjection = void >
	class EnumFlags final : public Internal::EnumFlagsAdaptor<TEnumeration, TProjection>
	{
	public:
		// SERVICE USE ONLY. The type of bit storage interface.
		using Storage		= typename Internal::EnumFlagsAdaptor<TEnumeration, TProjection>::Storage;

		// SERVICE USE ONLY. The type of enumeration traits.
		using Traits		= typename Storage::Traits;

		// The type of given enumeration.
		using Enumeration	= typename Traits::Enumeration;

		// The type of raw bit storage.
		using Bits			= typename Traits::BitStorage;

	// Construction and assignment.
	public:
		EnumFlags()												= default;
		EnumFlags( const EnumFlags& )							= default;
		EnumFlags( EnumFlags&& )								= default;
		explicit EnumFlags( const Bits flags )					{ Storage::m_bits = flags; };
		EnumFlags( std::initializer_list<Enumeration> flags )	{ Storage::SetFlags( flags ); };


		inline EnumFlags& operator = ( const EnumFlags& )							= default;
		inline EnumFlags& operator = ( EnumFlags&& )								= default;
		inline EnumFlags& operator = ( const Enumeration flag )						{ Storage::m_bits = Traits::GetBit( flag ); return *this; };
		inline EnumFlags& operator = ( std::initializer_list<Enumeration> flags )	{ return Black::CopyAndSwap( *this, flags ); };

	// Public interface.
	public:
		// Get the inverted state of flags.
		inline EnumFlags GetInverted() const								{ return EnumFlags{ Traits::GetInverted( Storage::m_bits ) }; };


		inline const bool operator [] ( const Enumeration flag ) const		{ return Storage::HasFlag( flag ); };

		inline operator const Bits& () const								{ return Storage::m_bits; };

		inline explicit operator const bool () const						{ return Storage::IsEmpty(); };
		inline const bool operator ! () const								{ return !Storage::IsEmpty(); };

		inline const bool operator == ( const Enumeration flag ) const		{ return Storage::m_bits == Traits::GetBit( flag ); };
		inline const bool operator == ( const EnumFlags& other ) const		{ return Storage::m_bits == other.m_bits; };
		inline const bool operator != ( const Enumeration flag ) const		{ return Storage::m_bits != Traits::GetBit( flag ); };
		inline const bool operator != ( const EnumFlags& other ) const		{ return Storage::m_bits != other.m_bits; };

		inline const bool operator && ( const Enumeration flag ) const		{ return Storage::HasFlag( flag ); };
		inline const bool operator && ( const EnumFlags& other ) const		{ return Storage::HasAllBits( other.m_bits ); };

		inline EnumFlags operator & ( const EnumFlags& other ) const		{ return EnumFlags{ Traits::Conjunction( Storage::m_bits, other.m_bits ) }; };

		inline EnumFlags operator + ( const EnumFlags& other ) const		{ return EnumFlags{ Traits::Disjunction( Storage::m_bits, other.m_bits ) }; };
		inline EnumFlags operator - ( const EnumFlags& other ) const		{ return EnumFlags{ Traits::Nonimplication( Storage::m_bits, other.m_bits ) }; };
		inline EnumFlags operator + ( const Enumeration flag ) const		{ return EnumFlags{ Traits::SetBit( Storage::m_bits, flag ) }; };
		inline EnumFlags operator - ( const Enumeration flag ) const		{ return EnumFlags{ Traits::UnsetBit( Storage::m_bits, flag ) }; };

		inline EnumFlags& operator += ( const EnumFlags& other )			{ Storage::SetBit( other.m_bits ); return *this; };
		inline EnumFlags& operator -= ( const EnumFlags& other )			{ Storage::UnsetBit( other.m_bits ); return *this; };
		inline EnumFlags& operator += ( const Enumeration flag )			{ Storage::SetFlag( flag ); return *this; };
		inline EnumFlags& operator -= ( const Enumeration flag )			{ Storage::UnsetFlag( flag ); return *this; };
	};
}
}
}
}
