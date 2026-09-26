typedef unsigned int u32;
u32 func_0202d4d8(u32 *base, u32 bitOffset, u32 bitCount)
{
    u32 result = 0;
    u32 mask;
    u32 n;
    base += (int)bitOffset / 32;
    bitOffset &= 0x1f;
    if ((int)(bitOffset + bitCount) > 0x20) {
        do {
            n = 0x20 - bitOffset;
            mask = (n == 0x20) ? 0xffffffff : (1u << n) - 1;
            bitCount -= n;
            result = (*base++ & mask) | (result << n);
            bitOffset = 0;
        } while ((int)bitCount > 0x20);
    }
    if ((int)bitCount > 0) {
        mask = (bitCount == 0x20) ? 0xffffffff : (1u << bitCount) - 1;
        result = (mask & (*base >> ((0x20 - bitOffset) - bitCount))) | (result << bitCount);
    }
    return result;
}
