#include "nitro/types.h"

typedef struct OverlaySelectionRecord {
    u8 overlaySet;
    u8 pad_01[0x1B];
    s16 soundArcIndex;
} OverlaySelectionRecord;

typedef struct SoundArcLoader {
    u8 pad_00[0x28];
    s32 primaryArc;
    s32 secondaryArc;
} SoundArcLoader;

typedef struct SoundArcList {
    void **entries;
    s32 entryCount;
} SoundArcList;

typedef struct SceneState {
    u8 pad_000[0x9B4];
    u8 selectionIndex;
    u8 pad_9B5[0xB2C - 0x9B5];
    SoundArcLoader soundArcLoader;
    u8 pad_B5C[0x1070 - 0xB5C];
    SoundArcList soundArcList;
} SceneState;

extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void SetSoundPairAndQueue(SoundArcLoader *loader, s32 primaryArc, s32 secondaryArc);
extern void QueueGroupSounds(SoundArcList *list);

void LoadSceneSoundArchives_020d4238(SceneState *scene)
{
    OverlaySelectionRecord *record;

    record = GetOverlaySelectionRecord(scene->selectionIndex);
    SetSoundPairAndQueue(&scene->soundArcLoader, 0x32, record->soundArcIndex + 0x54);
    QueueGroupSounds(&scene->soundArcList);
}
