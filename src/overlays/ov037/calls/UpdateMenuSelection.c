#include "nitro/types.h"

typedef struct MenuEntry {
    s32 id;
    s32 extra;
} MenuEntry;

typedef struct Ov037Context {
    u16 selected;
    u16 entryCount;
    s32 freeSlots;
    u8 list[0x4c];
    u8 tileTable[0x1c];
    u8 model[0x128];
    u8 camera[0x38];
    s32 enabled;
    MenuEntry entries[4];
    u8 text[0x34];
    u64 startTick;
    s32 textUploaded;
} Ov037Context;

extern Ov037Context *gContinueScreenContext;
extern u16 data_02060500;
extern u64 OS_GetTick(void);
extern void Text_UploadTileBuffer(void *text);
extern void RefreshMenuListLayout(void);
extern void PlaySoundEffect(int player, int sound);
extern void func_ov027_020b7df4(void *list);
extern void FlushDirtyTileTableRows(void *tileTable);
extern void camera_commit_projection(void *camera);
extern void AdvanceAnimationTracks(void *model, int step);
extern void func_01ffb12c(void *model);

s32 UpdateMenuSelection(void)
{
    s32 result = -1;
    Ov037Context *ctx = gContinueScreenContext;

    if (ctx == NULL) {
        return result;
    }
    if (ctx->textUploaded == 0 && OS_GetTick() >= ctx->startTick + 0xffb10) {
        Text_UploadTileBuffer(ctx->text);
        gContinueScreenContext->textUploaded = 1;
    }
    ctx = gContinueScreenContext;
    if (ctx->enabled) {
        if (data_02060500 & 0x40) {
            ctx->selected = (ctx->selected + ctx->entryCount - 1) % ctx->entryCount;
            RefreshMenuListLayout();
            if (gContinueScreenContext->entryCount > 1) {
                PlaySoundEffect(0, 0);
            }
        } else if (data_02060500 & 0x80) {
            ctx->selected = (ctx->selected + 1) % ctx->entryCount;
            RefreshMenuListLayout();
            if (gContinueScreenContext->entryCount > 1) {
                PlaySoundEffect(0, 0);
            }
        } else if (data_02060500 & 1) {
            result = ctx->entries[ctx->selected].id;
            ctx->enabled = 0;
            PlaySoundEffect(0, 1);
        }
    }
    func_ov027_020b7df4(gContinueScreenContext->list);
    FlushDirtyTileTableRows(gContinueScreenContext->tileTable);
    camera_commit_projection(gContinueScreenContext->camera);
    AdvanceAnimationTracks(gContinueScreenContext->model, 0x1000);
    func_01ffb12c(gContinueScreenContext->model);
    return result;
}
