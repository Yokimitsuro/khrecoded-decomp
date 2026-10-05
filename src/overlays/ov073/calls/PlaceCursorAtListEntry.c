#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x90];
    void *cursorCell;
} ListView;

extern void func_ov073_020c3700(ListView *list, int entryIndex, void *cell);

void PlaceCursorAtListEntry(ListView *list, int entryIndex)
{
    func_ov073_020c3700(list, entryIndex, list->cursorCell);
}
