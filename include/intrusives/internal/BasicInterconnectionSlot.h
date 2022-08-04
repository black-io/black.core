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
	// Friendship declarations.
	public:
		// Grant access to private state.
		friend class Black::Interconnection;

	// Lifetime management.
	public:
		InterconnectionSlot() = default;

		InterconnectionSlot( const InterconnectionSlot& other );
		InterconnectionSlot( InterconnectionSlot&& other ) noexcept;
		~InterconnectionSlot() noexcept;

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

	// Heirs interface.
	protected:
		// Register this slot at given interconnection.
		void RegisterAt( Black::Interconnection& interconnection );

	// Private lifetime management.
	private:
		InterconnectionSlot( InterconnectionSlot* previous, InterconnectionSlot* next );

	// Private interface.
	private:
		// Insert this slot in list before the given one.
		void InsertBefore( InterconnectionSlot& other );

		// Reset the state of slot.
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
