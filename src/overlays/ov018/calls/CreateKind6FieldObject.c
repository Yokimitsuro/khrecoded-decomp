#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TouchHandler {
    u32 words[5];
} TouchHandler;

typedef struct {
    u8 pad_00[0x59];
    u8 kind;
} ObjectDef;

typedef struct FieldObject {
    u8 pad_00[4];
    ObjectDef *def;
    u8 pad_08[4];
    void (*update)(void);
    u8 pad_10[0x20];
    u16 slotFlags;
    u8 actorId;
    u8 pad_33;
    fx32 speed;
    VecFx32 position;
    u16 packedLow;
    u8 packedHigh;
    u8 unk_47;
    s32 unk_48;
    s8 linkIndex;
    s8 linkGroup;
    u8 pad_4e[2];
    u16 flags;
    s8 state;
    u8 pad_53[0x4d];
    s32 kind;
    u8 pad_a4[4];
    TouchHandler touch;
} FieldObject;

extern FieldObject *func_ov001_02086330(void *manager);
extern void ResetKindDirection(FieldObject *obj);
extern void AppendNodeToActiveList(int kind, int objectId, int slot);
extern int func_ov001_02063a38(void);
extern void func_ov018_020a2ca4(void);
extern void FieldObject_ShiftWithArea(FieldObject *obj);
extern TouchHandler MakeCommandRecord(void (*callback)(FieldObject *), FieldObject *owner, int mode, int flags);
extern void LinkPendingNode(TouchHandler *handler);

u8 CreateKind6FieldObject(void *manager, u16 objectId, int slot, u16 packedLow, u8 packedHigh, VecFx32 *position,
                       s8 linkIndex, s8 linkGroup, fx32 speed)
{
    FieldObject *obj = func_ov001_02086330(manager);
    ObjectDef *def = obj->def;

    obj->position = *position;
    obj->packedLow = packedLow;
    obj->packedHigh = packedHigh;
    obj->unk_47 = 0;
    obj->speed = speed;
    obj->state = 0;
    obj->flags = 0;
    obj->unk_48 = 0;
    obj->linkIndex = linkIndex;
    obj->linkGroup = linkGroup;
    obj->flags |= 1;
    if (obj->state != 0) {
        obj->update = NULL;
        obj->state = 2;
    } else {
        obj->update = func_ov018_020a2ca4;
        obj->slotFlags |= 8;
        obj->slotFlags |= 0x10;
    }
    if (obj->linkGroup >= 0) {
        obj->kind = 1;
    } else {
        obj->kind = 3;
    }
    ResetKindDirection(obj);
    obj->actorId = slot;
    AppendNodeToActiveList(def->kind, objectId, obj->actorId);
    if (func_ov001_02063a38() == 7) {
        obj->touch = MakeCommandRecord(FieldObject_ShiftWithArea, obj, 2, 0);
        LinkPendingNode(&obj->touch);
    }
    return obj->actorId;
}







