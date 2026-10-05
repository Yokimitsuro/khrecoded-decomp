#include "nitro/types.h"

typedef struct {
    u16 id;
    s16 x;
    s16 y;
} Record;

extern void func_ov027_020b824c(void *pool, Record *record, s16 x, s16 y);

u16 DrawDigitRecords(void *pool, Record **digits, u32 value, int offsetY)
{
    u16 x = digits[0]->x;
    u16 count = 0;
    s16 y = (u16)(digits[0]->y + offsetY);

    do {
        func_ov027_020b824c(pool, digits[value % 10], x, y);
        x -= 2;
        value /= 10;
        count++;
    } while (count < 6 && value != 0);
    return x;
}

