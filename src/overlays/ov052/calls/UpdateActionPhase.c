#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PhaseActor PhaseActor;
typedef void (*ActorEventFunc)(PhaseActor *actor, int event);

typedef struct {
    u8 pad_00[0x2c];
    int threshold;
    u8 pad_30[0x4c - 0x30];
    u16 phase : 2;
    u16 reserved2 : 1;
    u16 held : 1;
    u16 reserved4 : 2;
    u16 released : 1;
    u16 reserved7 : 9;
} PhaseData;

struct PhaseActor {
    u8 pad_000[0x234];
    u32 modelFlags;
    u8 pad_238[0x760 - 0x238];
    int frame;
    u8 pad_764[4];
    int eventFlag;
    u8 pad_76c[0x9c4 - 0x76c];
    fx32 speed;
    u8 pad_9c8[4];
    fx32 velocityY;
    u8 pad_9d0[0x1030 - 0x9d0];
    int actionKind;
    u8 pad_1034[0x10ec - 0x1034];
    ActorEventFunc onEvent;
};

extern void SetActorPaused(PhaseActor *actor, int paused);
extern int GetSubObjectValue(void *owner, int which, int index);

BOOL UpdateActionPhase(PhaseActor *actor, PhaseData *data, int which)
{
    int threshold = data->threshold;

    if (threshold > 0 && data->phase == 0 && actor->frame >= threshold) {
        data->phase = 1;
        SetActorPaused(actor, 1);
    }
    if (!(actor->modelFlags & 4)) {
        if (data->released && !data->held) {
            actor->onEvent(actor, 4);
            return TRUE;
        }
        if (threshold != 0 && data->phase == 1 && actor->speed >= threshold + 0x3c000) {
            SetActorPaused(actor, 0);
            data->phase = 2;
            actor->velocityY = 0;
        }
    } else if (threshold != 0) {
        data->phase = 2;
        SetActorPaused(actor, 0);
    }
    if (actor->frame >= GetSubObjectValue(data, which, 1)) {
        switch (actor->actionKind) {
        case 0:
            break;
        case 1:
        case 6:
        case 7:
            actor->eventFlag = 1;
            break;
        default:
            actor->eventFlag = 1;
            break;
        }
    }
    return FALSE;
}
