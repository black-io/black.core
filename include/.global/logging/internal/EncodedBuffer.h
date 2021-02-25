#pragma once


namespace Black
{
inline namespace Core
{
inline namespace Global
{
inline namespace Logging
{
namespace Internal
{
	/**
		@brief	Static-length string buffer with compile-time encoding.

		This buffer stores only valuable string data. It does not tore the terminating symbol.
		It is very useful for compile-time string obfuscation.

		@tparam	BUFFER_LENGTH	Length of internal buffer for string.
	*/
	template< size_t BUFFER_LENGTH >
	class EncodedBuffer final
	{
	// Construction and initialization.
	public:
		constexpr EncodedBuffer()									= default;
		constexpr EncodedBuffer( const EncodedBuffer& other )		: EncodedBuffer{ other, std::make_index_sequence<BUFFER_LENGTH>{} } {};
		constexpr EncodedBuffer( EncodedBuffer&& )					= delete;
		constexpr EncodedBuffer( const char* const source_string )	: EncodedBuffer{ source_string, std::make_index_sequence<BUFFER_LENGTH>{} } {};

		EncodedBuffer& operator = ( const EncodedBuffer& )	= delete;
		EncodedBuffer& operator = ( EncodedBuffer&& )		= delete;

	// Public interface.
	public:
		/// @brief	Get the decoded string.
		inline std::string GetDecodedBuffer() const			{ return BufferEncoder::Decode( std::string{ m_buffer, BUFFER_LENGTH } ); };

		/// @brief	Get the string directly from buffer with encoded data.
		constexpr std::string_view GetEncodedBuffer() const	{ return std::string_view{ m_buffer, BUFFER_LENGTH }; };

		/// @breif	Get the length of buffer.
		constexpr const size_t GetLength() const			{ return BUFFER_LENGTH; };


		constexpr std::string_view operator * () const		{ return GetEncodedBuffer(); };

	// Private construction.
	private:
		template< size_t... INDICES >
		constexpr EncodedBuffer( const EncodedBuffer& other, std::index_sequence<INDICES...> )
			: m_buffer{ other.m_buffer[ INDICES ]... }
		{};

		template< size_t... INDICES >
		constexpr EncodedBuffer( const char* const source, std::index_sequence<INDICES...> )
			: m_buffer{ BufferEncoder::Encode( source[ INDICES ], INDICES )... }
		{};

	// Private state.
	private:
		const char m_buffer[ BUFFER_LENGTH ]{}; // Buffer for hosted encoded string.
	};
}
}
}
}
}
