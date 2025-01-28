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
	inline void Hypothetical<TValue>::Clear()
	{
		m_value.Clear();
	}

	template< typename TValue >
	inline void Hypothetical<TValue>::Swap( Hypothetical<TValue>& other )
	{
		m_value.Swap( other.m_value );
	}

	template< typename TValue >
	[[ nodiscard ]]
	inline Hypothetical<TValue> Hypothetical<TValue>::OrUse( const Hypothetical<TValue>::Value& value ) const &
	{
		return Hypothetical<Value>{ m_value.GetValue( value ) };
	}

	template< typename TValue >
	[[ nodiscard ]]
	inline Hypothetical<TValue> Hypothetical<TValue>::OrUse( Hypothetical<TValue>::Value value ) &&
	{
		return Hypothetical<Value>{ std::move( m_value ).GetValue( std::move( value ) ) };
	}

	template< typename TValue >
	template< typename TFunction >
	[[ nodiscard ]]
	inline auto Hypothetical<TValue>::Transform( TFunction&& transformer ) const & -> Hypothetical<std::invoke_result_t<TFunction, Hypothetical<TValue>::Value>>
	{
		using OtherHypothetical = Hypothetical<std::invoke_result_t<TFunction, Hypothetical<TValue>::Value>>;

		if( m_value.HasValue() )
		{
			return OtherHypothetical{ transformer( m_value.GetValue() ) };
		}

		return OtherHypothetical{};
	}

	template< typename TValue >
	template< typename TFunction >
	[[ nodiscard ]]
	inline auto Hypothetical<TValue>::Transform( TFunction&& transformer ) && -> Hypothetical<std::invoke_result_t<TFunction, Hypothetical<TValue>::Value&&>>
	{
		using OtherHypothetical = Hypothetical<std::invoke_result_t<TFunction, Hypothetical<TValue>::Value>>;

		if( m_value.HasValue() )
		{
			return OtherHypothetical{ transformer( std::move( m_value ).getValue() ) };
		}

		return OtherHypothetical{};
	}

	template< typename TValue >
	template< typename TFunction >
	[[ maybe_unused ]]
	inline auto Hypothetical<TValue>::AndThen( TFunction&& consumer ) const & -> Internal::HypotheticalOrVoid<TFunction, Hypothetical<TValue>::Value>
	{
		using Result = Internal::HypotheticalOrVoid<TFunction, Hypothetical<TValue>::Value>;

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
	inline auto Hypothetical<TValue>::AndThen( TFunction&& consumer ) && -> Internal::HypotheticalOrVoid<TFunction, Hypothetical<TValue>::Value&&>
	{
		using Result = Internal::HypotheticalOrVoid<TFunction, Hypothetical<TValue>::Value>;

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
