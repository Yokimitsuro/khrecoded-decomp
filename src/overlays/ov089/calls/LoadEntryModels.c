#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 modelFile;
    u32 animFile;
    u32 extra;
} EntryModelDef;

typedef struct {
    int index;
    u8 model[0xb0];
    fx32 scale[3];
    u8 pad_c0[0x1c];
    u8 blendTable[0x2c];
} EntryModel;

typedef struct {
    EntryModel entries[7];
    EntryModelDef *defs;
    u8 pad_73c[8];
    int entryCount;
    int cursor;
    u32 projection[10];
    fx32 rotateSpeed;
} Ov089Menu;

extern EntryModelDef data_ov089_020c0560[];
extern EntryModelDef data_ov089_020c05f8[];
extern EntryModelDef data_ov089_020c05b0[];

extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern void LoadDefaultProjectionValues(u32 *projection);
extern u32 BuildSlotImageParams(int slot, u32 low);
extern void *func_0202c4a0(u32 fileId, int mode);
extern void InitSharedRecordAndDispatchAlt(void *dst, u32 fileId, void *info, int mode);
extern void Flags16_SetBit1(void *model);
extern void selectJointAnimationBlend(void *model, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void LoadEntryModels(Ov089Menu *menu)
{
    int i;
    int track;
    void *anim;

    switch (ReadSessionPackedBits(0x3700, 3)) {
    case 0:
        menu->entryCount = 1;
        menu->defs = data_ov089_020c0560;
        break;
    case 6:
        menu->entryCount = 7;
        menu->defs = data_ov089_020c05f8;
        break;
    default:
        menu->entryCount = 6;
        menu->defs = data_ov089_020c05b0;
        break;
    }
    LoadDefaultProjectionValues(menu->projection);
    menu->rotateSpeed = 0x1e000;
    for (i = 0; i < menu->entryCount; i++) {
        menu->entries[i].index = i;
        anim = func_0202c4a0(BuildSlotImageParams(2, menu->defs[i].animFile), 0xe);
        InitSharedRecordAndDispatchAlt(menu->entries[i].model, BuildSlotImageParams(2, menu->defs[i].modelFile), anim, 0xe);
        for (track = 0; track < 5; track++) {
            Flags16_SetBit1(menu->entries[i].model);
            selectJointAnimationBlend(menu->entries[i].model, track, menu->entries[i].blendTable, 0);
        }
        menu->entries[i].scale[0] = menu->entries[i].scale[1] = menu->entries[i].scale[2] = 0x800;
        NNSi_FndFreeFromDefaultHeap(anim);
    }
}
