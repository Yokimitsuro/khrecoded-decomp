#include "nitro/types.h"

typedef struct {
    int x;
    int y;
} DigitPos;

extern void *FindWidgetById(void *root, int id);
extern DigitPos *func_ov027_020b91c8(void *root, void *widget);
extern int PXI_Init_0204f0c8(void *cells, int key, int flags);
extern void IndexedRecord_ClearActive(void *cells, int index);
extern void func_0204f218(void *cells, int index, int value);
extern void IndexedRecord_SetPair(void *cells, int index, DigitPos *pos);
extern void IndexedRecords_SetFlag2(void *cells, int index, int value);

s16 SetWidgetDigitDisplay(void *cells, int widgetId, int key, u32 value)
{
    DigitPos pos = *func_ov027_020b91c8(cells, FindWidgetById(cells, widgetId));
    s16 digit = 0;
    s16 index;

    do {
        index = PXI_Init_0204f0c8(cells, key, 0);
        IndexedRecord_ClearActive(cells, index);
        func_0204f218(cells, index, (u16)(value % 10));
        IndexedRecord_SetPair(cells, index, &pos);
        IndexedRecords_SetFlag2(cells, index, digit == 0 || value != 0);
        pos.x -= 0x7000;
        value /= 10;
        digit++;
    } while (digit < 6);
    return index - 5;
}
