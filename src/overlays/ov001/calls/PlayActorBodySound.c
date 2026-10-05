#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Entity {
    u8 pad[0xa8];
    VecFx32 position;
} Entity;

typedef struct ActorBody {
    Entity *entity;
} ActorBody;

typedef struct ScriptActor {
    u8 pad0[0xc];
    int soundToggle;
    u8 pad10[0xd08];
    ActorBody *body;
} ScriptActor;

extern int RestoreActorPositionMode(ScriptActor *actor);
extern u32 SpawnSoundSlot(u32 owner, u32 kind, VecFx32 *position, u32 flags);

void PlayActorBodySound(ScriptActor *actor, u32 kind) {
    VecFx32 position = actor->body->entity->position;
    int offset = 0;
    int bank = RestoreActorPositionMode(actor);
    int toggle;

    switch (kind) {
    case 0:
        break;
    case 1:
        offset = 0;
        break;
    case 2:
        offset = 5;
        break;
    case 3:
        offset = 4;
        break;
    case 4:
    case 5:
        break;
    }
    toggle = actor->soundToggle;
    actor->soundToggle = (toggle == 0);
    SpawnSoundSlot(bank, offset + toggle, &position, 0);
}
