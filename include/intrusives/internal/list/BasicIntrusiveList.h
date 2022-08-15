#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace Internal
{
inline namespace List
{
	/**
		@brief	Basic functionality of intrusive list.

		Intrusive list repeats the functionality of standard list from STL, but does not use memory allocations.
		The slot of value should be stored by value itself. List uses the pointer-to-member to access the slot.
		Since the slot is stored by value and accessed by pointer, in same time the value may be stored only by one list that use same slot member.

		@tparam	TValue	Type of stored values.
		@tparam	TTraits	Type traits for container.
	*/
	template< typename TValue, typename TTraits >
	class BasicIntrusiveList : private DoublyLinkedList
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
		using Iterator = Internal::ListIterator<TValue, TTraits>;

	// Lifetime management.
	public:
		inline BasicIntrusiveList()							= default;
		inline BasicIntrusiveList( BasicIntrusiveList&& )	= default;
		inline ~BasicIntrusiveList()						= default;

	// Public interface.
	public:
		// Clear the list, detaching all values.
		inline void Clear();


		// Add the value as new head of list. Safely detaches the value from previous list.
		inline void PushFront( Value& value );

		// Remove the current head of list. Expects that list is not empty.
		inline void PopFront();

		// Add the value as new tail of list. Safely detaches the value from previous list.
		inline void PushBack( Value& value );

		// Remove the current tail of list. Expects that list is not empty.
		inline void PopBack();

		// Insert the given value before the given position. Expects the iterator is valid. Safely detaches the value from previous list.
		inline void Insert( Iterator position, Value& value );

		// Erase the value at given position. Expects the iterator is valid.
		inline void Erase( Iterator position );


		// Get the value at the head of list. Expects that list is not empty.
		inline Value& GetFront() const;

		// Get the value at the tail of list. Expects that list is not empty.
		inline Value& GetBack() const;

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
