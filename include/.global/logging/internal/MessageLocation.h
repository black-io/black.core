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
	class MessageLocation final
	{
	// Construction and initialization.
	public:
		MessageLocation() = default;
		MessageLocation( std::string_view function_name, std::string_view file_path, const size_t file_line );

	// Public interface.
	public:
		//
		inline std::string GetFunctionName() const;

		//
		inline std::string GetFilePath() const;

		//
		inline const size_t GetFileLine() const;


		//
		inline const LocationId GetId() const { return m_id; };

	// Private state.
	private:
		const LocationId m_id; // Unique id for hosted combination of function, file and line.
	};

	//
	template<>
	class MessageLocation<Black::BuildMode::Debug> final
	{
	// Construction and initialization.
	public:
		MessageLocation() = default;
		MessageLocation( std::string_view function_name, std::string_view file_path, const size_t file_line );

	// Public interface.
	public:
		//
		inline std::string GetFunctionName() const		{ return BufferEncoder::Decode( std::string{ m_function_name } ); };

		//
		inline std::string GetFilePath() const			{ return BufferEncoder::Decode( std::string{ m_file_path } ); };

		//
		inline const size_t GetFileLine() const			{ return m_file_line; };


		//
		inline const LocationId GetId() const			{ return m_id; };

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
