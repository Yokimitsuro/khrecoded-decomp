#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroundLink {
    u8 pad_00[0x13];
    u8 surface;
} GroundLink;

typedef struct GroundFloor {
    u8 pad_00[0x83];
    u8 surface;
} GroundFloor;

typedef struct ActorPhysics {
    u8 pad_00[0x4];
    GroundFloor *floor;
    u8 pad_08[0x10 - 0x8];
    GroundLink *link;
    u8 pad_14[0xbc - 0x14];
    fx32 groundY;
    u8 pad_c0[0xc4 - 0xc0];
    int groundType;
} ActorPhysics;

typedef struct Actor {
    u8 pad_0000[0x274];
    ActorPhysics physics;
    u8 pad_033c[0x930 - 0x33c];
    u8 playerIndex;
    u8 pad_0931[0x93c - 0x931];
    int state;
    u8 pad_0940[0x1730 - 0x940];
    int voiceCount;
    int voiceHandle;
} Actor;

extern VecFx32 *Actor_GetModelPosition(Actor *actor);
extern int LookupKindTableValue(int state, int surface);
extern BOOL Actor_AnyAnimSlotBusy(Actor *actor);
extern int SpawnSoundSlot(int sound, int variant, VecFx32 *pos, int flags);

int Actor_PlaySurfaceSound(Actor *actor, int sound, int variant) {
    int result = 0;
    int surface;

    if (sound == 4 || sound == 0x15 || sound == 0x23) {
        ActorPhysics *physics = &actor->physics;
        VecFx32 *pos = Actor_GetModelPosition(actor);
        surface = -1;
        sound = -1;
        if (pos->y - physics->groundY < 0x3000) {
            switch (physics->groundType) {
            case 1:
                if (physics->link != NULL) {
                    surface = physics->link->surface;
                }
                break;
            case 2:
                if (physics->floor != NULL) {
                    surface = physics->floor->surface;
                }
                break;
            }
        }
        if (surface >= 0) {
            sound = LookupKindTableValue(actor->state, surface);
        }
    }
    if (actor->state == 3 && variant == 0x1f && !Actor_AnyAnimSlotBusy(actor)) {
        sound = -1;
        variant = -1;
    }
    if (sound == 0x30 && actor->voiceCount > 0) {
        return actor->voiceHandle;
    }
    if (sound >= 0 && variant >= 0) {
        if (actor->playerIndex == 0) {
            result |= 1;
        }
        result = SpawnSoundSlot(sound, variant, Actor_GetModelPosition(actor), result);
    }
    return result;
}
