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
    u8 pad_1c[0x51 - 0x1c];
    s8 matchGroup;
    s8 matchEnabled;
    u8 pad_53[2];
    s8 slotCount;
    u8 pad_56[0x84 - 0x56];
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

BOOL MarkMatchingPanelSlots(void) {
    u32 plane;
    BOOL result;
    int i;
    int marked;
    int count;

    result = FALSE;
    count = data_ov015_020812e0->slotCount;
    if (data_ov015_020812e0->matchEnabled == 0) {
        return result;
    }
    if (data_ov015_020812e0->flags & 2) {
        return result;
    }
    marked = 0;
    for (i = 0; i < count; i++) {
        if (data_ov015_020812e0->slots[i].level >= 2 && data_ov015_020812e0->matchGroup == data_ov015_020812e0->slots[i].group) {
            marked++;
            data_ov015_020812e0->slots[i].flags |= 4;
        }
    }
    if (marked >= 1) {
        ClearBuffer5100((u8 *)data_ov015_020812e0 + 0x15f38);
        for (i = 0; i < count; i++) {
            if (data_ov015_020812e0->slots[i].flags & 4) {
                SetPanelEntrySequence(i, 6);
                DrawSlotTileBlocks((u8 *)data_ov015_020812e0 + 0x15f38, data_ov015_020812e0->slotCount, i, 0xff, 0);
            }
        }
        plane = (REG_DB_DISPCNT & 0x1f00) >> 8;
        REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | ((plane & ~4) << 8);
        func_ov015_02078f18();
        BuildTileGridMap(G2S_GetBG2ScrPtr(), 0x145);
        ConvertTileGrid((u8 *)data_ov015_020812e0 + 0x1b038, (u8 *)data_ov015_020812e0 + 0x15f38, 0x16, 0x145);
        data_ov015_020812e0->flags |= 2;
        result = TRUE;
    }
    return result;
}
