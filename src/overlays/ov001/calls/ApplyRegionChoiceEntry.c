#include "nitro/types.h"

typedef struct {
    s32 offsets[11];
} RegionOffsetTable;

typedef struct {
    u8 pad_000[0x10];
    u8 region;
} SelectionRecord;

typedef struct {
    u8 pad_0000[0x488];
    u32 activeEntry;
    u8 pad_048c[0xb34 - 0x48c];
    u32 entries[0x200];
    u32 savedEntry;
} Scene;

typedef struct {
    u32 unk0;
    Scene *scene;
} SceneHolder;

extern SceneHolder data_ov001_020a04c4;
extern const RegionOffsetTable data_ov001_0209dd90;
extern SelectionRecord *GetOverlaySelectionRecord(u32 index);
extern void ClearChoiceHighlight(Scene *scene);
extern void PlaySoundEffect(int channel, int soundId);
extern void func_ov001_0207b668(u32 value);

void ApplyRegionChoiceEntry(u32 choice)
{
    Scene *scene = data_ov001_020a04c4.scene;
    RegionOffsetTable table = data_ov001_0209dd90;
    int index = choice + table.offsets[GetOverlaySelectionRecord(0)->region];

    ClearChoiceHighlight(scene);
    scene->activeEntry = scene->entries[index];
    scene->savedEntry = scene->entries[index];
    PlaySoundEffect(0, 0x13);
    func_ov001_0207b668((u8)choice);
}
