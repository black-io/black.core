#pragma once


namespace Black
{
	template< PlatformEndianness ENDIANNESS >
	constexpr uint32_t GetPackedBytes( const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4 )
	{
		union
		{
			uint8_t		bytes[4];
			uint32_t	value;
		} pack = { b1, b2, b3, b4 };

		CRET( ENDIANNESS == BUILD_ENDIANNESS, pack.value; );

		if( ENDIANNESS == PlatformEndianness::LittleEndian )
		{
			pack.bytes[0] = b1;
			pack.bytes[1] = b2;
			pack.bytes[2] = b3;
			pack.bytes[3] = b4;
			return pack.value;
		}
		else if( ENDIANNESS == PlatformEndianness::BigEndian )
		{
			pack.bytes[0] = b4;
			pack.bytes[1] = b3;
			pack.bytes[2] = b2;
			pack.bytes[3] = b1;
			return pack.value;
		}

		return 0;
	}

	template< PlatformEndianness ENDIANNESS >
	constexpr uint32_t GetPackedBytes(
		const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4,
		const uint8_t b5, const uint8_t b6, const uint8_t b7, const uint8_t b8
	)
	{
		union
		{
			uint8_t		bytes[8];
			uint64_t	value;
		} pack = { b1, b2, b3, b4, b5, b6, b7, b8 };

		CRET( ENDIANNESS == BUILD_ENDIANNESS, pack.value; );

		if( ENDIANNESS == PlatformEndianness::LittleEndian )
		{
			pack.bytes[0] = b1;
			pack.bytes[1] = b2;
			pack.bytes[2] = b3;
			pack.bytes[3] = b4;
			pack.bytes[4] = b5;
			pack.bytes[5] = b6;
			pack.bytes[6] = b7;
			pack.bytes[7] = b8;
			return pack.value;
		}
		else if( ENDIANNESS == PlatformEndianness::BigEndian )
		{
			pack.bytes[0] = b8;
			pack.bytes[1] = b7;
			pack.bytes[2] = b6;
			pack.bytes[3] = b5;
			pack.bytes[4] = b4;
			pack.bytes[5] = b3;
			pack.bytes[6] = b2;
			pack.bytes[7] = b1;
			return pack.value;
		}

		return 0;
	}
}
