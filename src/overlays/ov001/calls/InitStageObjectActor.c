#include "nitro/types.h"

typedef struct LinkTarget {
    u8 kind;
    u8 group;
    u8 index;
    u8 reserved;
} LinkTarget;

typedef struct {
    void (*func)(void *self);
    void *self;
} ObjectCallback;

typedef struct {
    u32 unk_00;
    u32 resourceA;
    u32 resourceB;
} StageObjectDef;

typedef struct {
    u8 pad_000[0x8];
    u16 flags;
    u8 pad_00A[0x182];
    ObjectCallback callback;
    u8 pad_194[0x3c];
    u16 cellX;
    u16 cellY;
    u8 pad_1D4[0x98];
    u32 stateBits : 31;
    u32 stateTop : 1;
    u8 pad_270[0x8];
    const void *animTable;
    u16 slot;
    u16 defId;
    u8 pad_280[0x8];
    u16 drawFlags;
    u16 mode : 2;
    u16 layer : 3;
    u16 shade : 3;
    u16 modeHigh : 8;
    u8 pad_28C[0x1c];
    s32 radius;
    s32 height;
    u8 pad_2B0[0x34];
    u8 alpha;
    u8 pad_2E5[0xb];
    s32 scale[3];
    u8 pad_2FC[0x20];
    s32 baseScale;
    u8 colorIndex;
    u8 pad_321[0xb];
    s32 spinX;
    s32 spinY;
    u8 pad_334[0x68];
    s32 scaleX;
    s32 scaleY;
    s16 timerA;
    u8 pad_3A6[0x2];
    s16 timerB;
} StageObjectActor;

extern const u8 gNearestEntrySyncHandlers[];

extern StageObjectDef *GetStageObjectRecord(int defId);
extern void InitSequencer(void *cell, int arg, u32 resourceA, u32 resourceB);
extern void ActorEntry_Init(int slot, void *entry, u16 group, const LinkTarget *attributes, const void *shape, BOOL flag20, s8 priority);
extern void InitStageObjectModel(StageObjectActor *actor, StageObjectDef *def);
extern void CanActorReactToSource(void *self);

BOOL InitStageObjectActor(StageObjectActor *actor, u16 defId, int slot, const void *shape, int cellArg) {
    LinkTarget link;
    ObjectCallback callback;
    StageObjectDef *def = GetStageObjectRecord(defId);

    if (def == NULL) {
        return FALSE;
    }
    if (slot == 0) {
        slot = 0xffff;
    }
    InitSequencer(&actor->cellX, cellArg, def->resourceA, def->resourceB);
    if (actor->stateBits & 0x800) {
        shape = NULL;
    }
    link.kind = 1;
    link.group = actor->cellX;
    link.index = actor->cellY;
    ActorEntry_Init(slot, actor, 0x30, &link, shape, FALSE, 0x20);
    callback.func = CanActorReactToSource;
    callback.self = actor;
    actor->callback = callback;
    InitStageObjectModel(actor, def);
    actor->flags |= 0x800;
    actor->defId = defId;
    actor->slot = slot;
    actor->scale[0] = 0x1000;
    actor->scale[1] = 0x1000;
    actor->scale[2] = 0x1000;
    actor->baseScale = 0x1000;
    actor->scaleX = 0x1000;
    actor->scaleY = 0x1000;
    actor->drawFlags |= 0x10;
    actor->height = 0xa000;
    actor->radius = 0xcd;
    actor->timerB = 0;
    actor->timerA = 0;
    actor->shade = 2;
    actor->layer = 5;
    actor->mode = 0;
    actor->animTable = gNearestEntrySyncHandlers;
    actor->colorIndex = 0x1f;
    actor->spinX = 0x8000;
    actor->spinY = 0x8000;
    actor->alpha = 0xff;
    return TRUE;
}
