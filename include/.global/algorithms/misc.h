#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Algorithms
{
namespace Internal
{
	// Common template for method binding provider.
	template< typename TSignature >
	class MethodBindingProvider;

	// Terminal path to bind the regular methods.
	template< typename THost, typename TResult, typename... TArguments >
	class MethodBindingProvider<TResult (THost::*)( TArguments... )> final
	{
	public:
		// Perform the binding.
		template< TResult (THost::*METHOD)( TArguments... ) >
		static inline auto Bind( THost& host )
		{
			class Delegate final
			{
			public:
				inline Delegate() = delete;
				inline ~Delegate() = default;

				explicit inline Delegate( THost& host ) : m_host{ host } {};

			public:
				inline TResult operator ()( TArguments&&... arguments ) const { return (m_host.*METHOD)( std::forward<TArguments>( arguments )... ); };

			private:
				THost& m_host;
			};

			return Delegate{ host };
		};
	};

	// Terminal path to bind the methods with constant context.
	template< typename THost, typename TResult, typename... TArguments >
	class MethodBindingProvider<TResult (THost::*)( TArguments... ) const> final
	{
	public:
		// Perform the binding.
		template< TResult (THost::*METHOD)( TArguments... ) const >
		static inline auto Bind( const THost& host )
		{
			class Delegate final
			{
			public:
				inline Delegate() = delete;
				inline ~Delegate() = default;

				explicit inline Delegate( const THost& host ) : m_host{ host } {};

			public:
				inline TResult operator ()( TArguments&&... arguments ) const { return (m_host.*METHOD)( std::forward<TArguments>( arguments )... ); };

			private:
				const THost& m_host;
			};

			return Delegate{ host };
		};
	};

	// Terminal path to bind the methods with volatile context.
	template< typename THost, typename TResult, typename... TArguments >
	class MethodBindingProvider<TResult (THost::*)( TArguments... ) volatile> final
	{
	public:
		// Perform the binding.
		template< TResult (THost::*METHOD)( TArguments... ) volatile >
		static inline auto Bind( const THost& host )
		{
			class Delegate final
			{
			public:
				inline Delegate() = delete;
				inline ~Delegate() = default;

				explicit inline Delegate( volatile THost& host ) : m_host{ host } {};

			public:
				inline TResult operator ()( TArguments&&... arguments ) const { return (m_host.*METHOD)( std::forward<TArguments>( arguments )... ); };

			private:
				volatile THost& m_host;
			};

			return Delegate{ host };
		};
	};

	// Terminal path to bind the methods with constant and volatile context.
	template< typename THost, typename TResult, typename... TArguments >
	class MethodBindingProvider<TResult (THost::*)( TArguments... ) const volatile> final
	{
	public:
		// Perform the binding.
		template< TResult (THost::*METHOD)( TArguments... ) const volatile >
		static inline auto Bind( const volatile THost& host )
		{
			class Delegate final
			{
			public:
				inline Delegate() = delete;
				inline ~Delegate() = default;

				explicit inline Delegate( const volatile THost& host ) : m_host{ host } {};

			public:
				inline TResult operator ()( TArguments&&... arguments ) const { return (m_host.*METHOD)( std::forward<TArguments>( arguments )... ); };

			private:
				const volatile THost& m_host;
			};

			return Delegate{ host };
		};
	};
}


	/**
		@brief	Converts value of enumeration type to its underlying type value.
		@param	value			Te value to be converted.
		@tparam	TEnumeration	Type of enumeration.
		@return					Returns value of `TEnumeration` underlying type.
	*/
	template< typename TEnumeration >
	constexpr const auto GetEnumValue( const TEnumeration value )
	{
		static_assert( std::is_enum_v<TEnumeration>, "`TEnumeration` template argument should be an enumeration." );
		return static_cast<const std::underlying_type_t<TEnumeration>>( value );
	}

	/**
		@brief	Copying-swap assignation paradigm implementation.

		@tparam	TValue		The type of entities to assign.
		@tparam	TArguments	Construction arguments to assign operation.
		@param	left		The left operand of assign operation.
		@param	arguments	Number of arguments to construct the right operand.
		@return				The value returned is an `left` operand after the assignation.
	*/
	template< typename TValue, typename... TArguments >
	inline TValue& CopyAndSwap( TValue& left, TArguments&&... arguments )
	{
		using std::swap;

		TValue vicar{ std::forward<TArguments>( arguments )... };
		swap( left, vicar );

		return left;
	}

	/**
		@brief	Bind the pointer to method with host to be called.
		This function simplifies the process of using the algorithms when the method should be used inside.
		Typically the writer should create lambda-function with `this` in captures and some signature to call the method.
		With this function one can just pass the result into algorithm.
		@tparam	METHOD_POINTER	Pointer to arbitrary method.
		@tparam	THost			Type of host object to call the given method for.
		@param	host			Arbitrary host object for given method to be called.
		@return					The value returned is functional object, which can be used in standard algorithms.
	*/
	template< auto METHOD_POINTER, typename THost >
	inline auto BindMethod( THost& host )
	{
		return Internal::MethodBindingProvider<decltype( METHOD_POINTER )>::Bind<METHOD_POINTER>( host );
	}
}
}
}
}
