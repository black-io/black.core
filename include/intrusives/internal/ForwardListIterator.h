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
	class ForwardListIterator final
	{
	// Lifetime management.
	public:
		inline ForwardListIterator()								= default;
		inline ForwardListIterator( const ForwardListIterator& )	= default;
		inline ForwardListIterator( ForwardListIterator& )			= default;
		inline ~ForwardListIterator()								= default;


		inline ForwardListIterator& operator = ( const ForwardListIterator& )	= default;
		inline ForwardListIterator& operator = ( ForwardListIterator&& )		= default;

	// Public interface.
	public:
		inline ForwardListIterator& operator ++ ();
		inline ForwardListIterator operator ++ ( int );

		inline operator ForwardListConstIterator<TValue, SLOT_POINTER>() const;

		inline TValue& operator * () const;
		inline TValue* operator -> () const;

		inline const bool operator == ( const ForwardListIterator& other ) const;
		inline const bool operator != ( const ForwardListIterator& other ) const;

	// Private inner types.
	private:
		// Traits for intrusive operations.
		using Traits = IntrusiveTraits<TValue, Black::IntrusiveForwardListSlot, SLOT_POINTER>;

	// Private lifetime management.
	private:
		inline explicit ForwardListIterator( SinglyLinkedListIterator iterator );

	// Private state.
	private:
		SinglyLinkedListIterator m_iterator; // Regular iterator for inner list type.
	};
}
}
}
}