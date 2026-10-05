#include "nitro/types.h"

typedef struct ModelInfo {
    u8 pad_00;
    u8 modelFile;
    u8 paletteId;
} ModelInfo;

typedef struct SelectionRecord {
    u8 pad_00[0x10];
    ModelInfo model;
} SelectionRecord;

typedef struct ModelSetupDesc {
    u32 file;
    u32 palette;
    u32 pad_08;
    u32 userValue;
    s32 partMask;
    u32 hasExtra;
} ModelSetupDesc;

typedef struct EntryGroupDesc {
    int resourceId;
    u32 animationName;
    s32 slotCount;
    u32 modelName;
    BOOL fixedSlots;
} EntryGroupDesc;

typedef struct ResourceOwner {
    u8 pad_00[4];
    u8 data[4];
} ResourceOwner;

typedef struct Entity {
    u8 pad_000[0x230];
    ResourceOwner *owner;
    u8 pad_234[0x6cc - 0x234];
    u8 modelUser[4];
    u8 pad_6d0[0x9b4 - 0x6d0];
    u8 kind;
    u8 pad_9b5[3];
    int tableIndex;
    u8 pad_9bc[0xb68 - 0x9bc];
    u32 model[(0xfc8 - 0xb68) / 4];
    u8 unit[0x1100 - 0xfc8];
    u16 groupId;
} Entity;

extern SelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern void InitUnitResources(void *unit, void *arg, int kind, u32 selection, int extra);
extern void SetPendingFromTable(int index);
extern void LoadModelObject(void *obj, ModelSetupDesc *desc);
extern void ZeroBytes0x14(void *obj);
extern u32 MakePaletteUploadParams130(u32 index);
extern u32 MakePaletteUploadParams145(u32 index);
extern int func_ov021_020a89c8(EntryGroupDesc *desc);
extern void ClearPendingWord(void);
extern void SetBit1WhenBit0Set(u32 *flags, s32 enable);

void LoadOverlay057EntityModel(Entity *entity)
{
    ModelInfo *info = &GetOverlaySelectionRecord(entity->kind)->model;
    ModelSetupDesc setup;
    EntryGroupDesc group;

    InitUnitResources(entity->unit, entity->owner->data, entity->tableIndex, entity->kind, 0);
    SetPendingFromTable(entity->tableIndex);
    setup.file = info->modelFile;
    setup.palette = 0;
    setup.pad_08 = 0;
    setup.userValue = (u32)entity->modelUser;
    setup.partMask = 0x100;
    setup.hasExtra = 0;
    LoadModelObject(entity->model, &setup);
    ZeroBytes0x14(&group);
    group.modelName = MakePaletteUploadParams130(info->paletteId);
    group.animationName = MakePaletteUploadParams145(info->paletteId);
    group.slotCount = 3;
    entity->groupId = func_ov021_020a89c8(&group);
    ClearPendingWord();
    SetBit1WhenBit0Set(entity->model, 1);
}
