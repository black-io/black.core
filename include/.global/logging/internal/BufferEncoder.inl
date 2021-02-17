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
	inline std::string BufferEncoder::Decode( std::string value )
	{
		std::string result{ std::move( value ) };

		if constexpr( Black::BUILD_CONFIGURATION != Black::BuildMode::Debug )
		{
			for( size_t index = 0; index < result.size(); ++index )
			{
				result[ index ] = Encode( result[ index ], index );
			}
		}

		return result;
	}
}
}
}
}
}
