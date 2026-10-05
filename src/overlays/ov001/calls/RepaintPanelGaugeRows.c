#include "nitro/types.h"

typedef struct {
    u16 count;
    u16 drawn;
    u8 pad_04[2];
    u16 span;
    u8 pad_08[0x10];
    int drawTail;
} PanelRecord;

typedef struct {
    u8 pad_000[0x18];
    u8 *tiles;
    u8 *tilesBackup;
    u8 pad_020[4];
    u8 flags;
    u8 pad_025[0x93];
    u16 markCell;
    u8 pad_0ba[0x52];
    PanelRecord records[2];
} PanelContext;

extern PanelContext *data_ov001_020a04cc;
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void func_ov001_02073894(u8 *tiles, int cell, int pattern);
extern void DrawGaugeSpan(u8 *tiles, int firstCell, int markCell, int cellCount, int rowCount, int barWidth,
                                   int leftInset, int topRow);

void RepaintPanelGaugeRows(void)
{
    PanelContext *ctx = data_ov001_020a04cc;
    PanelRecord *recA = &ctx->records[0];
    int rowB;
    PanelRecord *recB = &ctx->records[1];
    int rowA;
    int colB;
    int colA;
    int last;
    int i;
    int count;

    if (recA->drawn != 0) {
        last = recA->drawn - 1;
        colA = last % 48 + 1;
        rowA = last / 48;
    } else {
        colA = 0;
        rowA = 0;
    }
    if (recB->drawn != 0) {
        last = recB->drawn - 1;
        colB = last % 48 + 1;
        rowB = last / 48;
    } else {
        colB = 0;
        rowB = 0;
    }

    MIi_CpuCopyFast(ctx->tilesBackup, ctx->tiles, 0xe0);

    if (rowB == rowA) {
        for (i = 0; i < colB; i++) {
            func_ov001_02073894(ctx->tiles, i, 0);
        }
    } else if (rowA > rowB) {
        i = 0;
    } else {
        for (i = 0; i < colB; i++) {
            func_ov001_02073894(ctx->tiles, i, 0);
        }
    }

    if (recA->drawTail != 0) {
        for (; i < colA; i++) {
            func_ov001_02073894(ctx->tiles, i, 1);
        }
    }

    count = recA->span;
    if (count + recA->drawn > recA->count) {
        count = recA->count % 48 - colA;
    }
    if (count + colA > 48) {
        count = 48 - colA;
    }
    DrawGaugeSpan(ctx->tiles, i, ctx->markCell, count, 4, 0x30, 0, 3);
    ctx->flags = ctx->flags | 2;
}
