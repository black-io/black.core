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
		m_value.Clear();
	}

	template< typename TValue >
	inline void Monad<TValue>::Swap( Monad<TValue>& other )
	{
		m_value.Swap( other.m_value );
	}

	template< typename TValue >
	[[ nodiscard ]]
	inline Monad<TValue> Monad<TValue>::OrUse( const Monad<TValue>::Value& value ) const &
	{
		return Monad<Value>{ m_value.GetValue( value ) };
	}

	template< typename TValue >
	[[ nodiscard ]]
	inline Monad<TValue> Monad<TValue>::OrUse( Monad<TValue>::Value value ) &&
	{
		return Monad<Value>{ std::move( m_value ).GetValue( std::move( value ) ) };
	}

	template< typename TValue >
	template< typename TFunction >
	[[ nodiscard ]]
	inline auto Monad<TValue>::Transform( TFunction&& transformer ) const & -> Monad<std::invoke_result_t<TFunction, Monad<TValue>::Value>>
	{
		using OtherMonad = Monad<std::invoke_result_t<TFunction, Monad<TValue>::Value>>;

		if( m_value.HasValue() )
		{
			return OtherMonad{ transformer( m_value.GetValue() ) };
		}

		return OtherMonad{};
	}

	template< typename TValue >
	template< typename TFunction >
	[[ nodiscard ]]
	inline auto Monad<TValue>::Transform( TFunction&& transformer ) && -> Monad<std::invoke_result_t<TFunction, Monad<TValue>::Value&&>>
	{
		using OtherMonad = Monad<std::invoke_result_t<TFunction, Monad<TValue>::Value>>;

		if( m_value.HasValue() )
		{
			return OtherMonad{ transformer( std::move( m_value ).getValue() ) };
		}

		return OtherMonad{};
	}

	template< typename TValue >
	template< typename TFunction >
	[[ maybe_unused ]]
	inline auto Monad<TValue>::AndThen( TFunction&& consumer ) const & -> Internal::MonadOrVoid<TFunction, Monad<TValue>::Value>
	{
		using Result = Internal::MonadOrVoid<TFunction, Monad<TValue>::Value>;

		if constexpr( std::is_void_v<Result> )
		{
			if( m_value.IsEmpty() )
			{
				return;
			}

			consumer( m_value.GetValue() );
		}
		else
		{
			if( m_value.IsEmpty() )
			{
				return Result{};
			}

			return Result{ consumer( m_value.GetValue() ) };
		}
	}

	template< typename TValue >
	template< typename TFunction >
	[[ maybe_unused ]]
	inline auto Monad<TValue>::AndThen( TFunction&& consumer ) && -> Internal::MonadOrVoid<TFunction, Monad<TValue>::Value&&>
	{
		using Result = Internal::MonadOrVoid<TFunction, Monad<TValue>::Value>;

		if constexpr( std::is_void_v<Result> )
		{
			if( m_value.IsEmpty() )
			{
				return;
			}

			consumer( std::move( m_value ).GetValue() );
		}
		else
		{
			if( m_value.IsEmpty() )
			{
				return Result{};
			}

			return Result{ consumer( std::move( m_value ).GetValue() ) };
		}
	}
}
}
}
}
