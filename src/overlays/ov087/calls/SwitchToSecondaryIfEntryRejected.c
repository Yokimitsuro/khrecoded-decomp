#include "nitro/types.h"

typedef struct {
    u32 id;
    u8 pad_004[0x104];
} ListEntry;

typedef struct {
    u32 unk_00;
    int cursor;
    u8 pad_008[0x110];
    ListEntry entries[1];
} EntryList;

extern void *func_ov039_020bc1dc(void);
extern BOOL func_ov087_020c7c38(u32 entryId);
extern void SetWidgetRootDpadEnabled(void *container, BOOL enable);
extern void SetPrimaryElementEnabled(BOOL enabled);
extern void SetSecondaryElementEnabled(BOOL enabled);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void SwitchToSecondaryIfEntryRejected(EntryList *list)
{
    void *container = func_ov039_020bc1dc();

    if (func_ov087_020c7c38(list->entries[list->cursor].id)) {
        return;
    }
    SetWidgetRootDpadEnabled(container, FALSE);
    SetPrimaryElementEnabled(FALSE);
    SetSecondaryElementEnabled(TRUE);
    PlaySoundEffect(0, 2);
}
