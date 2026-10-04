typedef unsigned int u32;
typedef unsigned long long u64;

#define CHARACTER_WIDTH 8
#define CHARACTER_HEIGHT 8

extern void MIi_CpuClearFast(u32 data, void *destp, u32 size);
static inline void MI_CpuFillFast(void *dest, u32 data, u32 size)
{
    MIi_CpuClearFast(data, dest, size);
}
void ClearChar (void * pChar, int x, int y, int w, int h, u32 cl8, int bpp)
{

    if ((w == CHARACTER_WIDTH) && (h == CHARACTER_HEIGHT)) {
        MI_CpuFillFast(pChar, cl8, (u32)(8 * bpp));
    } else {
        if ( bpp == 4 ) {
            u32 mask;
            u32 data;
            u32 * pLine;
            u32 * pLineEnd;

            {
                u32 x4 = (unsigned int)x * 4;
                u32 rw4 = 32 - (w * 4 + x4);

                mask = (u32)(~0) >> x4;
                mask <<= x4 + rw4;
                mask >>= rw4;

                data = cl8 & mask;
                mask = ~mask;
            }

            pLine = (u32 *)pChar + y;
            pLineEnd = pLine + h;
            for ( ; pLine < pLineEnd; pLine++) {
                *pLine = (*pLine & mask) | data;
            }
        } else {
            u32 mask_0, mask_1;
            u32 data_0, data_1;

            {
                u32 x8 = (unsigned int)x * 8;
                u32 rw8 = 64 - (w * 8 + x8);

                mask_0 = (u32)(~0) >> x8;
                if ( rw8 >= 32 ) {
                    const u32 rw32 = rw8 - 32;
                    mask_0 <<= (x8 + rw32);
                    mask_0 >>= rw32;
                } else {
                    mask_0 <<= x8;
                }

                mask_1 = (u32)(~0) << rw8;
                if ( x8 >= 32 ) {
                    const u32 x32 = x8 - 32;
                    mask_1 >>= (x32 + rw8);
                    mask_1 <<= x32;
                } else {
                    mask_1 >>= rw8;
                }

                data_0 = cl8 & mask_0;
                data_1 = cl8 & mask_1;

                mask_0 = ~mask_0;
                mask_1 = ~mask_1;
            }

            {
                u32 * pLine = (u32 *)((u64 *)pChar + y);
                u32 * const pLineEnd = (u32 *)((u64 *)pLine + h);

                while ( pLine < pLineEnd ) {
                    *pLine = (*pLine & mask_0) | data_0;
                    pLine++;
                    *pLine = (*pLine & mask_1) | data_1;
                    pLine++;
                }
            }
        }
    }
}
