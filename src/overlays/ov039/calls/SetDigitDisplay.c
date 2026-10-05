#include "nitro/types.h"

typedef struct {
    int x;
    int y;
} DigitPos;

extern void IndexedRecords_SetFlag2(void *cells, int index, int value);
extern void func_0204f218(void *cells, int index, int value);
extern void IndexedRecord_SetPair(void *cells, int index, DigitPos *pos);

void SetDigitDisplay(void *cells, int first, int value, DigitPos *origin)
{
    DigitPos pos;
    BOOL visible;
    s16 digit;
    s16 index;

    if (origin != 0) {
        pos = *origin;
    }
    digit = 0;
    index = first;
    do {
        if (value >= 0 && (digit == 0 || value != 0)) {
            visible = TRUE;
        } else {
            visible = FALSE;
        }
        IndexedRecords_SetFlag2(cells, index, visible);
        if (visible) {
            func_0204f218(cells, index, (u16)(value % 10));
        }
        if (origin != 0) {
            IndexedRecord_SetPair(cells, index, &pos);
            pos.x -= 0x7000;
        }
        value /= 10;
        digit++;
        index++;
    } while (digit < 6);
}
