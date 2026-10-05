#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SpawnParams {
    u16 walkerKind;
    u16 ownerSlot;
    u16 spawnArg;
    u16 attachActorId;
    u16 attach : 1;
    u16 align : 1;
    u16 attachDefault : 1;
    u16 unused : 13;
    u16 pad_0a;
    const char *nodeName;
} SpawnParams;

typedef struct {
    u8 pad_00[0xa];
    u16 eventId;
    u16 actorId;
} StageLink;

typedef struct {
    u8 pad_000[0x1d2];
    u16 spawnEnabled;
} FieldPlayer;

typedef struct {
    void *eventRecord;
    StageLink *link;
    FieldPlayer *player;
} FieldContext;

typedef struct {
    u8 pad_000[0x2e6];
    u16 attachState[4];
} StageActor;

typedef struct {
    u32 tag;
    s32 value;
} TaggedValue;

typedef struct {
    TaggedValue first;
    TaggedValue second;
    u8 pad_10[4];
    u32 mode;
    u8 position[8];
} SpawnCommand;

extern FieldContext data_ov021_020b56c4;

extern u8 *func_ov001_0209c3e8(void);
extern TaggedValue *func_ov021_020b0394(void *context, TaggedValue *value);
extern void *func_ov001_0209c114(u32 id);
extern u16 func_ov021_020b0528(void *context, u32 mode, void *operand, VecFx32 *position, const char **nodeName);
extern void func_01ff88c4(void *dest, u32 value, u32 size);
extern u16 func_ov001_0209c294(FieldPlayer *player);
extern int func_ov001_02096b08(void *eventRecord, SpawnParams *params, VecFx32 *position);
extern StageLink *func_ov001_0209c148(void);
extern StageActor *func_ov001_0209c068(int id);
extern void func_ov001_02098124(StageLink *controller);

s32 ScriptOp_SpawnStageObject(void *context, SpawnCommand *cmd)
{
    u8 *gameData = func_ov001_0209c3e8();
    TaggedValue *ownerSlot = func_ov021_020b0394(context, &cmd->first);
    TaggedValue *spawnArg = func_ov021_020b0394(context, &cmd->second);
    void *eventRecord = data_ov021_020b56c4.eventRecord;
    FieldPlayer *player = data_ov021_020b56c4.player;
    StageLink *link = data_ov021_020b56c4.link;
    const char *nodeName = NULL;
    u16 flags;
    BOOL attach;
    StageLink *controller;
    SpawnParams params;
    VecFx32 position;

    if (eventRecord == NULL && link != NULL) {
        eventRecord = func_ov001_0209c114(link->eventId);
    }
    if (player->spawnEnabled == 0) {
        return 0;
    }
    flags = func_ov021_020b0528(context, cmd->mode, cmd->position, &position, &nodeName);
    attach = FALSE;
    func_01ff88c4(&params, 0, 0x10);
    params.ownerSlot = ownerSlot->value;
    params.spawnArg = spawnArg->value;
    params.attachActorId = func_ov001_0209c294(player);
    params.nodeName = nodeName;
    if (flags & 0x18) {
        attach = TRUE;
    }
    params.attach = attach;
    params.align = (flags & 0x10) ? TRUE : FALSE;
    params.walkerKind = *(u16 *)(gameData + 0x18eb8);
    if (!func_ov001_02096b08(eventRecord, &params, &position)) {
        return 0;
    }
    controller = func_ov001_0209c148();
    if (controller == NULL) {
        return 0;
    }
    if (link != NULL && (flags & 8) && link->actorId != 0 && controller->actorId != 0) {
        StageActor *source = func_ov001_0209c068((s16)link->actorId);
        StageActor *target = func_ov001_0209c068((s16)controller->actorId);
        if (source != NULL && target != NULL) {
            target->attachState[0] = source->attachState[0];
            target->attachState[1] = source->attachState[1];
            target->attachState[2] = source->attachState[2];
            target->attachState[3] = source->attachState[3];
        }
    }
    func_ov001_02098124(controller);
    return 0;
}
