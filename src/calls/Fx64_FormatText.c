#pragma thumb on

#include "nitro/types.h"

extern s64 _ll_sdiv(s64 numerator, s64 denom);
extern void MI_CpuFill8(void *dest, unsigned char data, u32 size);

static inline void ReverseText(char *pText, int nLen)
{
    char *pHead;
    char *pTail;

    pText[nLen] = 0;
    if (nLen >= 2) {
        for (pHead = pText, pTail = pText + nLen - 1; pHead < pTail; pHead++, pTail--) {
            char c = *pHead;
            *pHead = *pTail;
            *pTail = c;
        }
    }
}

void Fx64_FormatText(s64 value, int precision, char *pIntText, char *pFracText)
{
    s64 ipart = value >> 12;
    u32 frac = (u32)value & 0xfff;
    int len = 0;

    if ((ipart >> 32) == 0) {
        u32 n = (u32)ipart;

        while (n != 0) {
            u32 q = n / 10;

            pIntText[len] = (char)(n - q * 10 + '0');
            n = q;
            len++;
        }
    } else {
        while (ipart != 0) {
            s64 q = _ll_sdiv(ipart, 10);

            pIntText[len] = (char)((int)(ipart - q * 10) + '0');
            ipart = q;
            len++;
        }
    }
    if (len == 0) {
        pIntText[len] = '0';
        len++;
    }
    ReverseText(pIntText, len);

    if (precision > 0) {
        u32 n;
        int i;

        MI_CpuFill8(pFracText, '0', 13);
        n = ((frac & 0xf) * 100000000 >> 12) +
            ((((frac & 0xf00) >> 8) * 100000000 >> 4) + (((frac & 0xf0) >> 4) * 100000000 >> 8)) +
            100000000;
        for (i = 0; i < 8; i++) {
            u32 q = n / 10;

            pFracText[i] = (char)(n - q * 10 + '0');
            n = q;
        }
        pFracText[i] = 0;
        if (i >= 2) {
            char *pHead;
            char *pTail;

            for (pHead = pFracText, pTail = pFracText + i - 1; pHead < pTail; pHead++, pTail--) {
                char c = *pHead;
                *pHead = *pTail;
                *pTail = c;
            }
        }
    }
    pFracText[precision] = 0;
}
