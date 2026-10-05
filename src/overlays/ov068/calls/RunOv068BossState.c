#include "nitro/types.h"

typedef struct Actor Actor;
typedef void (*ActorStateFunc)(Actor *actor);

typedef struct {
    ActorStateFunc func;
    int id;
    int arg;
} ActorState;

typedef struct {
    u8 id;
    u8 pad_01[0x11];
    u16 flags;
    u8 pad_14[0x10];
    s8 level;
    u8 layer;
    u8 pad_26[2];
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct {
    u8 pad_00[8];
    int soundId;
    u8 pad_0c[0x40];
    s16 emitter;
    u8 pad_4e[0x1e];
    u8 *parts;
    u8 pad_70[0x11];
    s8 soundHandle;
    u8 pad_82[2];
    u8 cameraPath[0x60];
    ActorState saved;
    u8 pad_f0[4];
    int phase;
} BossObject;

typedef struct {
    u8 pad_00[0x12];
    u16 command;
} InputUnit;

struct Actor {
    u8 pad_000[0x1f8];
    void (*notify)(Actor *actor, int arg1, int arg2);
    void (*onLand)(Actor *actor, int frame);
    u8 pad_200[0x234 - 0x200];
    u32 modeFlags;
    u8 pad_238[0x760 - 0x238];
    int frame;
    u8 pad_764[4];
    BOOL finished;
    u8 pad_76c[0x9ac - 0x76c];
    u64 flags;
    u8 player;
    u8 pad_9b5[7];
    ActorState state;
    u8 pad_9c8[0xa51 - 0x9c8];
    s8 level;
    u8 pad_a52[0xb2c - 0xa52];
    u8 sound[0x1078 - 0xb2c];
    BossObject *boss;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setMode)(Actor *actor, int mode);
};

extern const int data_ov068_020d8674[];
extern InputUnit *func_ov001_0206db78(int player);
extern u16 SharedObject_GetId(InputUnit *unit);
extern int SharedObject_GetMode(InputUnit *unit);
extern int GetSubObjectValue(void *part, int arg1, int arg2);
extern BOOL func_ov001_02072040(void);
extern BOOL UpdateIdleTimeout(void);
extern void CameraPath_Start(void *path);
extern void RestartScriptSound(void *sound, int arg);
extern void ActivateSlotModelGroup(Actor *actor, int level);
extern void func_ov056_020d3418(Actor *actor);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
void RunOv068BossState(Actor *actor);

void RunOv068BossState(Actor *actor)
{
    BossObject *boss = actor->boss;
    int offset;
    u8 *parts = boss->parts;
    InputUnit *unit;
    MarkerRequest request;
    BOOL apply;
    int value;
    int emitter;
    u32 hasMode;

    offset = actor->level * 0x90;
    unit = func_ov001_0206db78(actor->player);
    if (SharedObject_GetId(unit) == 5) {
        switch (SharedObject_GetMode(unit)) {
        case 1:
            boss->phase = 2;
            break;
        case 3:
            boss->phase = 1;
            break;
        case 4:
            boss->phase = 3;
            break;
        case 0:
        case 2:
            break;
        }
        unit->command = 0;
    }
    if (boss->saved.id == 0x18 && actor->frame < GetSubObjectValue(parts + offset, 1, 1)) {
        goto launch;
    }
    apply = FALSE;
    switch (boss->phase) {
    default:
        boss->phase = 0;
    case 0:
        if (func_ov001_02072040() && !UpdateIdleTimeout()) {
            break;
        }
        if (boss->saved.id == 0x18) {
            actor->finished = TRUE;
            break;
        }
        if (actor->modeFlags & 4) {
            actor->setMode(actor, 1);
            if (actor->notify != NULL) {
                actor->notify(actor, 0, -1);
            }
        } else {
            actor->setMode(actor, 4);
        }
        return;
    case 1:
        actor->level = 0;
        boss->phase = 6;
        apply = TRUE;
        break;
    case 2:
        apply = TRUE;
        actor->level = 1;
        boss->phase = 6;
        break;
    case 3:
        CameraPath_Start(boss->cameraPath);
        RestartScriptSound(actor->sound, 0);
        actor->level = 2;
        boss->phase = 0;
        apply = TRUE;
        break;
    case 4:
        actor->state.id = 0;
        actor->setMode(actor, 1);
        boss->saved = actor->state;
        boss->phase = 0;
        break;
    case 5:
        actor->state.id = 0;
        actor->setMode(actor, 4);
        boss->saved = actor->state;
        boss->phase = 0;
        break;
    case 6:
        hasMode = actor->modeFlags & 4;
        actor->state.id = 0;
        if (hasMode) {
            actor->setMode(actor, 5);
        } else {
            actor->setMode(actor, 4);
        }
        boss->saved = actor->state;
        boss->phase = 0;
        actor->flags &= ~0x200000000ULL;
        break;
    }
    if (apply) {
        ActivateSlotModelGroup(actor, actor->level);
        value = GetSubObjectValue(boss->parts + actor->level * 0x90, 1, 0);
        if (actor->onLand != NULL) {
            if (value <= 0) {
                value = 0;
            }
            actor->onLand(actor, value);
        }
        boss->saved.func = func_ov056_020d3418;
        boss->saved.id = 0x18;
        actor->flags |= 0x200000000ULL;
        boss->soundHandle = -1;
    }
launch:
    if (boss->saved.id == 0x18) {
        emitter = boss->emitter;
        if (boss->soundHandle == -1 && actor->frame >= data_ov068_020d8674[actor->level]) {
            ResetAnimationTrackState(&request);
            request.id = actor->player;
            request.layer = 1;
            request.flags = 0x8000;
            request.level = actor->level;
            if (actor->level == 2) {
                request.soundId = boss->soundId;
                request.delay = 0;
            }
            boss->soundHandle = func_ov021_020a8cc0(&request, emitter);
        }
    }
    actor->state.id = boss->saved.id;
    boss->saved.func(actor);
    if (actor->boss == boss) {
        if (actor->state.func != RunOv068BossState) {
            boss->saved = actor->state;
        }
        actor->state.func = RunOv068BossState;
        actor->state.id = 0x18;
    }
}
