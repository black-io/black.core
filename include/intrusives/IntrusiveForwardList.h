#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
	/**
	*/
	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	class IntrusiveForwardList final
		: public Black::StandardForwardListFacade<IntrusiveForwardList<TValue, SLOT_POINTER>, Internal::BasicIntrusiveForwardList<TValue, SLOT_POINTER>>
	{
	// Public aliases.
	public:
		using typename Internal::BasicIntrusiveForwardList<TValue, SLOT_POINTER>::Iterator;
		using typename Internal::BasicIntrusiveForwardList<TValue, SLOT_POINTER>::ConstIterator;


		using Internal::BasicIntrusiveForwardList<TValue, SLOT_POINTER>::IsEmpty;

	// Friendship interface.
	public:
		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline Iterator begin( IntrusiveForwardList& range )							{ return range.GetBegin(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline Iterator end( IntrusiveForwardList& range )							{ return range.GetEnd(); };

		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline ConstIterator begin( const IntrusiveForwardList& range )				{ return range.GetBegin(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline ConstIterator end( const IntrusiveForwardList& range )				{ return range.GetEnd(); };

		// 'Swap' interface.
		friend inline void swap( IntrusiveForwardList& left, IntrusiveForwardList& right )	{ left.Swap( right ); };

	// Public lifetime management.
	public:
		using Black::StandardForwardListFacade<
			IntrusiveForwardList<TValue, SLOT_POINTER>,
			Internal::BasicIntrusiveForwardList<TValue, SLOT_POINTER>
		>::StandardForwardListFacade;


		inline IntrusiveForwardList& operator = ( IntrusiveForwardList&& other ) noexcept
		{
			// End the lifetime of current list.
			IntrusiveForwardList::~IntrusiveForwardList();

			// Start the lifetime of new list by moving the given `other`.
			return *new( this ) IntrusiveForwardList{ std::move( other ) };
		}

	// Public interface.
	public:
		inline explicit operator const bool () const	{ return !IsEmpty(); };
		inline const bool operator ! () const			{ return IsEmpty(); };
	};
}
}
}
