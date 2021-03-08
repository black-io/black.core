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
	using HighPrecisionTime = float;

	// Regular time duration specification.
	using TimeDuration = std::chrono::duration<Time>;

	// High precision time duration specification.
	using HighPrecisionTimeDuration = std::chrono::duration<HighPrecisionTime>;

	// Regular 32-bit hash value.
	enum class Hash32 : uint32_t;

	// Regular 64-bit hash value.
	enum class Hash64 : uint64_t;


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
		inline NonCopyConstructible()							= default;
		inline NonCopyConstructible( NonCopyConstructible&& )	= default;


		inline NonCopyConstructible& operator = ( const NonCopyConstructible& )	= default;
		inline NonCopyConstructible& operator = ( NonCopyConstructible&& )		= default;

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
		inline NonCopyAssignable()								= default;
		inline NonCopyAssignable( const NonCopyAssignable& )	= default;
		inline NonCopyAssignable( NonCopyAssignable&& )			= default;


		inline NonCopyAssignable& operator = ( NonCopyAssignable&& ) = default;

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
		inline NonMoveConstructible()								= default;
		inline NonMoveConstructible( const NonMoveConstructible& )	= default;


		inline NonMoveConstructible& operator = ( const NonMoveConstructible& )	= default;
		inline NonMoveConstructible& operator = ( NonMoveConstructible&& )		= default;

	// Denied operations.
	private:
		inline NonMoveConstructible( NonMoveConstructible&& ) = delete;
	};

	// Generic tag to prohibit move-assignment of derived types.
	// It would be better to use private inheritance.
	class NonMoveAssignable
	{
	// Allowed operations.
	public:
		inline NonMoveAssignable()								= default;
		inline NonMoveAssignable( const NonMoveAssignable& )	= default;
		inline NonMoveAssignable( NonMoveAssignable&& )			= default;


		inline NonMoveAssignable& operator = ( const NonMoveAssignable& ) = default;

	// Denied operations.
	private:
		inline NonMoveAssignable& operator = ( NonMoveAssignable&& ) = delete;
	};

	// Generic tag to prohibit copy-construction and copy-assignment of derived types.
	// It would be better to use private inheritance.
	class NonCopyable
	{
	// Allowed operations.
	public:
		inline NonCopyable()				= default;
		inline NonCopyable( NonCopyable&& )	= default;


		inline NonCopyable& operator = ( NonCopyable&& ) = default;

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


		inline NonMovable& operator = ( const NonMovable& ) = default;

	// Denied operations.
	private:
		inline NonMovable( NonMovable&& ) = delete;


		inline NonMovable& operator = ( NonMovable&& ) = delete;
	};

	// Generic tag to prohibit copy/move construction/assignment of derived types.
	// It would be better to use private inheritance.
	class NonTransferable
	{
	// Allowed operations.
	public:
		NonTransferable() = default;

	// Denied operations.
	private:
		NonTransferable( const NonTransferable& )	= delete;
		NonTransferable( NonTransferable&& )		= delete;


		NonTransferable& operator = ( const NonTransferable& )	= delete;
		NonTransferable& operator = ( NonTransferable&& )		= delete;
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

		Size64() = default;
		Size64( const int64_t value ) : value{ value } {};
		Size64( const uint32_t lo_part, const int32_t hi_part )
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
	public:
		ScopeLeaveHandler()								= delete;
		ScopeLeaveHandler( const ScopeLeaveHandler& )	= default;
		ScopeLeaveHandler( ScopeLeaveHandler&& )		= default;
		explicit ScopeLeaveHandler( TFunction function ) : m_function{ std::move( function ) } {};
		~ScopeLeaveHandler() { CRET( m_is_canceled ); m_function(); };


		ScopeLeaveHandler& operator = ( ScopeLeaveHandler&& )		= default;
		ScopeLeaveHandler& operator = ( const ScopeLeaveHandler& )	= default;


		// Cancel the handling.
		inline void Cancel() { m_is_canceled = true; };

	private:
		TFunction	m_function;
		bool		m_is_canceled	= false;
	};
}
}
}
}
