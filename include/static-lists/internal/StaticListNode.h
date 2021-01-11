#pragma once


namespace Black
{
inline namespace Core
{
inline namespace StaticLists
{
namespace Internal
{
	template< typename TInterface, typename TImplementation >
	class StaticListNode final : private StaticListBasicNode<TInterface>
	{
	public:
		StaticListNode() : StaticListBasicNode<TInterface>{ TImplementation::GetDebugName() } {};
		explicit StaticListNode( Black::DebugName&& name ) : StaticListBasicNode<TInterface>{ std::move( name ) } {};

		template< typename... TArguments >
		explicit StaticListNode( Black::DebugName&& name, Black::ConstructInplace, TArguments&&... arguments );

		virtual ~StaticListNode();

	public:
		// Construct the implementation.
		template< typename... TArguments >
		inline TImplementation& Construct( TArguments&&... arguments ) const;

		// Destroy the stored implementation.
		inline void Destroy();


		inline explicit operator const bool () const			{ return m_implementation != nullptr; };
		inline const bool operator ! () const					{ return m_implementation == nullptr; };


		inline TImplementation& operator * () const				{ return GetImplementation(); };
		inline TImplementation* operator -> () const			{ return &GetImplementation(); };

	private:
		// Get the stored implementation.
		inline TImplementation& GetImplementation() const;

		// Invalidate (destroy) the stored interface.
		virtual void Invalidate() override						{ Destroy(); };

		// Get the stored interface.
		virtual TInterface& GetInterface() const override		{ return GetImplementation(); };

	private:
		static constexpr size_t STORAGE_ALIGNMENT	= alignof( TImplementation );
		static constexpr size_t STORAGE_LENGTH		= sizeof( TImplementation );

		mutable TImplementation*										m_implementation	= nullptr;
		mutable std::array<uint8_t, STORAGE_LENGTH + STORAGE_ALIGNMENT>	m_storage			{};
	};
}
}
}
}
