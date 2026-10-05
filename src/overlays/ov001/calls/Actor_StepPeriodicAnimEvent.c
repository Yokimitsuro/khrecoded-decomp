#include "nitro/types.h"

typedef struct AnimObject {
    u32 unk_00;
    u16 frameData[1];
} AnimObject;

typedef struct ActorBody {
    AnimObject *anim;
} ActorBody;

typedef struct Actor {
    u32 unk_000;
    int eventPeriod;
    int eventId;
    u8 pad_00c[0xd18 - 0xc];
    ActorBody *body;
    u8 pad_d1c[0xef4 - 0xd1c];
    u32 flags;
} Actor;

extern void QueueActorAnimEvent(Actor *actor);
extern int Anim_GetFrame(u16 *frameData, int arg);
extern s64 _s32_div_f(int numerator, int denominator);
extern void PlayActorBodySound(Actor *actor, int eventId);

void Actor_StepPeriodicAnimEvent(Actor *actor)
{
    int frame;

    if (actor->flags & 0x100) {
        QueueActorAnimEvent(actor);
        return;
    }
    frame = Anim_GetFrame(actor->body->anim->frameData, 0) >> 12;
    if ((int)(_s32_div_f(frame, actor->eventPeriod) >> 32) == 0 && frame != 0) {
        PlayActorBodySound(actor, actor->eventId);
    }
}
