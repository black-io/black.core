#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
	/**
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
		virtual ~Interconnection() noexcept;


		Interconnection& operator = ( const Interconnection& other );
		Interconnection& operator = ( Interconnection&& other ) noexcept;

	// Public interface.
	public:
		// Whether the interconnection host some slots.
		inline const bool HasInterconnections() const	{ return m_begin.m_next != &m_end; };

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
		// Perform the invalidation of registered slots.
		void Invalidate() const;


		// Register given slot. Safely resolve the previous registration of slot.
		void RegisterSlot( Internal::BasicInterconnectionSlot& slot ) const;

	// Private non-state.
	private:
		mutable DummySlot	m_begin;
		mutable DummySlot	m_end;
	};
}
}
}
