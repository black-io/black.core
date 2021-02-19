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
		@brief	Logging message format adapter.

		The format of log messages is required to be uniquely identified in the logging core.
		This adapter is used for purposes of such registration. In addition, the adapter implements the assess to registered data via given unique ID.

		@tparam	BUILD_CONFIGURATION	Build configuration to specify the functionality of adapter.
	*/
	template< Black::BuildMode BUILD_CONFIGURATION >
	class MessageFormat final
	{
	// Construction and initialization.
	public:
		inline MessageFormat( std::string_view format );

	// Public interface.
	public:
		/// @brief	Get the encoded string of logging format.
		inline std::string_view GetRawFormat() const;

		/// @brief	Get the decoded (original) string of logging format.
		inline std::string GetFormat() const;


		/// @brief	Get the unique ID of channel.
		inline const FormatId GetId() const			{ return m_id; };


		inline const FormatId operator * () const	{ return m_id; };

	// Private state.
	private:
		const FormatId m_id; // Unique id for hosted log format.
	};

	// The selection variant for Debug build configuration. It includes some additional fields.
	template<>
	class MessageFormat<Black::BuildMode::Debug> final
	{
	// Construction and initialization.
	public:
		inline MessageFormat( std::string_view format );

	// Public interface.
	public:
		/// @brief	Get the encoded string of logging format.
		inline std::string_view GetRawFormat() const	{ return m_format; };

		/// @brief	Get the decoded (original) string of logging format.
		inline std::string GetFormat() const			{ return BufferEncoder::Decode( std::string{ m_format } ); };


		/// @brief	Get the unique ID of channel.
		inline const FormatId GetId() const				{ return m_id; };


		inline const FormatId operator * () const		{ return m_id; };

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
