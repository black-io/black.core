#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Types
{
	// Intrusive link.
	template< typename TLinkedType, bool USE_LINKING = Black::IS_BASE_OF<IntrusiveHook, TLinkedType> >
	class IntrusiveLink;

	// Positive specification for intrusive link.
	template< typename TLinkedType >
	class IntrusiveLink<TLinkedType, true> : protected IntrusiveHook::RegularIntrusiveLink
	{
	public:
		IntrusiveLink() = default;
		IntrusiveLink( const IntrusiveLink& other );
		IntrusiveLink( IntrusiveLink&& other );
		explicit IntrusiveLink( const TLinkedType* hook );
		virtual ~IntrusiveLink();

	protected:
		// Link the given intrusive hook.
		virtual void SetHook( const TLinkedType* hook );

		// Invalidate the link.
		virtual void InvalidateIntrusiveLink() override;

	private:
		// Register link for current hook.
		void RegisterLink();

		// Unregister link for current hook.
		void UnregisterLink();

	private:
		const TLinkedType*	m_hook	= nullptr;	// Linked intrusive hook via its derived type.
	};

	// Negative specification for intrusive link.
	template< typename TLinkedType >
	class IntrusiveLink<TLinkedType, false>
	{
	public:
		IntrusiveLink()									= default;
		IntrusiveLink( const IntrusiveLink& )			= default;
		IntrusiveLink( IntrusiveLink&& )				= default;
		explicit IntrusiveLink( const TLinkedType* )	{};
		virtual ~IntrusiveLink()						= default;

	protected:
		// Empty stub for functional symmetry.
		virtual void SetHook( const TLinkedType* hook )	{};

		// Empty stub for functional symmetry.
		virtual void InvalidateIntrusiveLink() override	{};
	};
}
}
}
