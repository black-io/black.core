#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
	template< typename TValue >
	inline void Monad<TValue>::Clear()
	{
		m_value.reset();
	}

	template< typename TValue >
	inline void Monad<TValue>::Swap( Monad<TValue>& other )
	{
		std::swap( m_value, other.m_value );
	}

	template< typename TValue >
	[[ nodiscard ]]
	inline Monad<TValue> Monad<TValue>::ThisOr( const Monad<TValue>::Value& value ) const &
	{
		return Monad<Value>{ m_value.value_or( value ) };
	}

	template< typename TValue >
	[[ nodiscard ]]
	inline Monad<TValue> Monad<TValue>::ThisOr( Monad<TValue>::Value value ) &&
	{
		return Monad<Value>{ std::move( m_value ).value_or( std::move( value ) ) };
	}

	template< typename TValue >
	template< typename TFunction >
	[[ nodiscard ]]
	inline auto Monad<TValue>::Transform( TFunction&& transformer ) const & -> Monad<std::invoke_result_t<TFunction, Monad<TValue>::Value>>
	{
		using OtherMonad = Monad<std::invoke_result_t<TFunction, Monad<TValue>::Value>>;

		if( m_value.has_value() )
		{
			return OtherMonad{ transformer( m_value.value_or( Value{} ) ) };
		}

		return OtherMonad{};
	}

	template< typename TValue >
	template< typename TFunction >
	[[ nodiscard ]]
	inline auto Monad<TValue>::Transform( TFunction&& transformer ) && -> Monad<std::invoke_result_t<TFunction, Monad<TValue>::Value&&>>
	{
		using OtherMonad = Monad<std::invoke_result_t<TFunction, Monad<TValue>::Value>>;

		if( m_value.has_value() )
		{
			return OtherMonad{ transformer( std::move( m_value ).value_or( Value{} ) ) };
		}

		return OtherMonad{};
	}

	template< typename TValue >
	template< typename TFunction >
	[[ maybe_unused ]]
	inline auto Monad<TValue>::Feed( TFunction&& consumer ) const & -> Internal::MonadOrVoid<TFunction, Monad<TValue>::Value>
	{
		using Result = Internal::MonadOrVoid<TFunction, Monad<TValue>::Value>;

		if constexpr( std::is_void_v<Result> )
		{
			if( !m_value.has_value() )
			{
				return;
			}

			consumer( m_value.value_or( Value{} ) );
		}
		else
		{
			if( !m_value.has_value() )
			{
				return Result{};
			}

			return Result{ consumer( m_value.value_or( Value{} ) ) };
		}
	}

	template< typename TValue >
	template< typename TFunction >
	[[ maybe_unused ]]
	inline auto Monad<TValue>::Feed( TFunction&& consumer ) && -> Internal::MonadOrVoid<TFunction, Monad<TValue>::Value&&>
	{
		using Result = Internal::MonadOrVoid<TFunction, Monad<TValue>::Value>;

		if constexpr( std::is_void_v<Result> )
		{
			if( !m_value.has_value() )
			{
				return;
			}

			consumer( std::move( m_value ).value_or( Value{} ) );
		}
		else
		{
			if( !m_value.has_value() )
			{
				return Result{};
			}

			return Result{ consumer( std::move( m_value ).value_or( Value{} ) ) };
		}
	}
}
}
}
}
