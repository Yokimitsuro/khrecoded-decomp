#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MotionBody {
    u8 pad_00[0xa8];
    VecFx32 position;
} MotionBody;

typedef struct MotionLink {
    MotionBody *body;
    u32 unk04;
    VecFx32 velocity;
} MotionLink;

typedef struct PartyActor {
    u8 pad_000[0x84c];
    VecFx32 move;
    void *pendingPath;
    u8 pad_85c[0xd18 - 0x85c];
    MotionLink *link;
    u8 pad_d1c[0xef4 - 0xd1c];
    u32 flags;
} PartyActor;

extern const VecFx32 data_0205344c;
extern void func_ov001_020893bc(PartyActor *actor);
extern void func_ov001_02089bfc(PartyActor *actor);
extern void func_ov001_02089230(PartyActor *actor, VecFx32 *out);
extern void func_ov001_02089ad0(PartyActor *actor);
extern void Actor_StepPeriodicAnimEvent(PartyActor *actor);
extern void AlignPartyLeaderToActor(PartyActor *actor);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern void func_02038e80(MotionLink *link, int mode);
extern void Obj_SetPosition(MotionBody *body, const VecFx32 *position);

static inline void SetGroundVelocity(MotionLink *link, const VecFx32 *velocity)
{
    link->velocity.x = velocity->x;
    link->velocity.y = 0;
    link->velocity.z = velocity->z;
}

void UpdatePartyActorMotion(PartyActor *actor)
{
    VecFx32 drift;
    VecFx32 position;
    u32 flags;

    drift.z = 0;
    drift.y = 0;
    drift.x = 0;
    flags = actor->flags;
    if (flags & 0x200) {
        func_ov001_020893bc(actor);
        flags = actor->flags;
        if (flags == 0) {
            return;
        }
    }
    if ((flags & 0x20) || (flags & 0x4000)) {
        return;
    }
    func_ov001_02089bfc(actor);
    if (actor->flags & 0x40) {
        func_ov001_02089230(actor, &drift);
        VEC_Add(&drift, &actor->move, &drift);
        if (VEC_Mag(&drift) <= 0x10) {
            drift.z = 0;
            drift.y = 0;
            drift.x = 0;
        }
        SetGroundVelocity(actor->link, &drift);
    }
    if (actor->pendingPath != NULL) {
        func_ov001_02089ad0(actor);
    }
    if (actor->flags & 0x10) {
        if (VEC_Mag(&actor->move) != 0 || VEC_Mag(&drift) != 0) {
            func_02038e80(actor->link, 0);
        }
    } else if (VEC_Mag(&actor->move) != 0 || VEC_Mag(&drift) != 0) {
        position = actor->link->body->position;
        if (VEC_Mag(&drift) != 0) {
            VEC_Add(&position, &drift, &position);
        } else {
            VEC_Add(&position, &actor->move, &position);
        }
        Obj_SetPosition(actor->link->body, &position);
    }
    if (actor->flags & 0x80) {
        Actor_StepPeriodicAnimEvent(actor);
    }
    if (actor->flags & 0x800) {
        AlignPartyLeaderToActor(actor);
    }
    SetGroundVelocity(actor->link, &data_0205344c);
}
