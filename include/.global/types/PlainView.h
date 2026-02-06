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
		using typename Internal::BasicPlainView<TValue>::Iterator;


		using Internal::BasicPlainView<TValue>::GetValueAt;
		using Internal::BasicPlainView<TValue>::IsEmpty;
		using Internal::BasicPlainView<TValue>::GetLength;
		using Internal::BasicPlainView<TValue>::GetBegin;
		using Internal::BasicPlainView<TValue>::GetEnd;

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


		PlainView( Iterator begin, Iterator end ) : PlainView{ begin, size_t( std::distance( begin, end ) ) } {};


		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		PlainView( const PlainView<TOtherValue>& other ) : PlainView( other.GetBegin(), other.GetEnd() ) {};

		template< size_t ARRAY_LENGTH >
		PlainView( TValue (&elements)[ ARRAY_LENGTH ] ) : PlainView{ elements, ARRAY_LENGTH } {};

		template< size_t ARRAY_LENGTH >
		PlainView( std::array<TValue, ARRAY_LENGTH>& elements ) : PlainView{ elements.data(), ARRAY_LENGTH } {};

		template< typename TAllocator >
		PlainView( std::vector<TValue, TAllocator>& elements ) : PlainView{ elements.data(), elements.size() } {};


		template< typename TOtherValue, typename = std::enable_if_t<std::is_convertible_v<TOtherValue*, TValue*>> >
		inline PlainView& operator = ( const PlainView<TOtherValue>& other )		{ return CopyAndSwap( *this, other ); };

		template< size_t ARRAY_LENGTH >
		inline PlainView& operator = ( TValue elements[ ARRAY_LENGTH ] )			{ return CopyAndSwap( *this, elements ); };

		template< size_t ARRAY_LENGTH >
		inline PlainView& operator = ( std::array<TValue, ARRAY_LENGTH>& elements )	{ return CopyAndSwap( *this, elements ); };

		template< typename TAllocator >
		inline PlainView& operator = ( std::vector<TValue, TAllocator>& elements )	{ return CopyAndSwap( *this, elements ); };

	// Public interface.
	public:
		/**
			@brief	Get the sub-view produced from this one by truncating the `length` elements from tail.

			@param	length	Number of elements to be skipped backward from end of this view.
			@return			The value returned is new view with same begin, but shorter length.
			@retval	{}		In case the given `length` is more or equal to the length of this view.
		*/
		inline PlainView TruncateSuffix( const size_t length ) const;

		/**
			@brief	Get the sub-view produced from this one by truncating the `length` elements from head.

			@param	length	Number of elements to be skipped toward from begin of this view.
			@return			The value returned is new view with same end, but shorter length.
			@retval	{}		In case the given `length` is more or equal to the length of this view.
		*/
		inline PlainView TruncatePrefix( const size_t length ) const;

		/**
			@brief	Get the sub-view, that begins from `begin_index` of this view and count the `length` elements.

			@param	begin_index		Ordinal index in this view to become the begin of sub-view.
			@param	length			Number of elements in sub-view.
			@return					The value returned is new view over some consecutive elements of this view.
			@retval	{}				In case the `begin_index` points out of view or `length` is zero.
		*/
		inline PlainView GetSubview( const size_t begin_index, const size_t length ) const;


		inline TValue& operator [] ( const size_t index ) const		{ return GetValueAt( index ); };


		inline explicit operator const bool () const			{ return !IsEmpty(); };
		inline const bool operator ! () const					{ return IsEmpty(); };
	};
}
}
}
}
