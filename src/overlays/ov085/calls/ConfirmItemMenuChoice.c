#include "nitro/types.h"

typedef struct ItemInfo
{
    int id;
} ItemInfo;

typedef struct ItemEntry
{
    u8 pad_00[8];
    ItemInfo *info;
} ItemEntry;

typedef struct ItemStatus
{
    int id;
    u8 pad_04[3];
    u8 maxLevel;
} ItemStatus;

typedef struct ItemSlot
{
    u8 *level;
    ItemEntry *entry;
    ItemStatus *status;
} ItemSlot;

typedef struct ItemMenu
{
    u8 state;
    u8 pad_01;
    u8 hideRank;
    u8 pad_03[3];
    u8 keepChoice;
    u8 pad_07;
    int confirmed;
    u8 pad_0c[4];
    s16 stockIndex;
    u8 pad_12[0xa];
    s16 itemCount;
    s16 cursor;
    u8 pad_20[0x5a4c - 0x20];
    ItemSlot *slots[1];
} ItemMenu;

extern ItemEntry *GetItemMenuEntry(ItemMenu *menu, int index);
extern BOOL CanSelectItem(ItemMenu *menu, int index);
extern void func_ov085_020c0bb0(ItemMenu *menu, u8 state);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern u16 GetSecondaryRecordCount(void);
extern u16 GetByteCounterOrDefault(int index);
extern u32 GetPrimaryRecordCount(void);
extern u8 *data_0205fe0c;

static inline BOOL IsSlotMaxed(ItemSlot *slot)
{
    BOOL maxed = FALSE;
    if (slot->status->maxLevel != 0 && *slot->level >= slot->status->maxLevel - 1)
    {
        maxed = TRUE;
    }
    return maxed;
}

void ConfirmItemMenuChoice(ItemMenu *menu)
{
    switch (menu->state)
    {
    case 0:
    {
        BOOL inRange;
        BOOL full;
        int id;
        ItemSlot *slot;
        u32 remaining;
        int next;

        if (menu->itemCount == 0 || !CanSelectItem(menu, menu->cursor))
        {
            PlaySoundEffect(0, 4);
            return;
        }
        inRange = FALSE;
        PlaySoundEffect(0, 1);
        id = GetItemMenuEntry(menu, menu->cursor)->info->id;
        if (id >= 0 && id <= 0x7f)
        {
            inRange = TRUE;
        }
        if (menu->hideRank != 0)
        {
            if (inRange)
            {
                full = TRUE;
            }
            else
            {
                u16 count = GetByteCounterOrDefault(id);
                full = TRUE;
                if (count != 1)
                {
                    full = FALSE;
                }
            }
        }
        else
        {
            slot = menu->slots[menu->cursor];
            if (slot->entry->info->id >= 0 && slot->entry->info->id <= 0x7f)
            {
                remaining = GetSecondaryRecordCount() - GetPrimaryRecordCount();
            }
            else
            {
                remaining = 99 - (data_0205fe0c + menu->stockIndex)[0x28d8];
            }
            full = TRUE;
            if (remaining > 1 && !IsSlotMaxed(slot))
            {
                full = FALSE;
            }
        }
        menu->confirmed = full;
        if (full)
        {
            next = 2;
        }
        else
        {
            next = 1;
        }
        func_ov085_020c0bb0(menu, next);
        break;
    }
    case 1:
        PlaySoundEffect(0, 1);
        func_ov085_020c0bb0(menu, 2);
        break;
    case 2:
        if (menu->keepChoice == 0)
        {
            PlaySoundEffect(0, 1);
            func_ov085_020c0bb0(menu, 0);
        }
        else
        {
            BOOL decline = FALSE;
            PlaySoundEffect(0, 1);
            if (menu->confirmed == 0)
            {
                decline = TRUE;
            }
            func_ov085_020c0bb0(menu, decline);
        }
        break;
    }
}
