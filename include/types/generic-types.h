#pragma once


namespace Black
{
	// Regular time type, in seconds.
	using Time			= float;

	// Regular time duration specification.
	using TimeDuration	= std::chrono::duration<Time>;

	// Regular 32-bit size specification.
	using size32_t		= uint32_t;

	// Regular 64-bit size specification. Always may be separated to high and low part, as well as be casted to `size_t`.
	union size64_t final
	{
		int64_t			value	= 0;	// Total size, 8 bytes length.

		struct
		{
			size32_t	lo;				// Lower 4-byte part of total size.
			int32_t		hi;				// Upper 4-byte part of total size.
		};

		size64_t() {};
		size64_t( const int64_t value ) : value{ value } {};
		size64_t( const size32_t lo_part, const int32_t hi_part )
		{
			lo = lo_part;
			hi = hi_part;
		}

		inline size_t& operator * ()				{ return reinterpret_cast<size_t&>( value ); };
		inline const size_t& operator * () const	{ return reinterpret_cast<const size_t&>( value ); };

		inline operator int64_t& ()					{ return value; };
		inline operator const int64_t () const		{ return value; };
	};

	// Implementation for hashing object for enumeration types, which may be used with `std` containers.
	class EnumHash final
	{
	public:
		// Hashing function. Uses `GetEnumValue` to produce the hash.
		template< typename TEnumeration >
		inline const size_t operator () ( const TEnumeration& value ) const
		{
			return static_cast<const size_t>( GetEnumValue( value ) );
		}
	};

	// Tagging type to mark the operation variant, that will ignore internal failures.
	struct IgnoreFailure final
	{

	};

	// Tagging object to mark the operation variant, that will ignore internal failures.
	constexpr IgnoreFailure IGNORE_FALURES = {};

	// Pointer to arbitrary global function.
	template< typename TResult, typename... TArguments >
	using GlobalFunctionPointer					= TResult (*)( TArguments... );

	// Pointer to arbitrary member-function.
	template< class THost, typename TResult, typename... TArguments >
	using MemberFunctionPointer					= TResult (THost::*)( TArguments... );

	// Pointer to arbitrary constant member-function.
	template< class THost, typename TResult, typename... TArguments >
	using MemberConstFunctionPointer			= TResult (THost::*)( TArguments... ) const;

	// Pointer to arbitrary volatile member-function.
	template< class THost, typename TResult, typename... TArguments >
	using MemberVolatileFunctionPointer			= TResult (THost::*)( TArguments... ) volatile;

	// Pointer to arbitrary volatile and constant member-function.
	template< class THost, typename TResult, typename... TArguments >
	using MemberConstVolatileFunctionPointer	= TResult (THost::*)( TArguments... ) const volatile;

	// Generic tag to prohibit copy-construction of derived types.
	// It would be better to use private inheritance.
	class NonCopyConstructible
	{
	public:
		NonCopyConstructible() = default;

	private:
		NonCopyConstructible( const NonCopyConstructible& ) = delete;
	};

	// Generic tag to prohibit copy-assignment of derived types.
	// It would be better to use private inheritance.
	class NonCopyAssignable
	{
	private:
		NonCopyAssignable& operator = ( const NonCopyAssignable& ) = delete;
	};

	// Generic tag to prohibit move-construction of derived types.
	// It would be better to use private inheritance.
	class NonMoveConstructible
	{
	public:
		NonMoveConstructible() = default;

	private:
		NonMoveConstructible( NonMoveConstructible&& ) = delete;
	};

	// Generic tag to prohibit move-assignment of derived types.
	// It would be better to use private inheritance.
	class NonMoveAssignable
	{
	private:
		NonMoveAssignable& operator = ( NonMoveAssignable&& ) = delete;
	};

	// Generic tag to prohibit copy-construction and copy-assignment of derived types.
	// It would be better to use private inheritance.
	class NonCopyable: private NonCopyConstructible, private NonCopyAssignable
	{

	};

	// Generic tag to prohibit move-construction and move-assignment of derived types.
	// It would be better to use private inheritance.
	class NonMovable: private NonMoveConstructible, private NonMoveAssignable
	{

	};

	// Generic tag to prohibit copy/move construction/assignment of derived types.
	// It would be better to use private inheritance.
	class NonTransferable: private NonCopyable, private NonMovable
	{

	};
}
