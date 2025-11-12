#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
	// Regular time type, in seconds.
	using Time = float;

	// Type of time with high precision, in seconds.
	using HighPrecisionTime = double;

	// Regular time duration specification.
	using TimeDuration = std::chrono::duration<Time>;

	// High precision time duration specification.
	using HighPrecisionTimeDuration = std::chrono::duration<HighPrecisionTime>;

	// Regular 32-bit hash value.
	enum class Hash32 : uint32_t;

	// Regular 64-bit hash value.
	enum class Hash64 : uint64_t;


	// TODO: Get rid of this template.
	// Trivial common selection between Debug and Non-debug implementations.
	template< typename RelaseImplementation, typename DebugImplementation >
	using BuildModeDependent = std::conditional_t<Black::BUILD_CONFIGURATION == Black::BuildMode::Release, RelaseImplementation, DebugImplementation>;


	// Tagging type to mark the operation variant, that will ignore internal failures.
	enum class IgnoreFailure;

	// Tagging object to mark the operation variant, that will ignore internal failures.
	inline constexpr IgnoreFailure IGNORE_FALURE = {};

	// Tagging type to mark the operation variant, that will use in-place construction.
	enum class ConstructInplace;

	// Tagging object to mark the operation variant, that will use in-place construction.
	inline constexpr ConstructInplace CONSTRUCT_INPLACE = {};


	// Regular bit storage for requested number of bits. The number of bits should be 8, 16, 32 or 64 only.
	template< size_t MAX_BITS >
	struct BitStorage;

	// Terminal branch for 8-bit storage.
	template<>
	struct BitStorage<8>
	{
		using Bits = uint8_t;
	};

	// Terminal branch for 16-bit storage.
	template<>
	struct BitStorage<16>
	{
		using Bits = uint16_t;
	};

	// Terminal branch for 32-bit storage.
	template<>
	struct BitStorage<32>
	{
		using Bits = uint32_t;
	};

	// Terminal branch for 64-bit storage.
	template<>
	struct BitStorage<64>
	{
		using Bits = uint64_t;
	};


	// Generic tag to prohibit copy-construction of derived types.
	// It would be better to use private inheritance.
	class NonCopyConstructible
	{
	// Allowed operations.
	public:
		inline NonCopyConstructible()									= default;
		inline NonCopyConstructible( NonCopyConstructible&& ) noexcept	= default;
		inline ~NonCopyConstructible() noexcept							= default;


		inline NonCopyConstructible& operator = ( const NonCopyConstructible& )		= default;
		inline NonCopyConstructible& operator = ( NonCopyConstructible&& ) noexcept	= default;

	// Denied operations.
	private:
		inline NonCopyConstructible( const NonCopyConstructible& ) = delete;
	};

	// Generic tag to prohibit copy-assignment of derived types.
	// It would be better to use private inheritance.
	class NonCopyAssignable
	{
	// Allowed operations.
	public:
		inline NonCopyAssignable()									= default;
		inline NonCopyAssignable( const NonCopyAssignable& )		= default;
		inline NonCopyAssignable( NonCopyAssignable&& ) noexcept	= default;
		inline ~NonCopyAssignable() noexcept						= default;


		inline NonCopyAssignable& operator = ( NonCopyAssignable&& ) noexcept	= default;

	// Denied operations.
	private:
		inline NonCopyAssignable& operator = ( const NonCopyAssignable& ) = delete;
	};

	// Generic tag to prohibit move-construction of derived types.
	// It would be better to use private inheritance.
	class NonMoveConstructible
	{
	// Allowed operations.
	public:
		inline NonMoveConstructible()										= default;
		inline NonMoveConstructible( const NonMoveConstructible& ) noexcept	= default;
		inline ~NonMoveConstructible() noexcept								= default;


		inline NonMoveConstructible& operator = ( const NonMoveConstructible& )		= default;
		inline NonMoveConstructible& operator = ( NonMoveConstructible&& ) noexcept	= default;

	// Denied operations.
	private:
		inline NonMoveConstructible( NonMoveConstructible&& ) noexcept = delete;
	};

	// Generic tag to prohibit move-assignment of derived types.
	// It would be better to use private inheritance.
	class NonMoveAssignable
	{
	// Allowed operations.
	public:
		inline NonMoveAssignable()									= default;
		inline NonMoveAssignable( const NonMoveAssignable& )		= default;
		inline NonMoveAssignable( NonMoveAssignable&& ) noexcept	= default;
		inline ~NonMoveAssignable() noexcept						= default;


		inline NonMoveAssignable& operator = ( const NonMoveAssignable& ) = default;

	// Denied operations.
	private:
		inline NonMoveAssignable& operator = ( NonMoveAssignable&& ) noexcept = delete;
	};

	// Generic tag to prohibit copy-construction and copy-assignment of derived types.
	// It would be better to use private inheritance.
	class NonCopyable
	{
	// Allowed operations.
	public:
		inline NonCopyable()							= default;
		inline NonCopyable( NonCopyable&& ) noexcept	= default;
		inline ~NonCopyable() noexcept					= default;


		inline NonCopyable& operator = ( NonCopyable&& ) noexcept = default;

	// Denied operations.
	private:
		inline NonCopyable( const NonCopyable& ) = delete;


		inline NonCopyable& operator = ( const NonCopyable& ) = delete;
	};

	// Generic tag to prohibit move-construction and move-assignment of derived types.
	// It would be better to use private inheritance.
	class NonMovable
	{
	// Allowed operations.
	public:
		inline NonMovable()						= default;
		inline NonMovable( const NonMovable& )	= default;
		inline ~NonMovable() noexcept			= default;


		inline NonMovable& operator = ( const NonMovable& ) = default;

	// Denied operations.
	private:
		inline NonMovable( NonMovable&& ) noexcept = delete;


		inline NonMovable& operator = ( NonMovable&& ) noexcept = delete;
	};

	// Generic tag to prohibit copy/move construction/assignment of derived types.
	// It would be better to use private inheritance.
	class NonTransferable
	{
	// Allowed operations.
	public:
		inline NonTransferable()			= default;
		inline ~NonTransferable() noexcept	= default;

	// Denied operations.
	private:
		inline NonTransferable( const NonTransferable& )		= delete;
		inline NonTransferable( NonTransferable&& ) noexcept	= delete;


		inline NonTransferable& operator = ( const NonTransferable& )		= delete;
		inline NonTransferable& operator = ( NonTransferable&& ) noexcept	= delete;
	};


	// Implementation for hashing object for enumeration types, which may be used with `std` containers.
	class EnumHash final
	{
	public:
		// Hashing function. Uses `GetEnumValue` to produce the hash.
		template< typename TEnumeration >
		inline const size_t operator () ( TEnumeration&& value ) const
		{
			return static_cast<const size_t>( GetEnumValue( std::forward<TEnumeration>( value ) ) );
		}
	};


	// Regular 64-bit size specification. Always may be separated to high and low part, as well as be casted to `size_t`.
	union Size64 final
	{
		int64_t			value	= 0;	// Total size, 8 bytes length.

		struct
		{
			uint32_t	lo;				// Lower 4-byte part of total size.
			int32_t		hi;				// Upper 4-byte part of total size.
		};

		inline Size64()													= default;
		inline Size64( const int64_t value )							: value{ value } {};
		inline Size64( const uint32_t lo_part, const int32_t hi_part )
		{
			lo = lo_part;
			hi = hi_part;
		}

		inline size_t& operator * ()				{ return reinterpret_cast<size_t&>( value ); };
		inline const size_t& operator * () const	{ return reinterpret_cast<const size_t&>( value ); };

		inline operator int64_t& ()					{ return value; };
		inline operator const int64_t () const		{ return value; };
	};


	// Scope exit handler may be used to invoke some function just before leaving current scope.
	template< typename TFunction >
	class ScopeLeaveHandler final
	{
	// Construction and assignment.
	public:
		inline ScopeLeaveHandler()									= delete;
		inline ScopeLeaveHandler( const ScopeLeaveHandler& )		= default;
		inline ScopeLeaveHandler( ScopeLeaveHandler&& ) noexcept	= default;

		explicit inline ScopeLeaveHandler( TFunction function )		: m_function{ std::move( function ) } {};

		inline ~ScopeLeaveHandler()
		{
			CRET( m_is_canceled );
			m_function();
		}


		ScopeLeaveHandler& operator = ( ScopeLeaveHandler&& )		= default;
		ScopeLeaveHandler& operator = ( const ScopeLeaveHandler& )	= default;

	// Public interface.
	public:
		// Cancel the handling.
		inline void Cancel() { m_is_canceled = true; };

	// Private state.
	private:
		TFunction	m_function;					// The function to be executed.
		bool		m_is_canceled	= false;	// Whether the function should not be executed.
	};

	// Locale holder accepts the new locale through the constructor, uses it on construction and returns the previous locale only on destruction.
	class SystemLocaleHolder final : private NonTransferable
	{
	// Construction and destruction.
	public:
		explicit inline SystemLocaleHolder( const std::string& new_locale )	: SystemLocaleHolder{ new_locale.data() } {};
		explicit inline SystemLocaleHolder( const char* new_locale )		: m_old_locale{ std::setlocale( LC_ALL, new_locale ) } {};
		inline ~SystemLocaleHolder()
		{
			CRET( m_old_locale == nullptr );
			std::setlocale( LC_ALL, m_old_locale );
		}

	// Private state.
	private:
		const char* m_old_locale; // The previous locale that should be returned.
	};
}
}
}
}
