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
	class BasicInterconnectionSlot
	{
	// Friendship declarations.
	public:
		// Grant access to private state.
		friend class Black::Interconnection;

	// Lifetime management.
	public:
		BasicInterconnectionSlot() = default;

		BasicInterconnectionSlot( const BasicInterconnectionSlot& other );
		BasicInterconnectionSlot( BasicInterconnectionSlot&& other ) noexcept;

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

	// Heirs lifetime management.
	protected:
		~BasicInterconnectionSlot() noexcept;

	// Heirs interface.
	protected:
		// Attach this slot to given interconnection.
		void AttachTo( const Black::Interconnection& interconnection );

		// Detach the slot from interconnection.
		void Detach();

	// Private lifetime management.
	private:
		BasicInterconnectionSlot( BasicInterconnectionSlot* previous, BasicInterconnectionSlot* next );

	// Private interface.
	private:
		// Insert this slot in list before the given one.
		void InsertBefore( BasicInterconnectionSlot& other );

		// Reset the state of slot.
		void Reset();

	// Private state.
	private:
		BasicInterconnectionSlot* m_previous	= nullptr;	// Previous slot in interconnection.
		BasicInterconnectionSlot* m_next		= nullptr;	// Next slot in interconnection.
	};
}
}
}
}
