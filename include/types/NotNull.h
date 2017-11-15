#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	/**
		@brief	Core C++ Guideline `not_null` type.
		Assigning of `nullptr` to instance of this type will cause termination of execution.
		@tparam	TStoredType	Type of stored pointer.
	*/
	template< typename TStoredType >
	class NotNull
	{
	public:
		NotNull( const NotNull& )	= default;
		NotNull( NotNull&& )		= default;
		NotNull( TStoredType* new_pointer ) : m_stored_pointer{ new_pointer } { EXPECTS( m_stored_pointer != nullptr ); };

		template< typename TDerivedType, typename = EnableIf<IS_CONVERTIBLE<TDerivedType*, TStoredType*>> >
		NotNull( const NotNull<TDerivedType>& other ) : m_stored_pointer( other.m_stored_pointer ) {};


		inline NotNull& operator = ( const NotNull& other )		= default;
		inline NotNull& operator = ( NotNull&& other )			= default;
		inline NotNull& operator = ( TStoredType* new_pointer )	{ EXPECTS( new_pointer != nullptr ); m_stored_pointer = new_pointer; return *this; };

		template< typename TDerivedType, typename = EnableIf<IS_CONVERTIBLE<TDerivedType*, TStoredType*>> >
		inline NotNull& operator = ( const NotNull<TDerivedType>& other )	{ m_stored_pointer = other.m_stored_pointer; return *this; };


		inline TStoredType* get() const	{ BLACK_ASSUME( m_stored_pointer != nullptr ); return m_stored_pointer; };

		template< typename TCastingType >
		inline EnableIf<IS_CONVERTIBLE<TDerivedType*, TStoredType*>, TCastingType*> get() const	{ return static_cast<TCastingType*>( get() ); };


		inline TStoredType* operator -> () const											{ return get(); };
		inline Conditional<IS_VOID<TStoredType>, uint8_t, TStoredType>& operator * () const	{ return *get(); };
		inline operator TStoredType* () const												{ return get(); };

	private:
		NotNull()					= delete;
		NotNull( std::nullptr_t )	= delete;
		NotNull( int )				= delete;

		NotNull& operator = ( std::nullptr_t )	= delete;
		NotNull& operator = ( int )				= delete;

	private:
		TStoredType*	m_stored_pointer;
	};
}
}
}
