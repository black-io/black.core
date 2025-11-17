#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Types
{
	/**
		@brief	Implementation of regular ring buffer.

		AKA circular buffer, circular queue, cyclic buffer.
		Overview: https://en.wikipedia.org/wiki/Circular_buffer

		This buffer does not own or control the underlying memory buffer. It just organize the data in buffer.
		Each time the buffer is re-initialized, the data stored before initialization considered lost.
		Ring buffer can't be copied, but may be moved or invalidated using default-initialized other object.
	*/
	class RingBuffer final : private Black::NonCopyable
	{
	// Friendship declarations.
	public:
		// Allow swapping of buffers.
		friend void swap( RingBuffer& left, RingBuffer& right ) { left.Swap( right ); };

	// Public lifetime management.
	public:
		RingBuffer() noexcept;
		RingBuffer( RingBuffer&& other ) noexcept;
		~RingBuffer() noexcept;

		explicit RingBuffer( Black::PlainView<std::byte> buffer ) noexcept;


		RingBuffer& operator = ( RingBuffer&& other ) noexcept;

	// Public interface.
	public:
		// Rewind the buffer. All previously stored data will be lost.
		void Rewind();

		// Swap the state of this buffer with other buffer.
		void Swap( RingBuffer& other );


		/**
			@brief	Store the data from given `buffer` with given `length`.

			@param	buffer			The source buffer with data to be stored.
			@param	buffer_length	Length of given `buffer`.
			@return					The value returned is the size of stored data.
		*/
		const size_t WriteBuffer( Black::NotNull<const void*> buffer, const size_t buffer_length );

		/**
			@brief	Store the data from given `buffer`.

			@param	buffer	The source buffer with data to be stored.
			@return			The value returned is partition of `buffer` with data that was stored.
		*/
		Black::PlainView<const std::byte> WriteBuffer( Black::PlainView<const std::byte> buffer );

		/**
			@brief	Feed the given `buffer` of given `length` with stored data.

			@param	buffer			The buffer to be filled with stored data.
			@param	buffer_length	Length of given `buffer`.
			@return					The value returned is the length of stored in `buffer` data.
		*/
		const size_t ReadBuffer( Black::NotNull<void*> const buffer, const size_t buffer_length ) const;

		/**
			@brief	Feed the given `buffer` with stored data.

			@param	buffer	The buffer to be filled with stored data.
			@return			The value returned is partition of `buffer` filled with data.
		*/
		Black::PlainView<std::byte> ReadBuffer( Black::PlainView<std::byte> buffer ) const;

		/**
			@brief	Feed the given `buffer` of given `length` with stored data.

			Instead of `ReadBuffer` method, this one does not shift the buffer.
			One should use `ReadBuffer` or `SkipUnreadLength` methods to

			@param	buffer			The buffer to be filled with stored data.
			@param	buffer_length	Length of given `buffer`.
			@return					The value returned is the length of stored in `buffer` data.
		*/
		const size_t PeekBuffer( Black::NotNull<void*> const buffer, const size_t buffer_length ) const;

		/**
			@brief	Feed the given `buffer` with stored data.

			Instead of `ReadBuffer` method, this one does not shift the buffer.
			One should use `ReadBuffer` or `SkipUnreadLength` methods to

			@param	buffer	The buffer to be filled with stored data.
			@return			The value returned is partition of `buffer` filled with data.
		*/
		Black::PlainView<std::byte> PeekBuffer( Black::PlainView<std::byte> buffer ) const;

		// Skip the unread length of bytes.
		void SkipUnreadLength( const size_t unread_length );

		/**
			@brief	Perform the transaction of writing the solid partition of data into buffer.

			This method allows user of ring buffer use solid partition of buffer memory to perform the write operation.
			Commonly this method helps to directly read from streams to ring buffer.

			This method predicts the continuous write. `write_function` may be repeatedly called if given memory view filled completely in last call.
			Method expects the `write_function` to satisfy the common signature: `std::optional<Black::PlainView<std::byte>> ( Black::PlainView<std::byte> )`.
			Ring buffer will use the view of its solid memory partition as argument of `write_function`.
			Ring buffer expects the `write_function` will return empty optional as sign of no memory was written to partition.

			In case of `write_function` fills some memory of partition, it should return view of filled memory as its result.
			Ring buffer will use this view to commit the write operation.

			@tparam	TWriteFunction	Type of function, commonly similar to .
			@param	write_function	This function will be used to fill the given to it memory view with desired data.
			@return					`Success` if transaction committed at the end. `Failure` in other cases.
		*/
		template< typename TWriteFunction >
		inline Black::BooleanStatus PerformWriteTransaction( TWriteFunction&& write_function );


		// Get the total capacity of buffer.
		inline const size_t GetCapacity() const	{ return m_buffer.GetLength(); };

		// Get the length of stored data.
		inline const size_t GetLength() const	{ return ( m_is_wrapped )? GetWrappedLength() : GetStraightLength(); };


		// Whether the buffer can read or write the data.
		inline const bool IsValid() const	{ return !m_buffer.IsEmpty(); };

		// Whether the buffer contains no data.
		inline const bool IsEmpty() const	{ return !m_is_wrapped && ( m_read_head == m_write_head ); };

		// Whether the buffer totally filled with data.
		inline const bool IsFull() const	{ return m_is_wrapped && ( m_read_head == m_write_head ); };

		// Whether the data can be readden from buffer.
		inline const bool CanRead() const	{ return IsValid() && GetLength() > 0; };

		// Whether the data can be stored in buffer.
		inline const bool CanWrite() const	{ return IsValid() && GetLength() < GetCapacity(); };

	// Private interface.
	private:
		// Commit the writing of stored partition with given length.
		void CommitWriting( const size_t partition_length ) const;

		// Commit the reading of stored partition with given length.
		void CommitReading( const size_t partition_length ) const;


		// Get the length of next contiguous partition for reading.
		const size_t GetWritePartitionLength() const;

		// Get the length of next contiguous partition for reading.
		const size_t GetReadPartitionLength() const;


		// Get the length of stored data in straight buffer.
		inline const size_t GetStraightLength() const	{ return m_write_head - m_read_head; };

		// Get the length of stored data in wrapped around buffer.
		inline const size_t GetWrappedLength() const	{ return m_buffer.GetLength() - ( m_read_head - m_write_head ); };

	// Private state.
	private:
		Black::PlainView<std::byte>	m_buffer;	// Buffer to store the data.

	// Private non-state.
	private:
		mutable std::byte*	m_write_head	= nullptr;	// Head of next write operation.
		mutable std::byte*	m_read_head		= nullptr;	// Head of next read operation.
		mutable bool		m_is_wrapped	= false;	// Whether the data stored in buffer wraps around the end of buffer.
	};
}
}
}
}
