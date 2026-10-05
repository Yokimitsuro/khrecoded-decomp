#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*EntryCallback)(u8 *entry, int arg, int size, int mode);

typedef struct {
    u8 pad_000[0xa4];
    VecFx32 position;
    u8 pad_0b0[0x5c];
    u8 blendTable[0x24];
    s8 slot;
    s8 active;
    u8 pad_132[2];
    VecFx32 basePosition;
    u8 pad_140[4];
    fx32 speed;
    s32 elapsed;
} SlotMarker;

extern VecFx32 *func_ov001_0206dc60(int slot);
extern u8 *GetBoundedEntryField(int index);
extern void selectJointAnimationBlend(void *animationState, u16 trackIndex, void *blendTable, s16 blendIndex);

void ActivateSlotMarker(SlotMarker *marker)
{
    u8 *entry;
    EntryCallback callback;

    marker->speed = 0x16000;
    marker->elapsed = 0;
    marker->active = 1;
    marker->basePosition = *func_ov001_0206dc60(marker->slot);
    marker->position = marker->basePosition;
    selectJointAnimationBlend(marker, 0, marker->blendTable, 0);
    entry = GetBoundedEntryField(marker->slot);
    callback = *(EntryCallback *)(entry + 0x1f0);
    if (callback != NULL) {
        callback(entry, 0, 0x20, 2);
    }
}
