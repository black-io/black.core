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
		@brief	Regular iterator for constant forward list.
	*/
	template< typename TValue, Black::IntrusiveForwardListSlot TValue::* SLOT_POINTER >
	class ForwardListConstIterator final
	{
	// Friendship declarations.
	public:
		// Grant access to private state and constructor.
		friend class Black::IntrusiveForwardList<TValue, SLOT_POINTER>;

		// Grant access to private state and constructor.
		friend class ForwardListIterator<TValue, SLOT_POINTER>;

	// Lifetime management.
	public:
		inline ForwardListConstIterator()									= default;
		inline ForwardListConstIterator( const ForwardListConstIterator& )	= default;
		inline ForwardListConstIterator( ForwardListConstIterator& )		= default;
		inline ~ForwardListConstIterator()									= default;


		inline ForwardListConstIterator& operator = ( const ForwardListConstIterator& )	= default;
		inline ForwardListConstIterator& operator = ( ForwardListConstIterator&& )		= default;

	// Public interface.
	public:
		inline ForwardListConstIterator& operator ++ ();
		inline ForwardListConstIterator operator ++ ( int );

		inline const TValue& operator * () const;
		inline const TValue* operator -> () const;

		inline const bool operator == ( const ForwardListConstIterator& other ) const;
		inline const bool operator != ( const ForwardListConstIterator& other ) const;

	// Private inner types.
	private:
		// Traits for intrusive operations.
		using Traits = IntrusiveTraits<TValue, Black::IntrusiveForwardListSlot, SLOT_POINTER>;

	// Private lifetime management.
	private:
		inline explicit ForwardListConstIterator( SinglyLinkedListIterator iterator );

	// Private state.
	private:
		SinglyLinkedListIterator m_iterator; // Regular iterator for inner list type.
	};
}
}
}
}
