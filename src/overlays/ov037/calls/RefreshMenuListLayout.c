#include "nitro/types.h"

typedef struct Ov037Context {
    u16 selected;
    u16 entryCount;
    s32 baseY;
    u8 list[0x68];
} Ov037Context;

extern Ov037Context *gContinueScreenContext;
extern void *FindLoadedElementById(void *list, u32 id);
extern void PositionListRecords(void *list, void *element, s16 position);
extern void SetTagRecordArmed(void *list, void *element, BOOL arm);
extern void *FindActiveRecordById(void *list, u32 id);
extern void func_ov027_020b824c(void *list, void *record, int mode, s16 position);

void RefreshMenuListLayout(void)
{
    void *list;
    int index;
    Ov037Context *ctx;

    ctx = gContinueScreenContext;
    list = ctx->list;

    for (index = 0; index < ctx->entryCount; index++) {
        if (index == ctx->selected) {
            PositionListRecords(list, FindLoadedElementById(list, 0), (s16)(ctx->baseY + index * 2));
            SetTagRecordArmed(list, FindLoadedElementById(list, 0), TRUE);
        } else {
            func_ov027_020b824c(list, FindActiveRecordById(list, 0), 8, (s16)(ctx->baseY + index * 2));
        }
        ctx = gContinueScreenContext;
    }
}
