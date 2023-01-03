#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
	/**
		@brief	Forward list.

		Intrusive forward list repeats the functionality of standard forward list from STL, but does not use memory allocations.
		The slot of value should be stored by value itself. List uses the pointer-to-member to access the slot.
		Since the slot is stored by value and accessed by pointer, in same time the value may be stored only by one list that use same slot member.

		This template declare the STL-compatible interface to allow use it with standard algorithms.

		@tparam	TValue			Type of stored values.
		@tparam	SLOT_POINTER	Pointer-to-member of slot to be used.
	*/
	template< typename TValue, auto SLOT_POINTER >
	class IntrusiveForwardList;

	/**
		@brief	Partial specialization of intrusive forward list, where the slot is placed directly at type of container element.

		@tparam	TValue			Type of stored values.
		@tparam	SLOT_POINTER	Pointer-to-member of slot to be used.
	*/
	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	class IntrusiveForwardList<TValue, SLOT_POINTER> final
		: public Black::StandardForwardListFacade<
			IntrusiveForwardList<TValue, SLOT_POINTER>,
			Internal::BasicIntrusiveForwardList<TValue, Internal::IntrusiveTypeTraits<TValue, SLOT_POINTER>>,
			false
		>
	{
	// Most valuable private aliases.
	private:
		// Functional base of this type.
		using ListBase = Internal::BasicIntrusiveForwardList<TValue, Internal::IntrusiveTypeTraits<TValue, SLOT_POINTER>>;

		// Direct base of this type.
		using DirectBase = Black::StandardForwardListFacade<IntrusiveForwardList<TValue, SLOT_POINTER>, ListBase, false>;

	// Public aliases.
	public:
		using typename ListBase::Iterator;


		using ListBase::IsEmpty;

	// Friendship interface.
	public:
		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline Iterator begin( const IntrusiveForwardList& range )					{ return range.GetBegin(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline Iterator end( const IntrusiveForwardList& range )						{ return range.GetEnd(); };

		// 'Swap' interface.
		friend inline void swap( IntrusiveForwardList& left, IntrusiveForwardList& right )	{ left.Swap( right ); };

	// Public lifetime management.
	public:
		inline IntrusiveForwardList()			= default;
		inline ~IntrusiveForwardList() noexcept	= default;

		inline IntrusiveForwardList( IntrusiveForwardList&& other ) noexcept
			: DirectBase{ std::forward<DirectBase&&>( other ) }
		{
		}


		inline IntrusiveForwardList& operator = ( IntrusiveForwardList&& other ) noexcept
		{
			IntrusiveForwardList{ std::move( other ) }.Swap( this );
			return *this;
		}

	// Public interface.
	public:
		// Swap the state with given other.
		inline void Swap( IntrusiveForwardList& other )	{ ListBase::Swap( other ); };


		inline explicit operator const bool () const	{ return !IsEmpty(); };
		inline const bool operator ! () const			{ return IsEmpty(); };
	};

	/**
		@brief	Partial specialization of intrusive forward list, where the slot is placed at the base type of container element.

		@tparam	TValue			Type of stored values.
		@tparam	TValueBase		Type of value base, where the container slot is placed.
		@tparam	SLOT_POINTER	Pointer-to-member of slot to be used.
	*/
	template< typename TValue, typename TValueBase, Black::IntrusiveForwardListSlot TValueBase::* SLOT_POINTER >
	class IntrusiveForwardList<TValue, SLOT_POINTER> final
		: public Black::StandardForwardListFacade<
			IntrusiveForwardList<TValue, SLOT_POINTER>,
			Internal::BasicIntrusiveForwardList<TValue, Internal::IntrusiveTypeTraits<TValue, SLOT_POINTER>>,
			false
		>
	{
	// Most valuable private aliases.
	private:
		// Functional base of this type.
		using ListBase = Internal::BasicIntrusiveForwardList<TValue, Internal::IntrusiveTypeTraits<TValue, SLOT_POINTER>>;

		// Direct base of this type.
		using DirectBase = Black::StandardForwardListFacade<IntrusiveForwardList<TValue, SLOT_POINTER>, ListBase, false>;

	// Public aliases.
	public:
		using typename ListBase::Iterator;


		using ListBase::IsEmpty;

	// Friendship interface.
	public:
		// 'Range-based for loop' interface, the `begin( __range )` statement.
		friend inline Iterator begin( const IntrusiveForwardList& range )					{ return range.GetBegin(); };

		// 'Range-based for loop' interface, the `end( __range )` statement.
		friend inline Iterator end( const IntrusiveForwardList& range )						{ return range.GetEnd(); };

		// 'Swap' interface.
		friend inline void swap( IntrusiveForwardList& left, IntrusiveForwardList& right )	{ left.Swap( right ); };

	// Public lifetime management.
	public:
		inline IntrusiveForwardList()			= default;
		inline ~IntrusiveForwardList() noexcept	= default;

		inline IntrusiveForwardList( IntrusiveForwardList&& other ) noexcept
			: DirectBase{ std::forward<DirectBase&&>( other ) }
		{
		}


		inline IntrusiveForwardList& operator = ( IntrusiveForwardList&& other ) noexcept
		{
			IntrusiveForwardList{ std::move( other ) }.Swap( this );
			return *this;
		}

	// Public interface.
	public:
		// Swap the state with given other.
		inline void Swap( IntrusiveForwardList& other )	{ ListBase::Swap( other ); };


		inline explicit operator const bool () const	{ return !IsEmpty(); };
		inline const bool operator ! () const			{ return IsEmpty(); };
	};
}
}
}
