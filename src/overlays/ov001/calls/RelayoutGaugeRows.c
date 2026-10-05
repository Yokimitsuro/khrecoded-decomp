#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x44];
    int rowCount;
    u8 pad_48[4];
    int unitCost;
    u8 pad_50[0x76];
    u16 totalUnits;
    u16 currentUnits;
} GaugeContext;

extern GaugeContext *data_ov001_020a04cc;
extern void *GetSceneTagTracker(void);
extern void *FindActiveRecordById(void *pool, u16 id);
extern void func_ov027_020b7f80(void *pool, void *record, int armed);
extern void func_ov001_020738d4(int row, BOOL filled, BOOL last);

void RelayoutGaugeRows(void)
{
    GaugeContext *ctx = data_ov001_020a04cc;
    int i;
    void *pool = GetSceneTagTracker();
    int scale;
    int total;
    int current;
    int rowsTotal;
    int rowsCurrent;

    for (i = 0; i < (ctx->rowCount + 1) / 2; i++) {
        func_ov027_020b7f80(pool, FindActiveRecordById(pool, (u16)(i + 50000)), 1);
    }

    scale = ctx->unitCost * 200;
    total = ctx->totalUnits * 48 / scale;
    current = ctx->currentUnits * 48 / scale;

    if (total > 0) {
        rowsTotal = (total - 1) / 48;
    } else {
        rowsTotal = 0;
    }
    if (current > 0) {
        rowsCurrent = (current - 1) / 48;
    } else {
        rowsCurrent = 0;
    }

    if (rowsTotal > 0) {
        for (i = 0; i < rowsTotal - 1; i++) {
            func_ov001_020738d4(i, i < rowsCurrent, FALSE);
        }
        func_ov001_020738d4(rowsTotal - 1, rowsTotal - 1 < rowsCurrent, TRUE);
    }

    ctx->rowCount = rowsTotal;
}


