#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
namespace Internal
{
	template< typename TInterface >
	class StaticListIterator final
	{
	// Iterator traits.
	public:
		using self_type			= StaticListIterator;
		using difference_type	= size_t;
        using value_type		= std::remove_const_t<TInterface>;
        using pointer			= TInterface*;
        using reference			= TInterface&;
        using iterator_category	= std::forward_iterator_tag;

	// Friendship interface.
	public:
		friend inline void swap( StaticListIterator& left, StaticListIterator& right )
		{
			using std::swap;
			swap( left.m_current_node, right.m_current_node );
		}

	// Construction and assignment.
	public:
		StaticListIterator()									= default;
		StaticListIterator( std::nullptr_t )					{};
		StaticListIterator( const StaticListIterator& other )	= default;
		StaticListIterator( StaticListIterator&& other );
		explicit StaticListIterator( StaticListBasicNode<TInterface>* root_node );


		inline StaticListIterator& operator = ( const StaticListIterator& other )				= default;
		inline StaticListIterator& operator = ( StaticListBasicNode<TInterface>* root_node );
		inline StaticListIterator& operator = ( StaticListIterator&& other );
		inline StaticListIterator& operator = ( std::nullptr_t );

	// Public interface.
	public:
		inline StaticListBasicNode<TInterface>* GetNode() const;

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
		StaticListBasicNode<value_type>*	m_current_node = nullptr;
	};
}
}
}
}
