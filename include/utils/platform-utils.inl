#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Utils
{
	template< typename TValue >
	inline void CopyMemory( TValue& dest_ref, const TValue& source_ref )
	{
		Black::CopyMemory( &dest_ref, &source_ref, sizeof( TValue ) );
	}

	template< typename TValue >
	inline void FillMemory( TValue& target_ref, const int32_t pattern )
	{
		Black::FillMemory( &target_ref, pattern, sizeof( TValue ) );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline void FillMemory( TValue (&target_array)[ ARRAY_LENGTH ], const int32_t pattern )
	{
		Black::FillMemory( target_array, pattern, sizeof( TValue ) * ARRAY_LENGTH );
	}

	template< typename TValue >
	inline void ZeroMemory( TValue& target_ref )
	{
		Black::FillMemory( &target_ref, 0, sizeof( TValue ) );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline void ZeroMemory( TValue (&target_array)[ ARRAY_LENGTH ] )
	{
		Black::FillMemory( target_array, 0, sizeof( TValue ) * ARRAY_LENGTH );
	}

	template< typename TValue >
	inline void SecuredZeroMemory( TValue& target_ref )
	{
		Black::SecuredZeroMemory( &target_ref, sizeof( TValue ) );
	}

	template< typename TValue, size_t ARRAY_LENGTH >
	inline void SecuredZeroMemory( TValue (&target_array)[ ARRAY_LENGTH ] )
	{
		Black::SecuredZeroMemory( target_array, sizeof( TValue ) * ARRAY_LENGTH );
	}

	template< typename TValue >
	inline const bool IsMemoryEqual( const TValue& left_ref, const TValue& right_ref )
	{
		return Black::IsMemoryEqual( &left_ref, right_ref, sizeof( TValue ) );
	}
}


inline namespace TextUtils
{
	inline Black::StringView WriteArguments( Black::PlainView<char> target_buffer, const Black::StringView format, ... )
	{
		va_list arguments;
		va_start( arguments, format );

		Black::StringView result = Black::WriteArguments( target_buffer, format, arguments );

		va_end( arguments );
		return result;
	}

	inline const size_t ReadArguments( const Black::StringView source_buffer, const Black::StringView format, ... )
	{
		va_list arguments;
		va_start( arguments, format );

		const size_t result = Black::ReadArguments( source_buffer, format, arguments );

		va_end( arguments );
		return result;
	}
}
}
}
