typedef unsigned short u16;

u16 NNSi_G2dSplitCharUTF16(const void **ppChar)
{
    const u16 *pChar = *ppChar;
    u16 c = *pChar++;
    *ppChar = pChar;
    return c;
}
