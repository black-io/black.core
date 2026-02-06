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
	inline PlainView<TValue> PlainView<TValue>::TruncateSuffix( const size_t length ) const
	{
		return { GetBegin(), GetEnd() - std::min( length, GetLength() ) };
	}

	template< typename TValue >
	inline PlainView<TValue> PlainView<TValue>::TruncatePrefix( const size_t length ) const
	{
		return { GetBegin() + std::min( length, GetLength() ), GetEnd() };
	}

	template< typename TValue >
	inline PlainView<TValue> PlainView<TValue>::GetSubview( const size_t begin_index, const size_t length ) const
	{
		const size_t subview_offset	= std::min( begin_index, GetLength() );
		const size_t subview_length	= std::min( length, GetLength() );
		const size_t subview_end	= std::min( subview_offset + subview_length, GetLength() );

		return { GetBegin() + subview_offset, GetBegin() + subview_end };
	}
}
}
}
}
