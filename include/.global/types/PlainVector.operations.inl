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
	inline const bool operator == ( const PlainVector<TValue>& left, const PlainVector<TValue>& right )
	{
		return left.GetMemory() == right.GetMemory();
	}

	template< typename TValue >
	inline const bool operator == ( const PlainVector<TValue>& left, const PlainView<TValue>& right )
	{
		return ( left.GetMemory() == right.GetMemory() ) && ( left.GetLength() == right.GetLength() );
	}

	template< typename TValue >
	inline const bool operator != ( const PlainVector<TValue>& left, const PlainVector<TValue>& right )
	{
		return left.GetMemory() != right.GetMemory();
	}

	template< typename TValue >
	inline const bool operator != ( const PlainVector<TValue>& left, const PlainView<TValue>& right )
	{
		return ( left.GetMemory() != right.GetMemory() ) || ( left.GetLength() != right.GetLength() );
	}
}
}
}
}
