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
		@brief	Log message identification type.

		Values of this type are unique for each log messages. So one message can be identified by its id.
	*/
	enum class MessageId : uint32_t;

	/**
		@brief	Message location identification type.

		The unique message location will always have unique id.
	*/
	enum class LocationId : uint32_t;

	/**
		@brief	Logging channel identification type.

		The unique message location will always have unique id.
	*/
	enum class ChannelId : uint32_t;

	/**
		@brief	Message format identification type.

		The unique message location will always have unique id.
	*/
	enum class FormatId : uint32_t;

	/**
		@brief	Log message category.

		Each log message is qualified by category.
		Some categories may be suppressed in certain build configurations.
	*/
	enum class MessageCategory : uint32_t
	{
		Fatal		= 0x01U,	// Most critical log message. Commonly, future execution of program becomes impossible.
		Critical	= 0x02U,	// Critical log message. Program will be safely finished.
		Error		= 0x04U,	// Subprogram error message. Subprogram will be finished, future program execution will be determined after it.
		Warning		= 0x08U,	// Soft subprogram warning, future program execution not affected.
		Info		= 0x10U,	// Information message. Used for information reports.
		Verbose		= 0x20U,	// Detailed information report. May be used to show work-flow process.
		Debug		= 0x40U,	// Debug message. Will be appearing only in debug mode and omitted in release.
	};

	/**
		@brief	Log writer status.
		Assigned log writer can report its status via values of this enumeration.
	*/
	enum class WriterStstus : uint8_t
	{
		Invalid	= 0,	// Log writer is broken, output stream is not ready. Needs to re-open log writer.
		Closed,			// Output stream is closed currently.
		Opened,			// Output stream opened and ready for receiving messages.
		Disabled,		// Output stream opened, but writer don't accept messages.
	};
}
}
}
}
}
