#include "nitro/types.h"

typedef struct PanelEntry {
    u8 pad_00[0x94];
    u32 visible : 1;
    u32 active : 1;
} PanelEntry;

typedef struct PanelContext {
    u8 pad_0000[0x6ac0];
    u8 entryManager[1];
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern PanelEntry *FindWidgetById(void *manager, int id);
extern int IsWidgetMoveFinished(PanelEntry *entry);

BOOL HasIdleActiveEntry(void)
{
    PanelEntry *entry;
    int i;

    for (i = 0; i < 3; i++) {
        entry = FindWidgetById(data_ov015_0207e960->entryManager, i + 1);
        if (entry != NULL && entry->active && IsWidgetMoveFinished(entry) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}
