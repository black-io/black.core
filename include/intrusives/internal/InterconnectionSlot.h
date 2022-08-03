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
	class InterconnectionSlot
	{
	// Lifetime management.
	public:
		InterconnectionSlot() = default;

		InterconnectionSlot( const InterconnectionSlot& other );
		InterconnectionSlot( InterconnectionSlot&& other ) noexcept;
		~InterconnectionSlot();

	// Public interface.
	public:
		// Whether the slot is attached to interconnection.
		inline const bool IsAttached() const		{ return ( m_previous != nullptr ) || ( m_next != nullptr ); };

		// Whether the slot implies the begin of interconnection.
		inline const bool IsBegin() const			{ return ( m_previous == nullptr ) && ( m_next != nullptr ); };

		// Whether the slot implies the end of interconnection.
		inline const bool IsEnd() const				{ return ( m_previous != nullptr ) && ( m_next == nullptr ); };

		// Whether the slot is attached to interconnection.
		inline const bool IsRegular() const			{ return ( m_previous != nullptr ) && ( m_next != nullptr ); };

	// Public virtual interface.
	public:
		// Perform the slot invalidation.
		virtual void Invalidate() = 0;

	// Private interface.
	private:
		// Insert this slot before given other.
		void InsertBefore( InterconnectionSlot& other );

		// Insert this slot after given other.
		void InsertAfter( InterconnectionSlot& other );

		// Insert this slot before given other, if can, or else insert after it.
		void InsertNear( const InterconnectionSlot& other );


		// Reset the links to previous and next slots.
		void Reset();

		// Detach the slot from list of interconnections.
		void Detach();

	// Private state.
	private:
		InterconnectionSlot* m_previous	= nullptr;	// Previous slot in interconnection.
		InterconnectionSlot* m_next		= nullptr;	// Next slot in interconnection.
	};
}
}
}
}
