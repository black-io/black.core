#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
	/**
	*/
	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	class IntrusiveList final
		: public Black::StandardListFacade<IntrusiveList<TValue, SLOT_POINTER>, Internal::BasicIntrusiveList<TValue, SLOT_POINTER>>
	{
	// Public aliases.
	public:
		using typename Internal::BasicIntrusiveList<TValue, SLOT_POINTER>::Iterator;
		using typename Internal::BasicIntrusiveList<TValue, SLOT_POINTER>::ConstIterator;


		using Internal::BasicIntrusiveList<TValue, SLOT_POINTER>::IsEmpty;

	// Friendship interface.
	public:
		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline Iterator begin( IntrusiveList& range )						{ return range.GetBegin(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline Iterator end( IntrusiveList& range )							{ return range.GetEnd(); };

		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline ConstIterator begin( const IntrusiveList& range )				{ return range.GetBegin(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline ConstIterator end( const IntrusiveList& range )				{ return range.GetEnd(); };

		// 'Swap' interface.
		friend inline void swap( IntrusiveList& left, IntrusiveList& right )		{ left.Swap( right ); };

	// Public lifetime management.
	public:
		using Black::StandardListFacade<
			IntrusiveList<TValue, SLOT_POINTER>,
			Internal::BasicIntrusiveList<TValue, SLOT_POINTER>
		>::StandardListFacade;


		inline IntrusiveList& operator = ( IntrusiveList&& other )
		{
			// End the lifetime of current list.
			IntrusiveList::~IntrusiveList();

			// Start the lifetime of new list by moving the given `other`.
			return *new( this ) IntrusiveList{ std::move( other ) };
		}

	// Public interface.
	public:
		inline explicit operator const bool () const	{ return !IsEmpty(); };
		inline const bool operator ! () const			{ return IsEmpty(); };
	};
}
}
}
