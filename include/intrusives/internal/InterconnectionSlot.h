#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
namespace Internal
{
	// Intrusive link.
	template< typename TLinkedType, bool USE_LINKING >
	class IntrusiveLink;

	// Positive specification for intrusive link.
	template< typename TLinkedType >
	class IntrusiveLink<TLinkedType, true> : protected Black::IntrusiveHook::RegularIntrusiveLink
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
		virtual void SetHook( const TLinkedType* )		{};

		// Empty stub for functional symmetry.
		virtual void InvalidateIntrusiveLink()			{};
	};
}


	// Intrusive link.
	template< typename TLinkedType >
	using IntrusiveLink = Internal::IntrusiveLink<TLinkedType, std::is_base_of_v<Black::IntrusiveHook, TLinkedType>>;
}
}
}
}
