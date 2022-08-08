#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
	/**
		@brief	Plain view implementation.

		Views are containers of unowned memory. Views only refers to contiguous block of memory where the types values are stored.
		Typically, the view represents the part of some buffer.
		View can refer to memory of mutable or constant values.

		This template declare the STL-compatible interface to allow use it with standard algorithms.

		@tparam	TBalue	Type of values in view.
	*/
	template< typename TValue >
	class PlainView : public Black::StandardArrayFacade<PlainView<TValue>, Internal::BasicPlainView<TValue>, false>
	{
	// Public aliases.
	public:
		using typename Internal::BasicPlainView<TValue>::Value;
		using typename Internal::BasicPlainView<TValue>::Iterator;


		using Internal::BasicPlainView<TValue>::GetValueAt;
		using Internal::BasicPlainView<TValue>::IsEmpty;

	// Friendship interface.
	public:
		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline Iterator begin( const PlainView& range )			{ return range.GetBegin(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline Iterator end( const PlainView& range )			{ return range.GetEnd(); };

		// 'Swap' interface.
		friend inline void swap( PlainView& left, PlainView& right )	{ left.Swap( right ); };

	// Public lifetime management.
	public:
		using Black::StandardArrayFacade<PlainView<TValue>, Internal::BasicPlainView<TValue>, false>::StandardArrayFacade;


		PlainView( Iterator begin, Iterator end ) : PlainView{ begin, std::distance( begin, end ) } {};


		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		PlainView( const PlainView<TOtherValue>& other ) : PlainView( other.GetBegin(), other.GetEnd() ) {};

		template< size_t ARRAY_LENGTH >
		PlainView( Value (&elements)[ ARRAY_LENGTH ] ) : PlainView{ elements, ARRAY_LENGTH } {};

		template< size_t ARRAY_LENGTH >
		PlainView( std::array<Value, ARRAY_LENGTH>& elements ) : PlainView{ elements.data(), ARRAY_LENGTH } {};

		template< typename TAllocator >
		PlainView( std::vector<Value, TAllocator>& elements ) : PlainView{ elements.data(), elements.size() } {};


		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainView& operator = ( const PlainView<TOtherValue>& other )		{ return CopyAndSwap( *this, other ); };

		template< size_t ARRAY_LENGTH >
		inline PlainView& operator = ( Value elements[ ARRAY_LENGTH ] )				{ return CopyAndSwap( *this, elements ); };

		template< size_t ARRAY_LENGTH >
		inline PlainView& operator = ( std::array<Value, ARRAY_LENGTH>& elements )	{ return CopyAndSwap( *this, elements ); };

		template< typename TAllocator >
		inline PlainView& operator = ( std::vector<Value, TAllocator>& elements )	{ return CopyAndSwap( *this, elements ); };

	// Public interface.
	public:
		inline TValue& operator [] ( const size_t index ) const	{ return GetValueAt( index ); };


		inline explicit operator const bool () const			{ return !IsEmpty(); };
		inline const bool operator ! () const					{ return IsEmpty(); };
	};
}
}
}
}
