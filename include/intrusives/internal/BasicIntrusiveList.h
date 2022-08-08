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
	*/
	template< typename TValue, Black::IntrusiveListSlot TValue::* SLOT_POINTER >
	class BasicIntrusiveList
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
		using Iterator = Internal::ListIterator<TValue, SLOT_POINTER>;

		// Iterator of view.
		using ConstIterator = Internal::ListConstIterator<TValue, SLOT_POINTER>;

	// Lifetime management.
	public:
		inline BasicIntrusiveList()							= default;
		inline BasicIntrusiveList( BasicIntrusiveList&& )	= default;
		inline ~BasicIntrusiveList()						= default;


		inline BasicIntrusiveList& operator = ( BasicIntrusiveList&& )	= default;

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
		inline void Insert( ConstIterator position, Value& value );

		// Erase the value at given position. Expects the iterator is valid.
		inline void Erase( ConstIterator position );


		// Get the value at the head of list. Expects that list is not empty.
		inline Value& GetFront();

		// Get the value at the head of list. Expects that list is not empty.
		inline const Value& GetFront() const;

		// Get the value at the tail of list. Expects that list is not empty.
		inline Value& GetBack();

		// Get the value at the tail of list. Expects that list is not empty.
		inline const Value& GetBack() const;

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
		using Traits = Internal::IntrusiveTraits<TValue, Black::IntrusiveListSlot, SLOT_POINTER>;

	// Private state.
	private:
		Internal::DoublyLinkedList m_slots; // Inner container for intrusive slots.
	};
}
}
}
}
