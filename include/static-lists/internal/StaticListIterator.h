#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
namespace Internal
{
	/**
		@breif	Iteration tool for particular static list.

		This iterator satisfy the requirements of standard forward iterator. It may be used in standard algorithms and range-based for loops.
		It is swappable as well.

		@tparam	TInterface	Interface of static list items.
	*/
	template< typename TInterface >
	class StaticListIterator final
	{
	// Iterator traits.
	public:
		using self_type			= StaticListIterator;
		using difference_type	= std::ptrdiff_t;
        using value_type		= std::remove_const_t<TInterface>;
        using pointer			= TInterface*;
        using reference			= TInterface&;
        using iterator_category	= std::forward_iterator_tag;

	// Friendship interface.
	public:
		// Swap the content of iterators.
		friend inline void swap( StaticListIterator& left, StaticListIterator& right )
		{
			Black::Swap( left.m_current_node, right.m_current_node );
		}

	// Construction and assignment.
	public:
		StaticListIterator()									= default;
		StaticListIterator( std::nullptr_t )					{};
		StaticListIterator( const StaticListIterator& other )	= default;
		StaticListIterator( StaticListIterator&& other );
		explicit StaticListIterator( StaticListCommonNode<TInterface>* root_node );


		inline StaticListIterator& operator = ( const StaticListIterator& other )				= default;
		inline StaticListIterator& operator = ( StaticListCommonNode<TInterface>* root_node );
		inline StaticListIterator& operator = ( StaticListIterator&& other );
		inline StaticListIterator& operator = ( std::nullptr_t );

	// Public interface.
	public:
		// Get the current node the iterator points.
		inline StaticListCommonNode<TInterface>* GetNode() const;


		inline self_type& operator ++ ();
		inline self_type operator ++ ( int );

		inline reference operator * () const;
		inline pointer operator -> () const;

		inline explicit operator const bool () const							{ return m_current_node != nullptr; };
		inline const bool operator ! () const									{ return m_current_node == nullptr; };

		inline const bool operator == ( const StaticListIterator& other ) const	{ return m_current_node == other.m_current_node; };
		inline const bool operator != ( const StaticListIterator& other ) const	{ return m_current_node != other.m_current_node; };

	// Private interface.
	private:
		// Switch to next node in list.
		inline void GoNextNode();

	// Private state.
	private:
		StaticListCommonNode<value_type>* m_current_node = nullptr;
	};
}
}
}
}
