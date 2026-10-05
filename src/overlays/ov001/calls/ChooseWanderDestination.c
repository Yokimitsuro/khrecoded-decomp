#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x1d0];
    u16 moveMode;
    u8 pad_1d2[0xee];
    VecFx32 position;
    VecFx32 destination;
} WanderActor;

typedef struct {
    u8 pad_000[0xc];
    u8 kind;
    u8 pad_00d[3];
    u16 actorId;
    u8 pad_012[0x192];
    s32 timer;
    u8 pad_1a8[4];
    s32 retargeted;
} WanderEntry;

typedef struct {
    u8 pad_00[0x10];
    s16 actorId;
} StageEventRecord;

extern int func_ov001_0209c250(WanderEntry *entry);
extern void func_ov001_02091840(WanderActor *actor);
extern int func_ov001_02096a2c(WanderEntry *target, int mode);
extern u32 random_next_scaled(u32 range);
extern StageEventRecord *func_ov001_0209c114(u32 id);
extern WanderActor *func_ov001_0209c068(int id);
extern void func_ov001_0209265c(fx32 length, VecFx32 *out);

void ChooseWanderDestination(WanderEntry *entry, WanderActor *actor, VecFx32 *destination)
{
    int row = func_ov001_0209c250(entry);
    WanderActor *other;
    int nearest;
    VecFx32 offset;

    func_ov001_02091840(actor);
    if (entry->kind != 5) {
        return;
    }
    if (actor->moveMode == 1) {
        if (entry->timer % 0x1e000 == 0) {
            nearest = func_ov001_02096a2c(entry, 0);
            entry->retargeted = 1;
            if (nearest != 0 && row != nearest && random_next_scaled(100) < 50) {
                other = func_ov001_0209c068(func_ov001_0209c114(nearest)->actorId);
                destination->x = other->position.x;
                destination->z = other->position.z;
            } else {
                func_ov001_0209265c(0x2000, &offset);
                destination->x = actor->position.x + offset.x;
                destination->z = actor->position.z + offset.z;
            }
        } else {
            destination->x = actor->destination.x;
            destination->z = actor->destination.z;
        }
    } else {
        if (entry->actorId == 0) {
            goto store;
        }
        other = func_ov001_0209c068((s16)entry->actorId);
        if (other == 0) {
            goto store;
        }
        destination->x = other->destination.x;
        destination->z = other->destination.z;
    }
store:
    actor->destination.x = destination->x;
    actor->destination.z = destination->z;
}
