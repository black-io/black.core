#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	template< typename >
	class BigEndian;

	// Universal little-endian integral value.
	template< typename TValue >
	class LitleEndian final
	{
		static_assert( Black::IS_INTEGER<TValue>, "Type of stored value should be an integer." );
		static_assert( sizeof( TValue ) >= 2, "Size of stored value may not be less than 2 bytes." );

	// Construction interface.
	public:
		LitleEndian()									= default;
		LitleEndian( const LitleEndian& )				= default;
		LitleEndian( LitleEndian&& )					= default;
		LitleEndian( const BigEndian<TValue>& other );
		LitleEndian( BigEndian<TValue>&& other );
		LitleEndian( const TValue value );
		LitleEndian( const TValue value, const PlatformEndianness endianness );

		inline LitleEndian& operator = ( const LitleEndian& )				= default;
		inline LitleEndian& operator = ( LitleEndian&& )					= default;
		inline LitleEndian& operator = ( const TValue value )				{ return CopyAndSwap( *this, value, Black::BUILD_ENDIANNESS ); };
		inline LitleEndian& operator = ( const BigEndian<TValue>& other );
		inline LitleEndian& operator = ( BigEndian<TValue>&& other );

	// Public interface.
	public:
		// Get the value in native endianness for current platform.
		inline TValue GetNativeValue() const;


		inline operator const TValue () const							{ return m_value.value; };

		inline uint8_t& operator [] ( const size_t index )				{ EXPECTS_DEBUG( index < sizeof( TValue ) ); return m_value.bytes[ index ]; };
		inline const uint8_t operator [] ( const size_t index ) const	{ EXPECTS_DEBUG( index < sizeof( TValue ) ); return m_value.bytes[ index ]; };

	private:
		// Store the native value in little-endian style.
		inline void StoreNativeValue( const TValue value );

	private:
		union BytePack
		{
			TValue	value = 0;
			uint8_t	bytes[ sizeof( TValue ) ];
		} m_value;
	};

	// Universal big-endian integral value.
	template< typename TValue >
	class BigEndian final
	{
		static_assert( Black::IS_INTEGER<TValue>, "Type of stored value should be an integer." );
		static_assert( sizeof( TValue ) >= 2, "Size of stored value may not be less than 2 bytes." );

	// Construction interface.
	public:
		BigEndian()										= default;
		BigEndian( const BigEndian& )					= default;
		BigEndian( BigEndian&& )						= default;
		BigEndian( const LitleEndian<TValue>& other );
		BigEndian( LitleEndian<TValue>&& other );
		BigEndian( const TValue value );
		BigEndian( const TValue value, const PlatformEndianness endianness );

		inline BigEndian& operator = ( const BigEndian& )					= default;
		inline BigEndian& operator = ( BigEndian&& )						= default;
		inline BigEndian& operator = ( const TValue value )					{ return CopyAndSwap( *this, value, Black::BUILD_ENDIANNESS ); };
		inline BigEndian& operator = ( const LitleEndian<TValue>& other );
		inline BigEndian& operator = ( LitleEndian<TValue>&& other );

	// Public interface.
	public:
		// Get the value in native endianness for current platform.
		inline TValue GetNativeValue() const;


		inline operator const TValue () const							{ return m_value.value; };

		inline uint8_t& operator [] ( const size_t index )				{ EXPECTS_DEBUG( index < sizeof( TValue ) ); return m_value.bytes[ index ]; };
		inline const uint8_t operator [] ( const size_t index ) const	{ EXPECTS_DEBUG( index < sizeof( TValue ) ); return m_value.bytes[ index ]; };

	private:
		// Store the native value in little-endian style.
		inline void StoreNativeValue( const TValue value );

	private:
		union BytePack
		{
			TValue	value = 0;
			uint8_t	bytes[ sizeof( TValue ) ];
		} m_value;
	};
}
}
}
