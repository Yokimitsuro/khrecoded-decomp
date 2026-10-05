#include "nitro/types.h"

typedef struct {
    s16 level;
    u16 flags;
    s16 group;
    u8 pad_06[0x12];
} PanelSlot;

typedef struct {
    u8 pad_00[0x18];
    u32 flags;
    u8 pad_1c[0x53 - 0x1c];
    s8 targetGroup;
    u8 pad_54;
    s8 slotCount;
    u8 pad_56;
    s8 requiredCount;
    u8 pad_58[2];
    s8 savedCount;
    u8 pad_5b[0x84 - 0x5b];
    PanelSlot slots[1];
} PanelState;

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)

extern PanelState *data_ov015_020812e0;
extern void ClearBuffer5100(void *buffer);
extern void SetPanelEntrySequence(int slot, int mode);
extern void DrawSlotTileBlocks(void *buffer, int count, int slot, int color, int flag);
extern void func_ov015_02078f18(void);
extern void *G2S_GetBG2ScrPtr(void);
extern void BuildTileGridMap(void *screen, int tile);
extern void ConvertTileGrid(void *dst, void *src, int width, int tile);

BOOL MarkLowPanelSlots(void) {
    u32 plane;
    BOOL result;
    int i;
    int marked;
    int count;

    result = FALSE;
    marked = 0;
    count = data_ov015_020812e0->slotCount;
    for (i = 0; i < count; i++) {
        if (data_ov015_020812e0->slots[i].level >= 2) {
            if (data_ov015_020812e0->targetGroup == data_ov015_020812e0->slots[i].group) {
                marked = 0;
                data_ov015_020812e0->savedCount = data_ov015_020812e0->requiredCount;
                data_ov015_020812e0->flags |= 4;
                break;
            }
            marked++;
            data_ov015_020812e0->slots[i].flags |= 2;
        }
    }
    if (marked >= data_ov015_020812e0->requiredCount) {
        ClearBuffer5100((u8 *)data_ov015_020812e0 + 0x15f38);
        for (i = 0; i < count; i++) {
            if (data_ov015_020812e0->slots[i].flags & 2) {
                SetPanelEntrySequence(i, 5);
                DrawSlotTileBlocks((u8 *)data_ov015_020812e0 + 0x15f38, data_ov015_020812e0->slotCount, i, 0xff, 0);
            }
        }
        plane = (REG_DB_DISPCNT & 0x1f00) >> 8;
        REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | ((plane & ~4) << 8);
        func_ov015_02078f18();
        BuildTileGridMap(G2S_GetBG2ScrPtr(), 0x145);
        ConvertTileGrid((u8 *)data_ov015_020812e0 + 0x1b038, (u8 *)data_ov015_020812e0 + 0x15f38, 0x16, 0x145);
        result = TRUE;
    }
    return result;
}
