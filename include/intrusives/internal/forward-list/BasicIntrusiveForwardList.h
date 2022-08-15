#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
inline namespace ForwardList
{
	/**
		@brief	Basic functionality of intrusive forward list.

		Intrusive forward list repeats the functionality of standard forward list from STL, but does not use memory allocations.
		The slot of value should be stored by value itself. List uses the pointer-to-member to access the slot.
		Since the slot is stored by value and accessed by pointer, in same time the value may be stored only by one list that use same slot member.

		@tparam	TValue	Type of stored values.
		@tparam	TTraits	Type traits for container.
	*/
	template< typename TValue, typename TTraits >
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

		// Pointer to value.
		using ValuePointer = TValue*;

		// Iterator of view.
		using Iterator = ForwardListIterator<TValue, TTraits>;

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
		inline void InsertAfter( Iterator position, Value& value );

		// Erase the value after given position. Expects the iterator is valid.
		inline void EraseAfter( Iterator position );


		// Get the value at the head of list. Expects that list is not empty.
		inline Value& GetFirstValue() const;

		// Get the iterator to beginning of list. May return invalid iterator.
		inline Iterator GetBegin() const;

		// Get the iterator to ending of list. May return invalid iterator.
		inline Iterator GetEnd() const;


		// Get the size of list.
		inline const size_t GetLength() const;


		// Whether the list is empty.
		inline const bool IsEmpty() const;
	};
}
}
}
}
}
