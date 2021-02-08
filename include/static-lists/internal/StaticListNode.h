#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
namespace Internal
{
	/**
		@brief	Implementation of static list node.

		Each node of static list carries its own object of particular type. The memory buffer is placed inside of node, but the construction may be deferred
		to the moment, when the object is requested.

		@tparam	TInterface		Type of common interface in static list.
		@tparam	TImplementation	Particular implementation of common interface.
	*/
	template< typename TInterface, typename TImplementation >
	class alignas( TImplementation ) StaticListNode final : private StaticListCommonNode<TInterface>
	{
	// Construction and initialization.
	public:
		inline StaticListNode()										: StaticListNode{ TImplementation::GetDebugName() } {};
		inline explicit StaticListNode( Black::DebugName&& name )	: StaticListCommonNode<TInterface>{ std::move( name ) } {};

		template< typename... TArguments >
		inline StaticListNode( Black::ConstructInplace, TArguments&&... arguments );

		template< typename... TArguments >
		inline StaticListNode( Black::DebugName&& name, Black::ConstructInplace, TArguments&&... arguments );

		virtual ~StaticListNode();

	// Public interface.
	public:
		// Construct the implementation.
		template< typename... TArguments >
		inline TImplementation& Construct( TArguments&&... arguments ) const;

		// Destroy the stored implementation.
		inline void Destroy();


		inline explicit operator const bool () const		{ return m_implementation != nullptr; };
		inline const bool operator ! () const				{ return m_implementation == nullptr; };


		inline TImplementation& operator * () const			{ return GetImplementation(); };
		inline TImplementation* operator -> () const		{ return &GetImplementation(); };

	// Private interface.
	private:
		// Get the stored implementation.
		inline TImplementation& GetImplementation() const;


		/// @see	BasicStaticNode::Invalidate
		void Invalidate() override							{ Destroy(); };

		/// @see	StaticListCommonNode::GetInterface
		TInterface& GetInterface() const override			{ return GetImplementation(); };

	// Private state.
	private:
		mutable	TImplementation*	m_implementation						= nullptr;	// Pointer to allocated instance.
		mutable std::byte			m_storage[ sizeof( TImplementation ) ];				// Memory buffer to store the allocated instance.
	};
}
}
}
}
