#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
	template< typename TWriteFunction >
	inline Black::BooleanStatus RingBuffer::PerformWriteTransaction( TWriteFunction&& write_function )
	{
		static_assert(
			std::is_invocable_r_v<std::optional<Black::PlainView<std::byte>>, TWriteFunction, Black::PlainView<std::byte>>,
			"TWriteFunction should satisfy the signature: std::optional<Black::PlainView<std::byte>> ( Black::PlainView<std::byte> )."
		);

		CRET( !IsValid() || IsFull(), Black::BooleanStatus::Failure );

		while( !IsFull() )
		{
			const size_t partition_length = GetWritePartitionLength();
			ENSURES_DEBUG( partition_length > 0 );

			std::optional<Black::PlainView<std::byte>> write_result{
				write_function( { m_write_head, partition_length } )
			};
			CRET( !write_result.has_value(), Black::BooleanStatus::Failure );

			Black::PlainView<std::byte> written_partition{ *write_result };
			CRET( written_partition.IsEmpty(), Black::BooleanStatus::Success );

			CommitWriting( written_partition.GetLength() );
			CBRK( written_partition.GetLength() < partition_length );
		}

		return Black::BooleanStatus::Success;
	}
}
}
}
}
