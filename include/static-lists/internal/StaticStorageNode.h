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
		@brief	Implementation of static storage node.

		Each node of static storage carries its own object of given implementation type. The memory buffer is placed inside of node.
		Construction of hosted object always deferred to the moment, when the object is required. Also only default construction is allowed for hosted object.

		@tparam	TStorageTag		Tagging type to indicate the unique static collection.
		@tparam	TImplementation	Type of hosted object.
	*/
	template< typename TStorageTag, typename TImplementation >
	class alignas( TImplementation ) StaticStorageNode final : private BasicStaticNode<TStorageTag>
	{
	// Construction and initialization.
	public:
		inline StaticStorageNode()										: StaticStorageNode{ TImplementation::GetDebugName() } {};
		inline explicit StaticStorageNode( Black::DebugName&& name )	: BasicStaticNode<TStorageTag>{ std::move( name ) } {};

	// Public interface.
	public:
		inline explicit operator const bool () const					{ return m_implementation != nullptr; };
		inline const bool operator ! () const							{ return m_implementation == nullptr; };


		inline TImplementation& operator * ()							{ return GetImplementation(); };
		inline TImplementation* operator -> ()							{ return &GetImplementation(); };

	// Private interface.
	private:
		// Construct the implementation.
		inline TImplementation& ConstructImplementation();

		// Get the stored implementation.
		inline TImplementation& GetImplementation();


		/// @see	BasicStaticNode::Invalidate
		void Invalidate() override;

	// Private state.
	private:
		Black::SpinLock							m_lock;												// For synchronized access to implementation.
		TImplementation*						m_implementation						= nullptr;	// Pointer to allocated instance.
		alignas( TImplementation ) std::byte	m_storage[ sizeof( TImplementation ) ];				// Memory buffer to store the allocated instance.
	};
}
}
}
}
