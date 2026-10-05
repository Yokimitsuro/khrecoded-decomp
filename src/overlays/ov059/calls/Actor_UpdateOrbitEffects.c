#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct OrbitSlot {
    fx32 angle;
    fx32 radius;
} OrbitSlot;

typedef struct Actor {
    u8 pad_0000[0x1738];
    VecFx32 orbitCenter;
    OrbitSlot *orbitSlots;
    u8 pad_1748[0x1812 - 0x1748];
    s16 effectGroupId;
} Actor;

typedef struct EffectEntry {
    u8 pad_00[0xa4];
    VecFx32 position;
} EffectEntry;

extern EffectEntry *GetGroupMemberData(s32 groupId, s32 entryIndex);
extern void func_ov059_020cac58(OrbitSlot *slot, VecFx32 *offset);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

void Actor_UpdateOrbitEffects(Actor *actor)
{
    s32 i;
    VecFx32 position;

    for (i = 0; i < 7; i++) {
        EffectEntry *entry = GetGroupMemberData(actor->effectGroupId, i);
        func_ov059_020cac58(&actor->orbitSlots[i], &position);
        VEC_Add(&position, &actor->orbitCenter, &position);
        entry->position = position;
    }
}
