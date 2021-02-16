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
	//
	template< size_t BUFFER_LENGTH>
	class EncodedBuffer final
	{
	// Construction and initialization.
	public:
		constexpr EncodedBuffer()									= default;
		constexpr EncodedBuffer( const EncodedBuffer& other )		: EncodedBuffer{ other, std::make_index_sequence<BUFFER_LENGTH - 1>{} } {};
		constexpr EncodedBuffer( EncodedBuffer&& )					= delete;
		constexpr EncodedBuffer( const char* const source_string )	: EncodedBuffer{ source_string, std::make_index_sequence<BUFFER_LENGTH - 1>{} } {};

		EncodedBuffer& operator = ( const EncodedBuffer& )	= delete;
		EncodedBuffer& operator = ( EncodedBuffer&& )		= delete;

	// Public interface.
	public:
		//
		inline std::string GetDecodedBuffer() const			{ return BufferEncoder::Decode( { m_buffer } ); };

		//
		constexpr std::string_view GetEncodedBuffer() const	{ return m_buffer; };

		//
		constexpr const size_t GetLength() const			{ return BUFFER_LENGTH; };


		constexpr std::string_view operator * () const		{ return m_buffer; };

	// Private construction.
	private:
		template< size_t... INDICES >
		constexpr EncodedBuffer( const EncodedBuffer& other, std::index_sequence<INDICES...> )
			: m_buffer{ other.m_buffer[ INDICES ]..., 0 }
		{};

		template< size_t... INDICES >
		constexpr EncodedBuffer( const char* const source, std::index_sequence<INDICES...> )
			: m_buffer{ BufferEncoder::Encode( source[ INDICES ], INDICES )..., 0 }
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
