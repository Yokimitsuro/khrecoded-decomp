#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MoviePlayerCtx {
    u8 pad_00[6];
    u16 flags;
} MoviePlayerCtx;

typedef void (*EntryCallback)(void *entry, s32 arg);

typedef struct SceneEntry {
    u8 pad_000[0x200];
    EntryCallback onReset;
} SceneEntry;

extern MoviePlayerCtx *data_ov030_020bd020;
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void func_ov001_0206a8c8(fx32 rate);
extern void BeginScreenFadeOut(s32 mode);
extern void func_ov001_0206e444(s32 enable);
extern SceneEntry *GetBoundedEntryField(s32 index);
extern void func_0204d994(void);

void SuspendSceneAtQuarterRate(void)
{
    SceneEntry *entry;

    func_ov001_0206a8c8(FX_Div(0x10000, 0x40000));
    BeginScreenFadeOut(2);
    func_ov001_0206e444(1);
    entry = GetBoundedEntryField(0);
    if (entry->onReset != NULL) {
        entry->onReset(entry, 0);
    }
    func_0204d994();
    data_ov030_020bd020->flags |= 0x40;
}
