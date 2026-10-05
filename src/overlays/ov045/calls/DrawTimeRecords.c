#include "nitro/types.h"

typedef struct {
    u16 id;
    s16 x;
    s16 y;
} Record;

extern void func_ov027_020b824c(void *pool, Record *record, s16 x, s16 y);

u16 DrawTimeRecords(void *pool, Record **digits, u32 value, int offsetY)
{
    u16 base;
    s16 y;
    Record *first = digits[0];
    u16 x = first->x;
    u16 count = 0;

    value /= 10;
    y = (u16)(first->y + offsetY);
    do {
        base = (count == 3) ? 6 : 10;
        func_ov027_020b824c(pool, digits[value % base], x, y);
        x -= 2;
        value /= base;
        if (count == 1 || count == 3) {
            func_ov027_020b824c(pool, digits[11], x + 1, y);
            x -= 1;
        }
        count++;
    } while (count < 6);
    return x;
}



