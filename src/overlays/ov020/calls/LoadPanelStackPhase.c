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
    u8 pad_48;
    s8 stackCount;
} PanelStack;

typedef struct {
    u32 flags;
    u16 drawFlags;
    u8 pad_06[0x7a];
    u16 unk_80;
    u8 pad_82[0x8a];
    u8 collision[4];
} Actor;

extern void func_ov001_020807b4(void *model, u8 modelKind, u8 paletteId, u8 actorId, void *out, int mode, int x, int y, int z, int a, int b, int c);
extern void ApplyRecordTableEntry2(int index, u16 *counter, int arg, int count);
extern Actor *ActorRegistry_GetEntityByIndex(u32 id);
extern void RebindAnimTracks(void *target, int value, int extra);
extern void Flags16_ClearBit1(void *target);
extern void Obj_SetPosition(Actor *actor, const s32 *position);
extern void ApplyRecordTableEntry5(int index, int a, int b);
extern void IndexedBytes_SetAt10(void *target, int a, int b);
extern int IsNodeFlagBitClear(PanelStack *obj);
extern void func_ov001_0207f078(u32 bit);

void LoadPanelStackPhase(PanelStack *obj, int phase, u16 *counter, int arg)
{
    u8 buffer[20];
    Actor *actor;

    if (phase == 2) {
        func_ov001_020807b4(obj->model, obj->def->modelKind, obj->paletteId, obj->actorId, buffer, 3, 0x1800, obj->stackCount * 0x1800, 0x1800, 0, 1, 0);
        ApplyRecordTableEntry2(obj->actorId, counter, arg, 4);
        (*counter)++;
        actor = ActorRegistry_GetEntityByIndex(obj->actorId);
        Obj_SetPosition(actor, obj->position);
        if (!(actor->flags & 0x20)) {
            actor->unk_80 = 0;
            actor->drawFlags |= 0x20;
        }
        RebindAnimTracks(&actor->drawFlags, obj->animIndex, 0);
        Flags16_ClearBit1(&actor->drawFlags);
        if (IsNodeFlagBitClear(obj)) {
            ApplyRecordTableEntry5(obj->actorId, 0, 0);
        }
        IndexedBytes_SetAt10(actor->collision, 1, 4);
        IndexedBytes_SetAt10(actor->collision, 3, 0xc);
        func_ov001_0207f078(0xc);
        obj->renderFlags |= 4;
    }
}
