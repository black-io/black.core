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
		@tparam	TPointer	Type of stored pointer.
	*/
	template< typename TPointer >
	class NotNull final
	{
	// Service inner types and predicates.
	public:
		// Whether the type could be casted to `TPointer`.
		template< typename TOther >
		static inline constexpr bool IS_CONVERTIBLE_FROM		= std::is_convertible_v<TOther, TPointer>;

		// Whether the `TPointer` could be casted to type.
		template< typename TOther >
		static inline constexpr bool IS_CONVERTIBLE_TO			= std::is_convertible_v<TPointer, TOther>;

	// Construction and assignment.
	public:
		static_assert( std::is_assignable_v<TPointer&, std::nullptr_t>, "`TPointer` should be able to accept `nullptr` value." );
		static_assert( !std::is_same_v<TPointer, std::nullptr_t>, "`TPointer` should not be the type of `nullptr`." );

		NotNull()					= delete;
		NotNull( const NotNull& )	= default;
		NotNull( NotNull&& )		= default;
		NotNull( std::nullptr_t )	= delete;
		constexpr NotNull( TPointer pointer ) : m_pointer{ std::move( pointer ) } { EXPECTS( m_pointer != nullptr ); };

		template< typename TOther, typename = std::enable_if_t<IS_CONVERTIBLE_FROM<TOther>> >
		constexpr NotNull( TOther&& other ) : m_pointer( std::forward<TOther>( other ) ) { EXPECTS( m_pointer != nullptr ); };

		template< typename TOther, typename = std::enable_if_t<IS_CONVERTIBLE_FROM<TOther>> >
		constexpr NotNull( const NotNull<TOther>& other ) : m_pointer( other.m_pointer ) { EXPECTS( m_pointer != nullptr ); };


		inline NotNull& operator = ( const NotNull& )					= default;
		inline NotNull& operator = ( NotNull&& )						= default;
		inline NotNull& operator = ( TPointer pointer )					{ return Black::CopyAndSwap( *this, pointer ); };
		inline NotNull& operator = ( std::nullptr_t )					= delete;

		template< typename TOther, typename = std::enable_if_t<IS_CONVERTIBLE_FROM<TOther>> >
		inline NotNull& operator = ( TOther other )						{ return Black::CopyAndSwap( *this, other ); };

		template< typename TOther, typename = std::enable_if_t<IS_CONVERTIBLE_FROM<TOther>> >
		inline NotNull& operator = ( const NotNull<TOther>& other )		{ return Black::CopyAndSwap( *this, other ); };

	// Public interface.
	public:
		constexpr TPointer Get() const	{ ENSURES_DEBUG( m_pointer != nullptr ); return m_pointer; };

		template< typename TOther >
		constexpr auto Get() const -> decltype( static_cast<TOther>( std::declval<TPointer>() ) )	{ return static_cast<TOther>( Get() ); };


		constexpr operator TPointer () const			{ return Get(); };
		constexpr TPointer operator -> () const			{ return Get(); };
		constexpr decltype( auto ) operator * () const	{ return *Get(); };


		NotNull& operator += ( ptrdiff_t )	= delete;
		NotNull& operator ++ ()				= delete;
		NotNull operator ++ ( int )			= delete;
		NotNull& operator -= ( ptrdiff_t )	= delete;
		NotNull& operator -- ()				= delete;
		NotNull operator -- ( int )			= delete;
		void operator [] ( size_t )			= delete;

	// Private state.
	private:
		TPointer	m_pointer;	// Stored pointer.
	};
}
}
}
