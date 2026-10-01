typedef unsigned long u32;
typedef unsigned char u8;

u32 ROMUtil_CRC32(void *buffer, u32 size)
{
    u32 crc;
    u32 polynomial;
    u8 *bytes;

    bytes = (u8 *)buffer;
    crc = 0xffffffff;
    polynomial = 0xedb88320;
    while (size-- != 0) {
        crc ^= *bytes++;
        if (crc & 1) { crc >>= 1; } else { crc = polynomial ^ (crc >> 1); }
        if (crc & 1) { crc >>= 1; } else { crc = polynomial ^ (crc >> 1); }
        if (crc & 1) { crc >>= 1; } else { crc = polynomial ^ (crc >> 1); }
        if (crc & 1) { crc >>= 1; } else { crc = polynomial ^ (crc >> 1); }
        if (crc & 1) { crc >>= 1; } else { crc = polynomial ^ (crc >> 1); }
        if (crc & 1) { crc >>= 1; } else { crc = polynomial ^ (crc >> 1); }
        if (crc & 1) { crc >>= 1; } else { crc = polynomial ^ (crc >> 1); }
        if (crc & 1) { crc >>= 1; } else { crc = polynomial ^ (crc >> 1); }
    }

    return ~crc;
}