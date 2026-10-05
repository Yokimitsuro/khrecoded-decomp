#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x80];
    u8 *entryStates;
} ListView;

extern void func_ov025_020b6cc0(ListView *list, int entryIndex);
extern BOOL func_ov025_020b6850(ListView *list, int entryIndex);

BOOL TrySelectListEntry(ListView *list, int entryIndex)
{
    u8 state = list->entryStates[entryIndex];
    BOOL selectable = TRUE;

    if (state != 0 && state != 1) {
        selectable = FALSE;
    }
    func_ov025_020b6cc0(list, entryIndex);
    if (!selectable || !func_ov025_020b6850(list, entryIndex)) {
        return FALSE;
    }
    return TRUE;
}
