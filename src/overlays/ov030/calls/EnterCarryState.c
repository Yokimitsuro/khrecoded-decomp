#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 pos;
    u8 pad_10[2];
    u16 angle;
    u8 pad_14[0x10];
    u8 unk_24;
    u8 unk_25;
    s16 duration;
    s16 prevIndex;
    s16 index;
} MarkerRequest;

typedef struct {
    u8 pad_00[2];
    u8 groupId;
    u8 pad_03[0x49];
    u16 pad_bits : 6;
    u16 visible : 1;
    u16 mode : 2;
    u16 rest_bits : 7;
} CarryModel;

typedef struct {
    u8 pad_00[8];
    s32 prevIndex;
    u8 pad_0c[0x48];
    s32 index;
    u8 pad_58[0x10];
    s32 kind;
    CarryModel *model;
    u8 pad_70[8];
    s16 *secondGroup;
    s16 *firstGroup;
    u8 secondSlot;
    u8 firstSlot;
} CarryOwner;

typedef struct CarryEntity CarryEntity;
typedef void (*EntityCallback)(CarryEntity *entity, int value, int extra);
typedef void (*EntityNotify)(CarryEntity *entity, int value);

typedef struct {
    s32 unk_00;
    fx32 speedX;
    s32 unk_08;
    fx32 speedY;
    VecFx32 offset;
    s16 scale;
} CarryMotion;

struct CarryEntity {
    u8 pad_000[0x1f8];
    EntityCallback onGroupChange;
    EntityNotify onReset;
    u8 pad_200[0x34];
    u32 stateFlags;
    u8 pad_238[0x9ac - 0x238];
    u64 flags;
    u8 markerId;
    u8 pad_9b5[0x9cc - 0x9b5];
    s32 carryHeight;
    u8 pad_9d0[0xa10 - 0x9d0];
    CarryMotion motion;
    u8 pad_a30[0xa51 - 0xa30];
    u8 carryDone;
};

typedef struct {
    u8 pad_00[0x14];
    int entryIndex;
} StateContext;

extern CarryEntity *GetBoundedEntryField(int index);
extern void ResetModelGroup(CarryModel *model);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern u8 func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern u32 GetLinkedAngleOffset(CarryEntity *entity);
extern VecFx32 *func_ov052_020ceb74(CarryEntity *entity);
extern void UpdateDraggedActorMotion(void);

static inline void NotifyGroupChange(CarryEntity *entity, int group, int extra)
{
    if (entity->onGroupChange != NULL) {
        entity->onGroupChange(entity, group, extra);
    }
}

void *EnterCarryState(StateContext *context, CarryOwner *owner, int *nextState)
{
    CarryModel *model;
    CarryMotion *motion;
    MarkerRequest request;
    CarryEntity *entity = GetBoundedEntryField(context->entryIndex);
    u32 wasVisible;

    wasVisible = entity->stateFlags & 4;
    entity->carryDone = 0;
    entity->flags |= 0x40;
    model = owner->model;
    NotifyGroupChange(entity, model->groupId + 0x2d, -1);
    if (entity->onReset != NULL) {
        entity->onReset(entity, 0);
    }
    ResetModelGroup(model);
    model->visible = wasVisible;
    model->mode = 1;
    if (owner->kind == 1) {
        model->mode = 2;
    }
    motion = &entity->motion;
    motion->speedX = 0x266;
    motion->speedY = 0x266;
    motion->scale = 0x1000;
    motion->offset.z = 0;
    motion->offset.y = 0;
    motion->offset.x = 0;
    entity->carryHeight = 0x740;
    ResetAnimationTrackState(&request);
    request.id = entity->markerId;
    request.unk_25 = 1;
    if (GetLinkedAngleOffset(entity) >= 0x8000) {
        request.angle = 0x3fff;
    } else {
        request.angle = 0xbffd;
    }
    request.duration = 5;
    request.unk_24 = 0;
    owner->firstSlot = func_ov021_020a8cc0(&request, *owner->firstGroup);
    ResetAnimationTrackState(&request);
    request.id = entity->markerId;
    request.pos = *func_ov052_020ceb74(entity);
    request.unk_24 = 0;
    request.prevIndex = owner->prevIndex;
    request.index = owner->index;
    owner->secondSlot = func_ov021_020a8cc0(&request, *owner->secondGroup);
    *nextState = 0x16;
    return UpdateDraggedActorMotion;
}
