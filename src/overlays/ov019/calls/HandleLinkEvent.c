#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactHandler {
    void *func;
    void *context;
} ContactHandler;

typedef struct ActorNode {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x80 - 0x06];
    u16 animTimer;
    u8 pad_82[0x10c - 0x82];
    u8 collision[0x80];
    ContactHandler contact;
} ActorNode;

typedef struct LinkEffect {
    u16 flags;
    u8 pad_02[0x7c - 0x02];
    u16 timer;
    u8 pad_7e[0xa4 - 0x7e];
    VecFx32 position;
} LinkEffect;

typedef struct LinkOwner {
    u8 pad_00[0x59];
    u8 listId;
    u8 pad_5a[0x68 - 0x5a];
    LinkEffect *effect;
} LinkOwner;

typedef struct ShapeInfo {
    u8 data[0x14];
} ShapeInfo;

typedef struct Actor {
    u8 pad_00[4];
    LinkOwner *owner;
    void *entity;
    u8 pad_0c[0x30 - 0x0c];
    u16 renderFlags;
    u8 actorId;
    u8 slotIndex;
    u8 pad_34[4];
    VecFx32 position;
    u8 pad_44[3];
    s8 animIndex;
    LinkEffect *effect;
    u8 pad_4c[6];
    u8 kind;
    u8 pad_53[7];
    u16 flags;
} Actor;

extern BOOL IsDestroyed(Actor *self);
extern void CacheEntry_SetActive(Actor *self, int active);
extern void func_ov001_020807b4(void *entity, u8 listId, u8 slotIndex, u8 actorId, ShapeInfo *info, int kind,
                                fx32 sizeX, fx32 sizeY, fx32 sizeZ, int angle, int allocate, int mode);
extern void ApplyRecordTableEntry2(u8 actorId, u16 *counter, int arg, int mode);
extern ActorNode *ActorRegistry_GetEntityByIndex(u8 actorId);
extern void RebindAnimTracks(void *anim, int blendIndex, int frame);
extern void Flags16_ClearBit1(void *anim);
extern void Flags16_SetBit1(void *anim);
extern void Obj_SetPosition(ActorNode *node, const VecFx32 *position);
extern void ApplyRecordTableEntry5(u8 actorId, int a1, int a2);
extern void SetActorExtraPosition(u8 actorId, Actor *self, int mode);
extern void IndexedBytes_SetAt10(void *collision, int mode, int flags);
extern BOOL IsNodeFlagBitClear(Actor *self);
extern void ActorSlot_SetFlag8ByIndex(int index, BOOL enable);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void func_0202edb0(void *object, u16 *counter, int arg, int mode);
extern void ResizeBoxCollisionObject(void *object, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle);
extern void func_ov001_0207f078(int mode);
extern void FieldObject_HandlePushContact(void);

static inline ContactHandler MakeHandler(void *func, void *context)
{
    ContactHandler handler;
    handler.func = func;
    handler.context = context;
    return handler;
}

void HandleLinkEvent(Actor *self, int event, u16 *counter, int arg)
{
    LinkOwner *owner = self->owner;
    ActorNode *node;
    BOOL enable;
    LinkEffect *effect;
    ShapeInfo info;

    if ((event == 0 && !(self->flags & 0x600)) || (event == 1 && (self->flags & 0x200)) ||
        (event == 10 && (self->flags & 0x400))) {
        if (IsDestroyed(self)) {
            return;
        }
        CacheEntry_SetActive(self, 1);
        func_ov001_020807b4(self->entity, self->owner->listId, self->slotIndex, self->actorId, &info, 3, 0x1800,
                            0x1800, 0x1800, 0, 1, 0);
        ApplyRecordTableEntry2(self->actorId, counter, arg, 4);
        (*counter)++;
        node = ActorRegistry_GetEntityByIndex(self->actorId);
        RebindAnimTracks(&node->animFlags, self->animIndex, 0);
        Flags16_ClearBit1(&node->animFlags);
        Obj_SetPosition(node, &self->position);
        if (!(node->flags & 0x20)) {
            node->animTimer = 0;
            node->animFlags |= 0x20;
        }
        ApplyRecordTableEntry5(self->actorId, 0, 0);
        SetActorExtraPosition(self->actorId, self, 0xc);
        enable = TRUE;
        IndexedBytes_SetAt10(node->collision, 1, 4);
        if (IsDestroyed(self) || !IsNodeFlagBitClear(self)) {
            enable = FALSE;
        }
        ActorSlot_SetFlag8ByIndex(self->actorId, enable);
        self->flags |= 0x40;
        IndexedBytes_SetAt10(node->collision, 3, 0xc);
        self->renderFlags |= 4;
        if (!(self->flags & 0x100)) {
            if (self->flags & 0x400) {
                self->kind = 10;
            } else if (self->flags & 0x200) {
                self->kind = 1;
            } else {
                self->kind = 0;
            }
        }
    } else if ((event == 2 && !(self->flags & 0x800)) || (event == 3 && (self->flags & 0x800))) {
        if (!(self->flags & 0x100) || IsDestroyed(self)) {
            return;
        }
        CacheEntry_SetActive(self, 1);
        node = ActorRegistry_GetEntityByIndex(self->actorId);
        self->effect = NNSi_FndAllocFromDefaultHeap(0x104);
        func_0202edb0(self->effect, counter, arg, 4);
        if (!(self->flags & 0x80)) {
            self->animIndex = 0;
            RebindAnimTracks(self->effect, self->animIndex, 0);
            Flags16_SetBit1(self->effect);
        } else {
            self->animIndex = 1;
            RebindAnimTracks(&node->animFlags, self->animIndex, 0);
            Flags16_ClearBit1(&node->animFlags);
        }
        self->effect->position = self->position;
        effect = self->effect;
        effect->timer = 0;
        effect->flags |= 0x20;
        (*counter)++;
        if (self->flags & 0x800) {
            node->contact = MakeHandler(FieldObject_HandlePushContact, self);
            self->kind = 3;
            ResizeBoxCollisionObject(node->collision, 0x1333, 0x1800, 0x1333, 0);
            Obj_SetPosition(node, &self->position);
        } else {
            self->kind = 2;
        }
        IndexedBytes_SetAt10(node->collision, 3, 0xc);
        func_ov001_0207f078(0xc);
        self->flags |= 0x100;
    } else if (event == 8 && !IsDestroyed(self) && owner->effect == NULL) {
        owner->effect = NNSi_FndAllocFromDefaultHeap(0x104);
        func_0202edb0(owner->effect, counter, arg, 4);
        RebindAnimTracks(owner->effect, 0, 0);
        Flags16_SetBit1(owner->effect);
        (*counter)++;
    }
}
