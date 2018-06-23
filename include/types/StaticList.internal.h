#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
namespace Internal
{
	/**
		@brief	Basic interface for static list nodes.
		The `StaticList` carries nodes as statically placed (static-duration storage) instances of `StaticListBasicNode`.
		Each basic node is an element of intrusive forward list.

		On its creation, the basic node stores current list head into `m_next_node` and places itself into list head.
		Each static node should be created with its own name for debug purposes.

		The instances of basic node should not be constructed or accessed directly.

		@tparam	TInterface	The common interface of stored items.
	*/
	template< typename TInterface >
	class StaticListBasicNode : private Black::NonTransferable
	{
		friend class StaticListIterator<TInterface>;	// Grant access to `m_next_node` member.
		friend class Black::StaticList<TInterface>;		// Grant access to `m_next_node` member.

	// Public interface.
	public:
		virtual ~StaticListBasicNode() = default;

		// Invalidate (destroy) the stored interface.
		virtual void Invalidate() = 0;

		// Get the stored interface.
		virtual const TInterface& GetInterface() const = 0;

		// Get the debug name (only for debug purposes).
		inline const char* const GetDebugName() const	{ return *m_name; };


		inline const TInterface* operator -> () const	{ return &GetInterface(); };

	// Inheritance interface.
	protected:
		StaticListBasicNode() = delete;
		StaticListBasicNode( Black::DebugName&& name ) : m_name{ std::move( name ) } { PlugIntoList(); };

	// Private interface.
	private:
		// Plug the node into static list.
		inline void PlugIntoList();

	// Private state.
	private:
		StaticListBasicNode*	m_next_node	= nullptr;	// Next node in list.
		const Black::DebugName	m_name;					// Debug name.
	};

	/**
		@brief	Construction proxy to properly construct the implementations of static list.

		Construction proxy implements the selectivity of object construction function between aggregate construction and narrowing construction.

		@tparam	TImplementation	The implementation type to create the objects.
	*/
	template< typename TImplementation >
	struct ConstructionProxy final
	{
		// Whether the `TImplementation` can be constructed through defined constructor with given argument types.
		template< typename... TArguments >
		static constexpr bool IS_CONSTRUCTIBLE = Black::IS_CONSTRUCTIBLE<TImplementation, TArguments...>;

		// Narrowing construction, in case of `TImplementation` may be constructed.
		template< typename... TArguments >
		static inline Black::EnableIf<IS_CONSTRUCTIBLE<TArguments...>, TImplementation*> Construct( void* memory, TArguments&&... arguments )
		{
			EXPECTS_DEBUG( memory != nullptr );
			return new( memory ) TImplementation( std::forward<TArguments>( arguments )... );
		}

		// Brace initialization, in case of  `TImplementation` is an aggregate type of has no constructor with given arguments.
		template< typename... TArguments >
		static inline Black::EnableIf<!IS_CONSTRUCTIBLE<TArguments...>, TImplementation*> Construct( void* memory, TArguments&&... arguments )
		{
			EXPECTS_DEBUG( memory != nullptr );
			return new( memory ) TImplementation{ std::forward<TArguments>( arguments )... };
		}
	};
}
}
}
}
