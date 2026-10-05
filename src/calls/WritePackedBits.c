typedef unsigned int u32;
void WritePackedBits(u32 *base, u32 bitOffset, u32 bitCount, u32 value)
{
    u32 mask;
    u32 n;
    base += (int)bitOffset / 32;
    bitOffset &= 0x1f;
    if ((int)(bitOffset + bitCount) > 0x20) {
        do {
            n = 0x20 - bitOffset;
            mask = (n == 0x20) ? 0xffffffff : (1u << n) - 1;
            bitCount -= n;
            *base = (*base & ~mask) | (mask & (value >> bitCount));
            base++;
            bitOffset = 0;
        } while ((int)bitCount > 0x20);
    }
    if ((int)bitCount > 0) {
        mask = (bitCount == 0x20) ? 0xffffffff : (1u << bitCount) - 1;
        n = (0x20 - bitOffset) - bitCount;
        *base = (*base & ~(mask << n)) | ((value & mask) << n);
    }
}
