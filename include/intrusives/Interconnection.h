#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
	/**
		@brief	Interconnection host.

		This type should be used as parent for target type, which objects are required to manage the slots referred to it.
		Inner template `Slot` selects the functionality depending on whether the `Interconnection` is one of base types for `THost` type or not.
		Some types of framework may require the functionality of interconnection slot. Such types are inherited from inner template `Slot`.

		`Slot` represents the single point of interconnection. `Interconnection` represents the host, where slots are registered.
		`Interconnection` is allowed to invalidate the hosted slots. On invalidation the slot become disconnected from interconnection.
		For slot the invalidation means it no more connected to interconnection.

		All this functionality allows to create managed links to objects, that automatically cleared on linked object destroyed.
	*/
	class Interconnection
	{
	// Friendship declarations.
	public:
		// Allow slot to use registration function.
		friend class Internal::BasicInterconnectionSlot;

	// Public inner types.
	public:
		// Regular slot for interconnection.
		template< typename THost >
		using Slot = std::conditional_t<
			std::is_base_of_v<Interconnection, THost>,
			Internal::InterconnectionSlot<THost>,
			Internal::InterconnectionSlotDummy<THost>
		>;

	// Lifetime management.
	public:
		Interconnection();
		Interconnection( const Interconnection& other );
		Interconnection( Interconnection&& other ) noexcept;


		Interconnection& operator = ( const Interconnection& other );
		Interconnection& operator = ( Interconnection&& other ) noexcept;

	// Public interface.
	public:
		// Whether the interconnection host some slots.
		inline const bool HasInterconnections() const	{ return m_begin.m_next != &m_end; };

	// Heirs lifetime management.
	protected:
		~Interconnection() noexcept;

	// Heirs interface.
	protected:
		// Perform the invalidation of registered slots.
		void Invalidate() const;

	// Private inner types.
	private:
		// Dummy slot to declare the `begin` and `end` of list.
		class DummySlot : public Internal::BasicInterconnectionSlot
		{
		// Lifetime management.
		public:
			using Internal::BasicInterconnectionSlot::BasicInterconnectionSlot;

		// `InterconnectionSlot` virtual overrides.
		public:
			/// @see BasicInterconnectionSlot::Invalidate
			void Invalidate() override {};
		};

	// Private interface.
	private:
		// Register given slot. Safely resolve the previous registration of slot.
		void RegisterSlot( Internal::BasicInterconnectionSlot& slot ) const;

	// Private non-state.
	private:
		mutable DummySlot	m_begin;	// Beginning slot of internal list.
		mutable DummySlot	m_end;		// Ending slot of internal list.
	};
}
}
}
