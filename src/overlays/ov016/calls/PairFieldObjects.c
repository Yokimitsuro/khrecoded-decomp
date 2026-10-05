#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x33];
    u8 slotIndex;
    u8 pad_34[0x38 - 0x34];
    VecFx32 position;
    u8 pad_44[0x77 - 0x44];
    u8 mode;
    u8 pad_78[0xbe - 0x78];
    u8 unk_BE_low : 4;
    u8 state : 4;
    u8 pad_bf;
    u32 flags;
    u8 pad_c4[0xd8 - 0xc4];
    VecFx32 pairVelocity;
    u16 pairTimer;
    u16 partnerSlot : 14;
    u16 alongZ : 1;
    u16 isLeader : 1;
} FieldObject;

extern const VecFx32 data_0205344c;
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_ov016_020a298c(FieldObject *obj, int arg);


static inline int AbsInt(int value)
{
    return (value ^ (value >> 31)) - (value >> 31);
}

void PairFieldObjects(FieldObject *first, FieldObject *second)
{
    FieldObject *leader;
    FieldObject *follower;
    VecFx32 delta;

    if (first->mode == 12 || first->mode == 14) {
        leader = first;
        follower = second;
    } else {
        leader = second;
        follower = first;
    }
    leader->state = 1;
    leader->isLeader = 1;
    leader->partnerSlot = follower->slotIndex;
    follower->state = 1;
    follower->isLeader = 0;
    follower->partnerSlot = leader->slotIndex;
    VEC_Subtract(&leader->position, &follower->position, &delta);
    func_ov016_020a298c(follower, 0);
    leader->flags &= ~0x400;
    follower->flags &= ~0x400;
    leader->pairVelocity = data_0205344c;
    leader->pairTimer = 0;
    if (AbsInt(delta.x) < AbsInt(delta.z)) {
        leader->alongZ = 1;
        follower->alongZ = 1;
    } else {
        leader->alongZ = 0;
        follower->alongZ = 0;
    }
}
