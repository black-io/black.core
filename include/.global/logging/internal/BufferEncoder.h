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
		@brief	String obfuscation codec for logging subsystem.

		This type designed to be used on compile-time.
	*/
	struct BufferEncoder final
	{
		/**
			@breif	Encode the input symbol using the given salt.

			The function may be used at compile-time.

			@param	symbol	The symbol to be encoded.
			@param	salt	The salt to mix with the value of given symbol.
			@return			The value returned is an encoded symbol.
		*/
		static constexpr char Encode( const char symbol, const size_t salt )
		{
			if constexpr( Black::BUILD_CONFIGURATION == Black::BuildMode::Debug )
			{
				// No obfuscation in debug builds.
				return symbol;
			}
			else
			{
				// Shuffled prime numbers. May be changed freely to get the unique result of obfuscation.
				constexpr uint8_t keys[]{
					173U, 179U, 223U, 157U, 193U, 199U, 167U, 149U, 241U, 229U, 251U, 163U,
					181U, 139U, 233U, 239U, 191U, 211U, 131U, 137U, 227U, 197U, 151U,
				};

				return symbol ^ keys[ salt % std::size( keys ) ];
			}
		}

		/**
			@brief	Decode the obfuscated string.

			This function may be used only in runtime.

			@param	value	Encoded string to be decoded. Accepted by value for purposes of zero-allocation inside.
			@return			The value returned is an decoded string.
		*/
		static inline std::string Decode( std::string value );
	};
}
}
}
}
}
