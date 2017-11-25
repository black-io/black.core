#pragma once


namespace Black
{
	template< PlatformEndianness ENDIANNESS >
	constexpr uint32_t GetPackedBytes( const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4 )
	{
		union
		{
			uint32_t	value;
			uint8_t		bytes[4];
		} pack;

		switch( ENDIANNESS )
		{
		case PlatformEndianness::LittleEndian:
			pack.bytes[0] = b1;
			pack.bytes[1] = b2;
			pack.bytes[2] = b3;
			pack.bytes[3] = b4;
			break;
		case PlatformEndianness::BigEndian:
			pack.bytes[0] = b4;
			pack.bytes[1] = b3;
			pack.bytes[2] = b2;
			pack.bytes[3] = b1;
			break;
		default:
			pack.value = 0;
			break;
		}

		return pack.value;
	}

	template< PlatformEndianness ENDIANNESS >
	constexpr uint64_t GetPackedBytes(
		const uint8_t b1, const uint8_t b2, const uint8_t b3, const uint8_t b4,
		const uint8_t b5, const uint8_t b6, const uint8_t b7, const uint8_t b8
	)
	{
		union
		{
			uint64_t	value;
			uint8_t		bytes[8];
		} pack;

		switch( ENDIANNESS )
		{
		case PlatformEndianness::LittleEndian:
			pack.bytes[0] = b1;
			pack.bytes[1] = b2;
			pack.bytes[2] = b3;
			pack.bytes[3] = b4;
			pack.bytes[4] = b5;
			pack.bytes[5] = b6;
			pack.bytes[6] = b7;
			pack.bytes[7] = b8;
			break;
		case PlatformEndianness::BigEndian:
			pack.bytes[0] = b8;
			pack.bytes[1] = b7;
			pack.bytes[2] = b6;
			pack.bytes[3] = b5;
			pack.bytes[4] = b4;
			pack.bytes[5] = b3;
			pack.bytes[6] = b2;
			pack.bytes[7] = b1;
			break;
		default:
			pack.value = 0;
			break;
		}

		return pack.value;
	}
}
