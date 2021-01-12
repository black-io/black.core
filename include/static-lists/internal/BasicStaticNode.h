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
		@brief	Basic interface for nodes of particular static collection.

		The `BasicStaticList` carries nodes as statically placed (static-duration storage) instances of `BasicStaticNode`.
		Each basic node is an element of intrusive forward list.

		On its creation, the basic node may store, if required, current list head into `m_next_node` and place itself into list head.
		Each static node should be created with its own name for debug purposes.

		The instances of basic node should not be constructed or accessed directly.

		@tparam	TStorageTag		Tagging type to indicate the unique static collection.
	*/
	template< typename TStorageTag >
	class BasicStaticNode : private Black::NonTransferable
	{
	// Friendship.
	public:
		friend class BasicStaticList<TStorageTag>;	// Grant access to `m_next_node` member.

	// Construction and destruction.
	public:
		BasicStaticNode()			= delete;
		virtual ~BasicStaticNode()	= default;

	// Public interface.
	public:
		// Invalidate (destroy) the content of node.
		virtual void Invalidate() = 0;


		// Get the debug name (only for debug purposes).
		inline std::string_view GetDebugName() const { return *m_name; };

	// Heirs construction.
	protected:
		inline BasicStaticNode( Black::DebugName&& name )						: m_name{ std::move( name ) } {};
		inline BasicStaticNode( Black::DebugName&& name, const InstantInsert )	: m_name{ std::move( name ) } { PlugIntoList(); };

	// Heirs interface.
	protected:
		// Get the next node in static list.
		inline BasicStaticNode* const GetNextNode() const;

		// Plug the node into static list. May be used only once!
		inline void PlugIntoList();

	// Private state.
	private:
		BasicStaticNode*		m_next_node	= nullptr;	// Next node in list.
		const Black::DebugName	m_name;					// Debug name.
	};
}
}
}
}
