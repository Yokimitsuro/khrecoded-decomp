#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct SpawnParams {
    s32 entityId;
    s32 groupId;
    u8 pad_08[3];
    u8 visible;
    u8 pad_0c[0x20];
    s16 prevId;
    s16 nextId;
    u32 slot;
    u8 colorR;
    u8 colorG;
    u8 colorB;
    u8 pad_37[0x25];
} SpawnParams;

typedef struct FieldObject {
    u32 entityIndex : 9;
    u32 ownerIndex : 9;
    u32 mode : 5;
    u32 nextMode : 5;
    u32 style : 4;
    u32 unk_04_0 : 16;
    u32 memberTotal : 8;
    u32 unk_04_24 : 8;
    u32 unk_08;
    u16 memberCount : 8;
    u16 unk_0c_8 : 8;
    u8 pad_0e[0xa];
    u16 scale;
    u8 pad_1a[2];
    fx32 radiusX;
    fx32 radiusZ;
    u8 pad_24[0x1bc];
} FieldObject;

typedef struct FieldContext {
    u8 pad_00[0xc4];
    s32 isLoaded;
    u8 pad_c8[2];
    u16 objectCount;
    FieldObject *objects;
} FieldContext;

typedef struct UnitWork {
    s16 state;
    s8 slot;
    u8 phase;
    s16 prevId;
    s16 nextId;
    u8 pad_08[0x1c];
    VecFx32 velocity;
    s32 speed;
    MtxFx33 rotation;
    VecFx32 offset;
} UnitWork;

typedef struct FieldUnit {
    u8 pad_00[4];
    FieldContext *context;
    u8 pad_08[0x6e];
    s8 visible;
    u8 kind;
    u8 pad_78[0x44];
    u8 cols : 4;
    u8 rows : 4;
    u8 layers : 4;
    u8 style : 4;
    u8 pad_be;
    s8 savedVisible;
    u8 pad_c0[0x2c];
    UnitWork *work;
} FieldUnit;

extern s32 data_02060848;
extern const VecFx32 data_0205344c;
extern const MtxFx33 data_02053458;

extern void func_01ff88c4(void *dst, int value, u32 size);
extern void *func_ov001_02086384(FieldContext *context, int index);
extern BOOL IsNodeFlagBitClear(void *node);
extern void CacheEntry_SetActive(FieldUnit *unit, BOOL active);
extern void CopyFieldUnitSlotFrame(FieldUnit *unit, int index, FieldObject *dest);
extern void func_ov032_020bc208(FieldUnit *unit, int kind);
extern u32 func_0202a9e4(u32 range);
extern void func_ov016_020a6974(FieldUnit *unit, void (*callback)(FieldUnit *self));
extern void UnlinkGroupMember(FieldUnit *self);
extern void func_ov016_020a6358(FieldContext *context, SpawnParams *params);

void SpawnGroupMemberGrid(FieldUnit *unit, const SpawnParams *params)
{
    UnitWork *work = unit->work;
    FieldContext *context = unit->context;
    FieldObject *object;
    SpawnParams local = *params;
    int spawned = 1;
    int groupId = params->groupId + 1;
    int prevId = params->entityId;
    int entityId = prevId + 1;
    int row;
    int layer;
    int nextId;
    int col;

    data_02060848 = 1;
    if (context->isLoaded == 0) {
        func_01ff88c4(work, 0, 100);
    }
    if (params->prevId == -1) {
        local.slot = context->objectCount;
        object = &context->objects[context->objectCount];
        if (context->isLoaded == 0) {
            object->entityIndex = params->entityId;
            object->memberCount = unit->cols * unit->rows * unit->layers;
            object->ownerIndex = params->entityId;
            unit->savedVisible = params->visible;
            unit->visible = unit->savedVisible;
            object->radiusZ = object->radiusX = unit->visible << 12;
            object->memberTotal = object->memberCount;
            object->style = unit->style - 5;
            object->scale = 0x1000;
            if (object->memberCount > 1) {
                local.nextId = entityId;
            }
        } else {
            CacheEntry_SetActive(unit, IsNodeFlagBitClear(func_ov001_02086384(unit->context, object->ownerIndex)));
            object = &context->objects[work->slot];
            CopyFieldUnitSlotFrame(unit, work->slot, object);
            local.slot = work->slot;
        }
        unit->kind = 0;
        context->objectCount++;
    } else {
        object = &context->objects[params->slot];
        if (context->isLoaded != 0) {
            unit->kind = object->mode;
            func_ov032_020bc208(unit, object->mode);
        }
    }
    if (context->isLoaded == 0) {
        work->prevId = local.prevId;
        work->nextId = local.nextId;
        work->slot = local.slot;
        work->state = 0;
        work->velocity = data_0205344c;
        work->phase = func_0202a9e4(0x10);
    }
    work->rotation = data_02053458;
    work->offset = data_0205344c;
    func_ov016_020a6974(unit, UnlinkGroupMember);
    for (layer = 0; layer < unit->layers; layer++) {
        for (row = 0; row < unit->rows; row++) {
            for (col = 0; col < unit->cols; col++) {
                if (col != 0 || row != 0 || layer != 0) {
                    if (spawned + 1 < object->memberCount) {
                        nextId = entityId + 1;
                    } else {
                        nextId = -1;
                    }
                    local.entityId = entityId;
                    local.groupId = groupId;
                    local.prevId = prevId;
                    local.nextId = nextId;
                    local.colorR = 1;
                    local.colorG = 1;
                    local.colorB = 1;
                    func_ov016_020a6358(context, &local);
                    prevId = entityId;
                    spawned++;
                    entityId++;
                    groupId++;
                }
            }
        }
    }
}







