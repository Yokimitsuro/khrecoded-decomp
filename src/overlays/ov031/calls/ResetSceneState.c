#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SceneEntry SceneEntry;
typedef void (*SceneResetCallback)(SceneEntry *entry, int arg);

struct SceneEntry {
    u8 pad_000[0x200];
    SceneResetCallback onReset;
};

typedef struct {
    u8 pad_00[0x06];
    u16 flags;
} OverlayState;

extern OverlayState *data_ov031_020bc820;
extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void func_ov001_0206a8c8(fx32 value);
extern void BeginScreenFadeOut(int mode);
extern void func_ov001_0206e444(int enable);
extern SceneEntry *GetBoundedEntryField(int index);
extern void func_0204d994(void);

void ResetSceneState(void)
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
    data_ov031_020bc820->flags = data_ov031_020bc820->flags | 0x40;
}
