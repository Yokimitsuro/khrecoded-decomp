#include "nitro/types.h"

typedef struct {
    u8 pad0[0x110];
    int digitCells[9];
} RecordPanel;

extern void *func_ov039_020bc1ec(void);
extern void func_0204f218(void *widget, int cell, u16 frame);
extern void IndexedRecords_SetFlag2(void *widget, int cell, BOOL visible);

void DrawPlayTimeDigits(RecordPanel *panel, u32 seconds)
{
    void *widget = func_ov039_020bc1ec();
    int i;

    if (seconds >= 3600000) {
        seconds = 3600000 - 1;
    }
    func_0204f218(widget, panel->digitCells[0], seconds % 10);
    seconds /= 10;
    func_0204f218(widget, panel->digitCells[1], seconds % 6);
    seconds /= 6;
    func_0204f218(widget, panel->digitCells[3], seconds % 10);
    seconds /= 10;
    func_0204f218(widget, panel->digitCells[4], seconds % 6);
    seconds /= 6;
    i = 6;
    do {
        IndexedRecords_SetFlag2(widget, panel->digitCells[i], TRUE);
        func_0204f218(widget, panel->digitCells[i], seconds % 10);
        seconds /= 10;
        i++;
    } while (seconds != 0);
    for (; i < 9; i++) {
        IndexedRecords_SetFlag2(widget, panel->digitCells[i], FALSE);
    }
}
