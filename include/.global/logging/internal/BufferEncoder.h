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
	struct BufferEncoder final
	{
		//
		static constexpr char Encode( const char symbol, const size_t salt )
		{
			if constexpr( Black::BUILD_CONFIGURATION == Black::BuildMode::Release )
			{
				// Shuffled prime numbers.
				constexpr uint8_t keys[]{
					173U, 179U, 223U, 157U, 193U, 199U, 167U, 149U, 241U, 229U, 251U, 163U,
					181U, 139U, 233U, 239U, 191U, 211U, 131U, 137U, 227U, 197U, 151U,
				};

				return symbol ^ keys[ salt % std::size( keys ) ];
			}
			else
			{
				return symbol;
			}
		}

		//
		static inline std::string Decode( std::string value );
	};
}
}
}
}
}
