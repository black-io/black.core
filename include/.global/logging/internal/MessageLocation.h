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
		@brief	Logging message location adapter.

		The location of log messages is required to be uniquely identified in the logging core.
		This adapter is used for purposes of such registration. In addition, the adapter implements the assess to registered data via given unique ID.

		Each logging location is created from:
		* the function name, where the logging is used.
		* the source code file path, where the logging is used.
		* the source code line number, where the logging occurs.

		All the parts creates the unique identification number of unique logging location.
		Constructed logging location is known by the logging core, so there is no needs to provide all logging messages with the information of location.
		Only unique id of logging location is required in entries of log message.

		@tparam	BUILD_CONFIGURATION	Build configuration to specify the functionality of adapter.
	*/
	template< Black::BuildMode BUILD_CONFIGURATION >
	class MessageLocation final
	{
	// Construction and initialization.
	public:
		inline MessageLocation( std::string_view function_name, std::string_view file_path, const size_t file_line );

	// Public interface.
	public:
		/// @brief	Get the encoded string of function name.
		inline std::string_view GetRawFunctionName() const;

		/// @brief	Get the encoded string of source code file path.
		inline std::string_view GetRawFilePath() const;

		/// @brief	Get the decoded (original) string of function name.
		inline std::string GetFunctionName() const;

		/// @brief	Get the decoded (original) string of source code file path.
		inline std::string GetFilePath() const;

		/// @brief	Get the line number of source code file.
		inline const size_t GetFileLine() const;


		/// @brief	Get the unique ID of location.
		inline const LocationId GetId() const		{ return m_id; };


		inline const LocationId operator * () const	{ return m_id; };

	// Private state.
	private:
		const LocationId m_id; // Unique id for hosted combination of function, file and line.
	};

	// The selection variant for Debug build configuration. It includes some additional fields.
	template<>
	class MessageLocation<Black::BuildMode::Debug> final
	{
	// Construction and initialization.
	public:
		inline MessageLocation( std::string_view function_name, std::string_view file_path, const size_t file_line );

	// Public interface.
	public:
		/// @brief	Get the encoded string of function name.
		inline std::string_view GetRawFunctionName() const	{ return m_function_name; };

		/// @brief	Get the encoded string of source code file path.
		inline std::string_view GetRawFilePath() const		{ return m_file_path; };

		/// @brief	Get the decoded (original) string of function name.
		inline std::string GetFunctionName() const			{ return BufferEncoder::Decode( std::string{ m_function_name } ); };

		/// @brief	Get the decoded (original) string of source code file path.
		inline std::string GetFilePath() const				{ return BufferEncoder::Decode( std::string{ m_file_path } ); };

		/// @brief	Get the line number of source code file.
		inline const size_t GetFileLine() const				{ return m_file_line; };


		/// @brief	Get the unique ID of location.
		inline const LocationId GetId() const				{ return m_id; };


		inline const LocationId operator * () const			{ return m_id; };

	// Private state.
	private:
		const std::string_view	m_function_name;	// The name of located function.
		const std::string_view	m_file_path;		// The path of source code file.
		const size_t			m_file_line;		// Located line in source code.
		const LocationId		m_id;				// Unique id for hosted combination of function, file and line.
	};
}
}
}
}
}
