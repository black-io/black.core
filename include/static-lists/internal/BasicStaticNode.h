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
		@brief	Basic interface for static list nodes.
		The `StaticList` carries nodes as statically placed (static-duration storage) instances of `BasicStaticNode`.
		Each basic node is an element of intrusive forward list.

		On its creation, the basic node stores current list head into `m_next_node` and places itself into list head.
		Each static node should be created with its own name for debug purposes.

		The instances of basic node should not be constructed or accessed directly.

		@tparam	TInterface	The common interface of stored items.
	*/
	template< typename TInterface >
	class BasicStaticNode : private Black::NonTransferable
	{
	// Friendship.
	public:
		friend class StaticListIterator<TInterface>;	// Grant access to `m_next_node` member.
		friend class Black::StaticList<TInterface>;		// Grant access to `m_next_node` member.

	// Construction and destruction.
	public:
		BasicStaticNode()			= delete;
		virtual ~BasicStaticNode()	= default;

	// Public interface.
	public:
		// Invalidate (destroy) the stored interface.
		virtual void Invalidate() = 0;


		// Get the stored interface.
		virtual TInterface& GetInterface() const = 0;

		// Get the debug name (only for debug purposes).
		inline std::string_view const GetDebugName() const	{ return *m_name; };


		inline TInterface* operator -> () const				{ return &GetInterface(); };

	// Heirs interface.
	protected:
		BasicStaticNode( Black::DebugName&& name ) : m_name{ std::move( name ) } { PlugIntoList(); };

	// Private interface.
	private:
		// Plug the node into static list.
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
