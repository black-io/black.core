#include <black/core.h>


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
	RingBuffer::RingBuffer() noexcept = default;

	RingBuffer::RingBuffer( RingBuffer&& other ) noexcept
		: m_buffer{ std::move( other.m_buffer ) }
		, m_write_head{ std::exchange( other.m_write_head, nullptr ) }
		, m_read_head{ std::exchange( other.m_read_head, nullptr ) }
		, m_is_wrapped{ std::exchange( other.m_is_wrapped, false ) }
	{
	}

	RingBuffer::~RingBuffer() noexcept = default;

	RingBuffer::RingBuffer( Black::PlainView<std::byte> buffer ) noexcept
		: m_buffer{ std::move( buffer ) }
		, m_write_head{ m_buffer.GetMemory() }
		, m_read_head{ m_buffer.GetMemory() }
	{
	}

	RingBuffer& RingBuffer::operator=( RingBuffer&& other ) noexcept
	{
		RingBuffer temporary{ std::move( other ) };
		temporary.Swap( *this );
		return *this;
	}

	void RingBuffer::Rewind()
	{
		m_write_head	= m_buffer.GetMemory();
		m_read_head		= m_buffer.GetMemory();
		m_is_wrapped	= false;
	}

	void RingBuffer::Swap( RingBuffer& other )
	{
		Black::Swap( m_buffer, other.m_buffer );
		Black::Swap( m_write_head, other.m_write_head );
		Black::Swap( m_read_head, other.m_read_head );
		Black::Swap( m_is_wrapped, other.m_is_wrapped );
	}

	const size_t RingBuffer::WriteBuffer( Black::NotNull<const void*> buffer, const size_t buffer_length )
	{
		size_t written_length = 0;
		CRET( IsFull(), written_length );

		const std::byte* source_head = reinterpret_cast<const std::byte*>( buffer.Get() );
		const size_t max_length = std::min( GetCapacity() - GetLength(), buffer_length );
		while( written_length < max_length )
		{
			const size_t partition_length = std::min( GetWritePartitionLength(), max_length );
			ENSURES_DEBUG( partition_length > 0 );

			Black::CopyMemory( m_write_head, source_head, partition_length );
			written_length += partition_length;

			source_head += partition_length;
			CommitWriting( partition_length );
		}

		return written_length;
	}

	Black::PlainView<const std::byte> RingBuffer::WriteBuffer( Black::PlainView<const std::byte> buffer )
	{
		Black::PlainView<const std::byte> result;

		const size_t written_length = WriteBuffer( buffer.GetMemory(), buffer.GetLength() );
		CRET( written_length == 0, result );

		result = { buffer.GetMemory(), written_length };
		return result;
	}

	const size_t RingBuffer::ReadBuffer( Black::NotNull<void*> const buffer, const size_t buffer_length ) const
	{
		size_t readden_length = 0;
		CRET( IsEmpty(), readden_length );

		std::byte* dest_head = reinterpret_cast<std::byte*>( buffer.Get() );
		const size_t max_length = std::min( GetLength(), buffer_length );
		while( readden_length < max_length )
		{
			const size_t partition_length = std::min( GetReadPartitionLength(), max_length );
			ENSURES_DEBUG( partition_length > 0 );

			Black::CopyMemory( dest_head, m_read_head, partition_length );
			readden_length += partition_length;

			dest_head += partition_length;
			CommitReading( partition_length );
		}

		return readden_length;
	}

	Black::PlainView<std::byte> RingBuffer::ReadBuffer( Black::PlainView<std::byte> buffer ) const
	{
		Black::PlainView<std::byte> result;

		const size_t readden_length = ReadBuffer( buffer.GetMemory(), buffer.GetLength() );
		CRET( readden_length == 0, result );

		result = { buffer.GetMemory(), readden_length };
		return result;
	}

	void RingBuffer::CommitWriting( const size_t partition_length ) const
	{
		std::byte* new_write_head = m_write_head + partition_length;

		if( m_buffer.IsInside( new_write_head ) )
		{
			ENSURES_DEBUG( !m_is_wrapped || ( new_write_head <= m_read_head ) );

			m_write_head = new_write_head;
			return;
		}

		ENSURES_DEBUG( !m_is_wrapped && ( new_write_head == m_buffer.GetEnd() ) );

		m_is_wrapped = true;
		m_write_head = m_buffer.GetMemory();
	}

	void RingBuffer::CommitReading( const size_t partition_length ) const
	{
		std::byte* new_read_head = m_read_head + partition_length;

		if( m_buffer.IsInside( new_read_head ) )
		{
			ENSURES_DEBUG( m_is_wrapped || ( new_read_head <= m_write_head ) );

			m_read_head = new_read_head;
			return;
		}

		ENSURES_DEBUG( m_is_wrapped && ( new_read_head == m_buffer.GetEnd() ) );

		m_is_wrapped = false;
		m_read_head = m_buffer.GetMemory();
	}

	const size_t RingBuffer::GetWritePartitionLength() const
	{
		CRET( m_is_wrapped, m_read_head - m_write_head );

		return m_buffer.GetEnd() - m_write_head;
	}

	const size_t RingBuffer::GetReadPartitionLength() const
	{
		CRET( m_is_wrapped, m_buffer.GetEnd() - m_read_head );

		return m_write_head - m_read_head;
	}
}
}
}
}
