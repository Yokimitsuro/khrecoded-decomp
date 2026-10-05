#include "nitro/types.h"

typedef struct {
    u8 pad_00;
    u8 modelFile;
    u8 paletteId;
} ModelInfo;

typedef struct {
    u8 pad_00[0x10];
    ModelInfo model;
} SelectionRecord;

typedef struct {
    u32 file;
    u32 palette;
    void *texture;
    void *user;
    s32 partMask;
    void *extra;
} ModelSetupDesc;

typedef struct {
    u8 pad_00[4];
    u8 data[4];
} ResourceOwner;

typedef struct {
    u8 pad_000[0x230];
    ResourceOwner *owner;
    u8 pad_234[0x6cc - 0x234];
    u8 modelUser[0x72c - 0x6cc];
    u8 modelExtra[0x930 - 0x72c];
    u8 kind;
    u8 pad_931[0x9d4 - 0x931];
    u8 modelSets[0xe34 - 0x9d4];
    u8 unit[0xe88 - 0xe34];
    u8 texture[4];
} Actor;

extern SelectionRecord *GetOverlaySelectionRecord(unsigned int selectionIndex);
extern void InitUnitResources(void *unit, void *arg, int kind, u32 selection, int extra);
extern void SetPendingFromTable(int index);
extern void LoadModelObject(void *obj, ModelSetupDesc *desc);
extern void ClearPendingWord(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void Actor_SetModelSetsVisible(Actor *actor, BOOL enable);

void LoadActorModel(Actor *actor)
{
    ModelInfo *info = &GetOverlaySelectionRecord(actor->kind)->model;
    ModelSetupDesc setup;

    InitUnitResources(actor->unit, actor->owner->data, 0, actor->kind, 0);
    SetPendingFromTable(0);
    setup.file = info->modelFile;
    setup.palette = 0;
    setup.texture = actor->texture;
    setup.user = actor->modelUser;
    setup.extra = actor->modelExtra;
    setup.partMask = 0x13;
    LoadModelObject(actor->modelSets, &setup);
    ClearPendingWord();
    if (func_ov001_020645c8(0x351f)) {
        Actor_SetModelSetsVisible(actor, TRUE);
    }
}
