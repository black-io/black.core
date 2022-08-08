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
	inline const bool operator == ( const PlainView<TValue>& left, const PlainView<TValue>& right )
	{
		return ( left.GetMemory() == right.GetMemory() ) && ( left.GetLength() == right.GetLength() );
	}

	template< typename TValue >
	inline const bool operator != ( const PlainView<TValue>& left, const PlainView<TValue>& right )
	{
		return ( left.GetMemory() != right.GetMemory() ) || ( left.GetLength() != right.GetLength() );
	}
}
}
}
}
