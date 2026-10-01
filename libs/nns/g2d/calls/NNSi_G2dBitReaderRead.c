typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;

typedef struct NNSiG2dBitReader {
    const u8 *src;
    s8 availableBits;
    u8 bits;
} NNSiG2dBitReader;

static inline void BitReaderReload(NNSiG2dBitReader *reader)
{
    reader->bits = *reader->src++;
    reader->availableBits = 8;
}

u32 NNSi_G2dBitReaderRead(NNSiG2dBitReader *reader, int nBits)
{
    u32 value = reader->bits;
    int availableBits = reader->availableBits;

    if (availableBits < nBits) {
        int missingBits = nBits - availableBits;
        value <<= missingBits;
        BitReaderReload(reader);
        value |= NNSi_G2dBitReaderRead(reader, missingBits);
    } else {
        value >>= availableBits - nBits;
        reader->availableBits = (s8)(availableBits - nBits);
    }

    value &= 0xff >> (8 - nBits);
    return value;
}