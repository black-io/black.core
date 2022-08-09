#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
	/**
		@brief	Basic functionality of intrusive forward list.

		Intrusive forward list repeats the functionality of standard forward list from STL, but does not use memory allocations.
		The slot of value should be stored by value itself. List uses the pointer-to-member to access the slot.
		Since the slot is stored by value and accessed by pointer, in same time the value may be stored only by one list that use same slot member.

		@tparam	TValue			Type of stored values.
		@tparam	SLOT_POINTER	Pointer-to-member of slot to be used.
	*/
	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	class BasicIntrusiveForwardList : private SinglyLinkedList
	{
	// Restrictions.
	public:
		static_assert( !std::is_reference_v<TValue>,	"Value type may not be reference type." );
		static_assert( !std::is_const_v<TValue>,		"Value type may not be constant." );

	// Public inner types.
	public:
		// Stored value.
		using Value = TValue;

		// Reference to value.
		using ValueReference = TValue&;

		// Reference to constant value.
		using ConstValueReference = const TValue&;

		// Pointer to value.
		using ValuePointer = TValue*;

		// Pointer to constant value.
		using ConstValuePointer = const TValue*;

		// Iterator of view.
		using Iterator = ForwardListIterator<TValue, SLOT_POINTER>;

		// Iterator of view.
		using ConstIterator = ForwardListConstIterator<TValue, SLOT_POINTER>;

	// Lifetime management.
	public:
		inline BasicIntrusiveForwardList()								= default;
		inline BasicIntrusiveForwardList( BasicIntrusiveForwardList&& )	= default;
		inline ~BasicIntrusiveForwardList()								= default;

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
		inline Value& GetFirstValue();

		// Get the value at the head of list. Expects that list is not empty.
		inline const Value& GetFirstValue() const;

		// Get the iterator to beginning of list. May return invalid iterator.
		inline Iterator GetBegin();

		// Get the iterator to beginning of list. May return invalid iterator.
		inline ConstIterator GetBegin() const;

		// Get the iterator to ending of list. May return invalid iterator.
		inline Iterator GetEnd();

		// Get the iterator to ending of list. May return invalid iterator.
		inline ConstIterator GetEnd() const;


		// Get the size of list.
		inline const size_t GetSize() const;


		// Whether the list is empty.
		inline const bool IsEmpty() const;

	// Private inner types.
	private:
		// Traits for intrusive operations.
		using Traits = Internal::IntrusiveTraits<TValue, Black::IntrusiveForwardListSlot, SLOT_POINTER>;
	};
}
}
}
}
