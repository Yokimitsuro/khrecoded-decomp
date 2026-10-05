#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x59];
    u8 modelKind;
} ObjectDef;

typedef struct {
    u8 pad_00[4];
    ObjectDef *def;
    void *model;
    u8 pad_0c[0x24];
    u16 renderFlags;
    u8 actorId;
    u8 paletteId;
    u8 pad_34[4];
    s32 position[3];
    u8 pad_44[3];
    s8 animIndex;
    void *resource;
    u8 pad_4c[4];
    s8 state;
    s8 scaleSteps;
    u8 pad_52[2];
    u16 flags;
} StackedBlock;

typedef struct {
    u32 flags;
    u16 drawFlags;
    u8 pad_06[0x7a];
    u16 unk_80;
    u8 pad_82[0x8a];
    u8 collision[4];
} Actor;

extern void *func_ov020_020a2898(StackedBlock *obj);
extern int func_ov020_020a34a4(StackedBlock *obj);
extern void func_ov001_020807b4(void *model, u8 modelKind, u8 paletteId, u8 actorId, void *out, int mode, int x, int y, int z, int a, int b, int c);
extern void ApplyRecordTableEntry2(int index, u16 *counter, int arg, int count);
extern Actor *ActorRegistry_GetEntityByIndex(u32 id);
extern void RebindAnimTracks(void *target, int value, int extra);
extern void Flags16_ClearBit1(void *target);
extern void Obj_SetPosition(Actor *actor, const s32 *position);
extern void ApplyRecordTableEntry5(int index, int a, int b);
extern void SetActorExtraPosition(u32 id, StackedBlock *obj, int value);
extern void IndexedBytes_SetAt10(void *target, int a, int b);
extern int IsNodeFlagBitClear(StackedBlock *obj);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void func_ov001_0207f078(u32 bit);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void func_0202edb0(void *object, u16 *counter, int arg, int count);
extern void Flags16_SetBit1(void *object);

void LoadStackedBlockPhase(StackedBlock *obj, int phase, u16 *counter, int arg)
{
    u8 buffer[20];
    Actor *actor;
    BOOL enable;

    if ((phase == 0 && !(obj->flags & 0x200)) || (phase == 1 && (obj->flags & 0x200))) {
        if (obj->flags & 1) {
            if (func_ov020_020a2898(obj) == NULL) {
                return;
            }
            func_ov001_020807b4(obj->model, obj->def->modelKind, obj->paletteId, obj->actorId, buffer, 3, 0x1800, obj->scaleSteps * 0x1800, 0x1800, 0, 1, 0);
        } else {
            /* Forces a fresh read of the flags field */
            if (*(vu16 *)&obj->flags & 0x8000) {
                return;
            }
            func_ov001_020807b4(obj->model, obj->def->modelKind, obj->paletteId, obj->actorId, buffer, -1, 0, 0, 0, 0, 1, 0);
        }
        ApplyRecordTableEntry2(obj->actorId, counter, arg, 4);
        (*counter)++;
        actor = ActorRegistry_GetEntityByIndex(obj->actorId);
        RebindAnimTracks(&actor->drawFlags, obj->animIndex, 0);
        Flags16_ClearBit1(&actor->drawFlags);
        Obj_SetPosition(actor, obj->position);
        if (!(actor->flags & 0x20)) {
            actor->unk_80 = 0;
            actor->drawFlags |= 0x20;
        }
        ApplyRecordTableEntry5(obj->actorId, 0, 0);
        SetActorExtraPosition(obj->actorId, obj, 6);
        enable = TRUE;
        IndexedBytes_SetAt10(actor->collision, 1, 4);
        if (func_ov020_020a34a4(obj) || (obj->flags & 0x8000) || !IsNodeFlagBitClear(obj)) {
            enable = FALSE;
        }
        ActorSlot_SetFlag8ByIndex(obj->actorId, enable);
        obj->flags |= 0x40;
        IndexedBytes_SetAt10(actor->collision, 3, 0xc);
        func_ov001_0207f078(0xc);
        obj->renderFlags |= 4;
    } else if (phase == 8) {
        if (!(obj->flags & 0x8000)) {
            obj->resource = NNSi_FndAllocFromDefaultHeap(0x104);
            func_0202edb0(obj->resource, counter, arg, 4);
            RebindAnimTracks(obj->resource, 0, 0);
            Flags16_SetBit1(obj->resource);
            (*counter)++;
        }
    }
}
