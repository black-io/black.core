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
		@brief	Plain vector implementation.

		Plain vector implements the trivial dynamic array functionality to allow easy usage of dynamic size buffers.
		Plain vectors can store only values of trivial types. `std::vector` should be used for types with invariant.

		This template declare the STL-compatible interface to allow use it with standard algorithms.

		@tparam	TValue	Type of stored value.
	*/
	template< typename TValue >
	class PlainVector final : public Black::StandardDynamicArrayFacade<PlainVector<TValue>, Internal::BasicPlainVector<TValue>>
	{
	// Public aliases.
	public:
		using typename Internal::BasicPlainVector<TValue>::Iterator;
		using typename Internal::BasicPlainVector<TValue>::ConstIterator;
		using typename Internal::BasicPlainVector<TValue>::ConstValuePointer;


		using Internal::BasicPlainVector<TValue>::GetValueAt;
		using Internal::BasicPlainVector<TValue>::IsEmpty;
		using Internal::BasicPlainVector<TValue>::GetMemory;
		using Internal::BasicPlainVector<TValue>::GetCapacity;
		using Internal::BasicPlainVector<TValue>::GetLength;

	// Friendship interface.
	public:
		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline Iterator begin( PlainVector& range )					{ return range.GetBegin(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline Iterator end( PlainVector& range )					{ return range.GetEnd(); };

		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline ConstIterator begin( const PlainVector& range )		{ return range.GetBegin(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline ConstIterator end( const PlainVector& range )			{ return range.GetEnd(); };

		// 'Swap' interface.
		friend inline void swap( PlainVector& left, PlainVector& right )	{ left.Swap( right ); };

	// Public lifetime management.
	public:
		using Black::StandardDynamicArrayFacade<PlainVector<TValue>, Internal::BasicPlainVector<TValue>>::StandardDynamicArrayFacade;


		PlainVector( ConstValuePointer elements, const size_t length ) : PlainVector{ elements, elements + length } {};
		PlainVector( std::initializer_list<TValue> elements ) : PlainVector{ elements.begin(), elements.end() } {};

		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		explicit PlainVector( PlainView<TOtherValue> elements ) : PlainVector( elements.GetBegin(), elements.GetEnd() ) {};

		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		explicit PlainVector( PlainView<const TOtherValue> elements ) : PlainVector( elements.GetBegin(), elements.GetEnd() ) {};

		template< typename TOtherValue, size_t ARRAY_LENGTH, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		explicit PlainVector( TOtherValue elements[ ARRAY_LENGTH ] ) : PlainVector( elements, ARRAY_LENGTH ) {};

		template< typename TOtherValue, size_t ARRAY_LENGTH, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		explicit PlainVector( const std::array<TOtherValue, ARRAY_LENGTH>& elements ) : PlainVector( elements.data(), ARRAY_LENGTH ) {};

		template< typename TOtherValue, typename TAllocator, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		explicit PlainVector( const std::vector<TOtherValue, TAllocator>& elements ) : PlainVector( elements.data(), elements.size() ) {};


		inline PlainVector& operator = ( std::initializer_list<TValue> elements )					{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainVector& operator = ( PlainView<TOtherValue> elements )							{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainVector& operator = ( PlainView<const TOtherValue> elements )					{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherValue, size_t ARRAY_LENGTH, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainVector& operator = ( TOtherValue elements[ ARRAY_LENGTH ] )						{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherValue, size_t ARRAY_LENGTH, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainVector& operator = ( const std::array<TOtherValue, ARRAY_LENGTH>& elements )	{ return CopyAndSwap( *this, elements ); };

		template< typename TOtherValue, typename TAllocator, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainVector& operator = ( const std::vector<TOtherValue, TAllocator>& elements )		{ return CopyAndSwap( *this, elements ); };

	// Public interface.
	public:
		inline TValue& operator [] ( const size_t index )				{ return GetValueAt( index ); };
		inline const TValue& operator [] ( const size_t index ) const	{ return GetValueAt( index ); };


		inline operator PlainView<TValue> ()				{ return { GetMemory(), GetLength() }; };
		inline operator PlainView<const TValue> () const	{ return { GetMemory(), GetLength() }; };


		inline explicit operator const bool () const	{ return !IsEmpty(); };
		inline const bool operator ! () const			{ return IsEmpty(); };
	};
}
}
}
}
