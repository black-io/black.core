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
	{
	// Public inner types.
	public:
		static_assert( !std::is_reference_v<TValue>,	"Value type may not be reference type." );
		static_assert( !std::is_const_v<TValue>,		"Value type may not be constant." );


		// Type of stored values.
		using Value			= TValue;

		// Iterator of view.
		using Iterator		= Internal::ForwardListIterator<TValue, SLOT_POINTER>;

		// Iterator of view.
		using ConstIterator	= Internal::ForwardListConstIterator<TValue, SLOT_POINTER>;

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

	// Lifetime management.
	public:
		inline IntrusiveForwardList()							= default;
		inline IntrusiveForwardList( IntrusiveForwardList&& )	= default;
		inline ~IntrusiveForwardList()							= default;


		inline IntrusiveForwardList& operator = ( IntrusiveForwardList&& )	= default;

	// Public interface.
	public:
		// Clear the list, detaching all values.
		inline void Clear();


		// Add the value as new head of list. Safely detaches the value from previous list.
		inline void PushFront( Value& value );

		// Remove the current head of list. Expects that list is not empty.
		inline void PopFront();

		// Insert the given value after the given position. Expects the iterator is valid. Safely detaches the value from previous list.
		inline void InsertAfter( ConstIterator position, Value& value );

		// Erase the value after given position. Expects the iterator is valid.
		inline void EraseAfter( ConstIterator position );


		// Get the value at the head of list. Expects that list is not empty.
		inline Value& GetFront();

		// Get the value at the head of list. Expects that list is not empty.
		inline const Value& GetFront() const;

		// Get the iterator to beginning of list. May return invalid iterator.
		inline Iterator GetBegin();

		// Get the iterator to beginning of list. May return invalid iterator.
		inline ConstIterator GetBegin() const;

		// Get the iterator to beginning of list. May return invalid iterator.
		inline ConstIterator GetConstBegin() const;

		// Get the iterator to ending of list. May return invalid iterator.
		inline Iterator GetEnd();

		// Get the iterator to ending of list. May return invalid iterator.
		inline ConstIterator GetEnd() const;

		// Get the iterator to ending of list. May return invalid iterator.
		inline ConstIterator GetConstEnd() const;


		// Get the size of list.
		inline const size_t GetSize() const;


		// Whether the list is empty.
		inline const bool IsEmpty() const;

	// Private inner types.
	private:
		// Traits for intrusive operations.
		using Traits = Internal::IntrusiveTraits<TValue, Black::IntrusiveForwardListSlot, SLOT_POINTER>;

	// Private state.
	private:
		Internal::SinglyLinkedList m_slots; // Inner container for intrusive slots.
	};
}
}
}
