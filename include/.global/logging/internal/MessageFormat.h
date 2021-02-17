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
	template< Black::BuildMode BUILD_CONFIGURATION >
	class MessageFormat final
	{
	// Construction and initialization.
	public:
		inline MessageFormat( std::string_view format );

	// Public interface.
	public:
		//
		inline std::string_view GetRawFormat() const;

		//
		inline std::string GetFormat() const;


		//
		inline const FormatId GetId() const { return m_id; };

	// Private state.
	private:
		const FormatId m_id; // Unique id for hosted log format.
	};

	//
	template<>
	class MessageFormat<Black::BuildMode::Debug> final
	{
	// Construction and initialization.
	public:
		inline MessageFormat( std::string_view format );

	// Public interface.
	public:
		//
		inline std::string_view GetRawFormat() const	{ return m_format; };

		//
		inline std::string GetFormat() const			{ return BufferEncoder::Decode( std::string{ m_format } ); };


		//
		inline const FormatId GetId() const				{ return m_id; };

	// Private state.
	private:
		const std::string_view	m_format;	// Hosted format.
		const FormatId			m_id;		// Unique id for hosted log format.
	};
}
}
}
}
}
