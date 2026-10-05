#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PanelSprite {
    u8 pad_00[0x8];
    fx32 scale;
} PanelSprite;

typedef struct PanelState {
    u8 pad_0000[0x6514];
    u8 spriteList[0xc9bc - 0x6514];
    u8 entryTable[0xcaac - 0xc9bc];
    fx32 baseScale;
    u8 pad_cab0[0x8];
    u32 activeEntry;
    PanelSprite *sprite;
    u8 pad_cac0[0xcb50 - 0xcac0];
    u8 *slotEntries[(0xcf74 - 0xcb50) / 4];
    s16 row;
    u8 pad_cf76[2];
    s16 column;
    u8 pad_cf7a[2];
    s16 slot;
    u8 pad_cf7e[0xcf92 - 0xcf7e];
    s8 fadeCount;
    s8 fadeDirection;
    u8 pad_cf94;
    s8 blinkTimer;
} PanelState;

extern PanelState *data_ov014_0206f9a0;
extern u8 data_ov014_0206f81c[][7];
extern void SetGroupSlotsScale(void *list, PanelSprite *sprite, fx32 scale, fx32 one);
extern void ResetGroupSlotsPosition(void *list, PanelSprite *sprite);
extern void ApplyCategoryRecord(void *table, u32 category, u32 entry);
extern void ClearPackedField(void *table, u32 category, u32 entry);
extern void SyncMismatchedCategoryEntries(void *list, u32 entry, void *table, s32 flag);

void UpdatePanelFade(void)
{
    if (data_ov014_0206f9a0->fadeDirection != 0) {
        PanelSprite *sprite;
        s32 level;
        fx32 scale;
        data_ov014_0206f9a0->fadeCount--;
        level = data_ov014_0206f9a0->fadeCount;
        if (data_ov014_0206f9a0->fadeDirection >= 0) {
            level = 4 - level;
        }
        scale = level << 10;
        sprite = data_ov014_0206f9a0->sprite;
        SetGroupSlotsScale(data_ov014_0206f9a0->spriteList, sprite, scale, 0x1000);
        sprite->scale = (fx32)(((s64)data_ov014_0206f9a0->baseScale * scale + 0x800) >> 12);
        ResetGroupSlotsPosition(data_ov014_0206f9a0->spriteList, sprite);
        if (data_ov014_0206f9a0->fadeCount <= 0) {
            data_ov014_0206f9a0->fadeDirection = 0;
        }
    }
    data_ov014_0206f9a0->blinkTimer++;
    if (data_ov014_0206f9a0->blinkTimer == 0) {
        u32 category = data_ov014_0206f81c[data_ov014_0206f9a0->row][data_ov014_0206f9a0->column];
        u32 entry = data_ov014_0206f9a0->slotEntries[category][data_ov014_0206f9a0->slot];
        ApplyCategoryRecord(data_ov014_0206f9a0->entryTable, category, entry);
        ClearPackedField(data_ov014_0206f9a0->entryTable, category, entry);
        return;
    }
    if (data_ov014_0206f9a0->blinkTimer > 16) {
        data_ov014_0206f9a0->blinkTimer = 16;
    }
    {
        s32 timer = data_ov014_0206f9a0->blinkTimer;
        if (timer >= 0 && timer < 16) {
            SyncMismatchedCategoryEntries(data_ov014_0206f9a0->spriteList, data_ov014_0206f9a0->activeEntry, data_ov014_0206f9a0->entryTable, timer & 4);
        }
    }
}
