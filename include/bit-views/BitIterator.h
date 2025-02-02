#pragma once


namespace Black
{
inline namespace Core
{
inline namespace BitViews
{
namespace Internal
{
	// Iterator type for bit view.
	template< typename TBitStorage >
	class BitIterator final
	{
	// Iterator traits.
	public:
		using self_type			= BitIterator;
		using size_type			= size_t;
		using difference_type	= ptrdiff_t;
		using value_type		= BitAdapter<TBitStorage>;
		using pointer			= BitAdapter<TBitStorage>*;
		using reference			= BitAdapter<TBitStorage>&;
		using iterator_category	= std::random_access_iterator_tag;

	// Friendship interface.
	public:
		inline void swap( self_type& left, self_type& right )	{ left.Swap( right ); };

	// Construction and assignment.
	public:
		BitIterator() = default;
		BitIterator( std::nullptr_t ) {};
		BitIterator( const self_type& other ) = default;
		BitIterator( self_type&& other );
		BitIterator( TBitStorage* head, const size_t bit_length );
		BitIterator( TBitStorage* head, const size_t bit_length, const size_t start_bit_index );


		inline self_type& operator = ( const self_type& other ) = default;
		inline self_type& operator = ( self_type&& other );
		inline self_type& operator = ( std::nullptr_t );

	// Public interface.
	public:
		// Swap the state with given iterator.
		inline void Swap( self_type& other );


		// Get the head of stream.
		inline TBitStorage* const GetStreamHead() const;

		// Get the index of current bit in stream.
		inline const size_t GetStreamBitIndex() const;

		// Get the storage of current bit.
		inline TBitStorage* const GetCurrentStorage() const;

		// Get the index of bit in current storage.
		inline const size_t GetCurrentBitIndex() const;

		// Whether the iterator is valid.
		inline const bool IsValid() const;


		inline value_type operator * () const;


		inline self_type& operator ++ ();
		inline self_type operator ++ ( int );
		inline self_type& operator += ( const difference_type offset );
		inline self_type operator + ( const difference_type offset );

		inline self_type& operator -- ();
		inline self_type operator -- ( int );
		inline self_type& operator -= ( const difference_type offset );
		inline self_type operator - ( const difference_type offset );


		inline explicit operator const bool () const	{ return IsValid(); };
		inline const bool operator ! () const			{ return !IsValid(); };


		inline const bool operator == ( const self_type& other ) const;
		inline const bool operator != ( const self_type& other ) const;
		inline const bool operator > ( const self_type& other ) const;
		inline const bool operator >= ( const self_type& other ) const;
		inline const bool operator < ( const self_type& other ) const;
		inline const bool operator <= ( const self_type& other ) const;

	// Private interface.
	private:
		// Invalidate the iterator.
		inline void Invalidate();

	// Private state.
	private:
		TBitStorage*					m_head			= nullptr;	// Head of bit storage.
		size_type						m_bit_length	= 0;		// Length of bit storage, in bits.
		BitStorageIndex<TBitStorage>	m_bit_index		{ 0 };		// Index of current bit.
	};
}
}
}
}
