#pragma thumb on

#include "nitro/types.h"

extern void func_0202d72c(s64 value, int precision, char *pIntText, char *pFracText);

static inline void WidenText(u16 *pDst, const char *pSrc)
{
    while (*pSrc != 0) {
        *pDst++ = *pSrc++;
    }
    *pDst = 0;
}

void Fx64_FormatWide(s64 value, int precision, u16 *pIntOut, u16 *pFracOut)
{
    char aIntText[26];
    char aFracText[14];

    func_0202d72c(value, precision, aIntText, aFracText);
    WidenText(pIntOut, aIntText);
    WidenText(pFracOut, aFracText);
}
