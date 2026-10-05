#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EffectSlot {
    u16 groupId;
    u16 effectId;
    u32 handle;
} EffectSlot;

typedef struct EffectEntry {
    u8 flags;
    u8 slotId;
} EffectEntry;

typedef struct ActorBody {
    VecFx32 position;
    u8 pad_0c[0xe8];
    EffectEntry effects[8];
} ActorBody;

typedef struct EffectActor {
    u8 pad_000[0x2c0];
    ActorBody body;
} EffectActor;

extern EffectSlot *func_ov001_0209c224(u32 id);
extern BOOL func_0204dc50(u32 handle);
extern void Handle_WritePayloadIfLive(u32 handle, VecFx32 *position);
extern void func_ov001_02091ae8(EffectActor *actor, u16 groupId, u16 effectId, int mode);

void UpdateActorAttachedEffects(EffectActor *actor)
{
    ActorBody *body = &actor->body;
    int i;

    for (i = 0; i < 8; i++) {
        EffectEntry *entry = &actor->body.effects[i];
        EffectSlot *slot;

        if (entry->slotId != 0) {
            slot = func_ov001_0209c224(entry->slotId);
            if (slot != NULL) {
                if (func_0204dc50(slot->handle)) {
                    if (entry->flags & 4) {
                        Handle_WritePayloadIfLive(slot->handle, &body->position);
                    }
                } else {
                    func_ov001_02091ae8(actor, slot->groupId, slot->effectId, 0);
                }
            }
        }
    }
}
