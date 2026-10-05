#include "nitro/types.h"

typedef struct {
    u16 maxValue;
    u16 value;
    u16 width;
} HudGaugeSlot;

typedef struct {
    u16 total;
    u16 current;
    u16 target;
    u16 span;
    u8 pad_08[0x14];
} HudGaugeCounter;

typedef struct {
    u8 *layers[3];
    u8 *cellLayers[3];
    void *unk_18;
    u8 pad_1C[0x8];
    u8 dirtyMask;
    u8 pad_25[0x57];
    s32 highlightOn;
    s32 highlightBlocked;
    u8 pad_84[0x30];
    HudGaugeSlot slots[3];
    u8 pad_C6[0xE];
    HudGaugeCounter counters[4];
} HudGaugeSet;

extern HudGaugeSet *data_ov001_020a04cc;

extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void DrawShortLayoutRow(u8 *tiles, int row, int style);
extern void DrawGaugeSpan(u8 *tiles, int firstCell, int markCell, int cellCount, int rowCount, int barWidth,
                                   int leftInset, int topRow);

void RedrawHudGaugeRows(void) {
    HudGaugeSet *set = data_ov001_020a04cc;
    HudGaugeCounter *main = &set->counters[0];
    HudGaugeCounter *sub = &set->counters[1];
    int style;
    int i;
    int span;

    MIi_CpuCopyFast(set->cellLayers[0], set->layers[0], 0x1c0);
    if (set->highlightOn != 0 && set->highlightBlocked == 0) {
        style = 2;
    } else {
        style = 0;
    }
    for (i = 0; i < sub->current; i++) {
        DrawShortLayoutRow(set->layers[0], i, style);
    }
    for (; i < main->current; i++) {
        DrawShortLayoutRow(set->layers[0], i, 1);
    }
    span = main->span;
    if (span + main->current > main->total) {
        span = main->total - main->current;
    }
    DrawGaugeSpan(set->layers[0], i, set->slots[0].width, span, 5, 0x6e, 0, 1);
    set->dirtyMask |= 8;
}
