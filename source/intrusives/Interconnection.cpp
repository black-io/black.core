#include <black/core/intrusives.h>


namespace Black
{
inline namespace Core
{
inline namespace Intrusives
{
namespace
{
	// Logging channel.
	constexpr const char* LOG_CHANNEL = "Black/Intrusives/Interconnection";
}


	Interconnection::Interconnection()
		: m_begin{ nullptr, &m_end }
		, m_end{ &m_begin, nullptr }
	{
	}

	Interconnection::Interconnection( const Interconnection& other )
		: Interconnection{}
	{
	}

	Interconnection::Interconnection( Interconnection&& other ) noexcept
		: Interconnection{}
	{
		other.Invalidate();
	}

	Interconnection& Interconnection::operator=( const Interconnection& other )
	{
		Invalidate();
		return *this;
	}

	Interconnection& Interconnection::operator=( Interconnection&& other ) noexcept
	{
		Invalidate();
		other.Invalidate();
		return *this;
	}

	Interconnection::~Interconnection() noexcept
	{
		Invalidate();
	}

	void Interconnection::Invalidate() const
	{
		Internal::BasicInterconnectionSlot* cursor = m_begin.m_next;

		m_begin.m_next		= &m_end;
		m_end.m_previous	= &m_begin;

		while( cursor != &m_end )
		{
			ENSURES_DEBUG( cursor != nullptr );
			auto slot = std::exchange( cursor, cursor->m_next );

			slot->Invalidate();
			slot->Reset();
		}
	}

	void Interconnection::RegisterSlot( Internal::BasicInterconnectionSlot& slot ) const
	{
		slot.Detach();
		slot.InsertBefore( m_end );
	}
}
}
}
