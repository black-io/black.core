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
		@brief	Common node for particular static list.

		The `StaticList` carries nodes as statically placed (static-duration storage) instances of `BasicStaticNode`.
		Each basic node is an element of intrusive forward list.

		On its creation, the basic node stores current list head into `m_next_node` and places itself into list head.
		Each static node should be created with its own name for debug purposes.

		The instances of basic node should not be constructed or accessed directly.

		@tparam	TInterface	The common interface of items stored in list.
	*/
	template< typename TInterface >
	class StaticListCommonNode : public BasicStaticNode<InterfaceTag<TInterface>>
	{
	// Friendship.
	public:
		friend class StaticListIterator<TInterface>;	// Grant access to `m_next_node` member.

	// Public interface.
	public:
		// Get the stored interface.
		virtual TInterface& GetInterface() const	= 0;


		inline TInterface* operator -> () const		{ return &GetInterface(); };

	// Heirs interface.
	protected:
		using BasicStaticNode<InterfaceTag<TInterface>>::BasicStaticNode;
	};
}
}
}
}
