#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x80];
    u8 *entryStates;
} ListView;

extern void SelectListEntry(ListView *list, int entryIndex);
extern BOOL ExpandListRow(ListView *list, int entryIndex);

BOOL TrySelectListEntry_020c37a8(ListView *list, int entryIndex)
{
    u8 state = list->entryStates[entryIndex];
    BOOL selectable = TRUE;

    if (state != 0 && state != 1) {
        selectable = FALSE;
    }
    SelectListEntry(list, entryIndex);
    if (!selectable || !ExpandListRow(list, entryIndex)) {
        return FALSE;
    }
    return TRUE;
}
