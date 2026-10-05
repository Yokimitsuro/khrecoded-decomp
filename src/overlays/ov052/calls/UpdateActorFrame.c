#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FrameActor FrameActor;
typedef void (*ActorEventFunc)(FrameActor *actor, int event);
typedef void (*ActorHookFunc)(FrameActor *actor);

typedef struct {
    u16 pad_00;
    u16 count;
} CursorState;

typedef struct {
    u8 pad_0000[0x27b6];
    u8 reserved0 : 4;
    u8 skipEvents : 1;
    u8 reserved5 : 3;
} FieldState;

struct FrameActor {
    u8 pad_000[0x1d4];
    CursorState *cursor;
    u8 pad_1d8[0x9ac - 0x1d8];
    u64 stateFlags;
    u8 pool;
    u8 pad_9b5[0x9c0 - 0x9b5];
    int mode;
    fx32 speed;
    u8 pad_9c8[0x9ec - 0x9c8];
    int delta;
    u8 pad_9f0[0x1048 - 0x9f0];
    u8 menuState[0x105c - 0x1048];
    u8 activeBlock[0x10ec - 0x105c];
    ActorEventFunc onEvent;
    ActorHookFunc preUpdate;
};

extern FieldState *data_ov001_020a0480;
extern void CheckFallOutOfBounds(FrameActor *actor);
extern fx32 func_ov001_0206db44(void);
extern void TickActorTimers(FrameActor *actor);
extern void UpdateDriveGaugeCharge(FrameActor *actor);
extern void ReadActiveMenuState(void *state);
extern BOOL func_ov001_020645c8(int id);
extern int func_ov001_02063a38(void);
extern void SetClampedCursor(FrameActor *actor, int value);
extern void func_ov052_020ca33c(FrameActor *actor, void *block, int delta);

void UpdateActorFrame(FrameActor *actor)
{
    BOOL allowEvent;

    if (actor->preUpdate != NULL) {
        actor->preUpdate(actor);
    }
    CheckFallOutOfBounds(actor);
    actor->speed += func_ov001_0206db44();
    TickActorTimers(actor);
    UpdateDriveGaugeCharge(actor);
    if ((actor->stateFlags & 0x400) == 0) {
        ReadActiveMenuState(actor->menuState);
    }
    if ((actor->stateFlags & 0x800) == 0) {
        allowEvent = TRUE;
        if (actor->mode == 15) {
            allowEvent = FALSE;
        }
        if (data_ov001_020a0480->skipEvents || func_ov001_020645c8(0x3525)) {
            if (actor->pool == 0 && func_ov001_02063a38() != 4 && actor->cursor->count == 0) {
                SetClampedCursor(actor, 1);
            }
            allowEvent = FALSE;
        }
        if (allowEvent && (actor->cursor->count == 0 || func_ov001_020645c8(0x3625))) {
            actor->onEvent(actor, 15);
            return;
        }
    }
    func_ov052_020ca33c(actor, actor->activeBlock, actor->delta);
}
