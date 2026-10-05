#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
} TargetSource;

typedef struct {
    u8 pad_00[0x24];
    VecFx32 *position;
} TargetNode;

typedef struct {
    u8 pad_000[0x10c];
    TargetNode node;
} TargetActor;

typedef struct {
    union {
        TargetSource *source;
        struct {
            u16 eventId;
            u16 slot;
        } event;
    } u;
    s32 kind;
} TargetKey;

extern const VecFx32 data_0205344c;
extern TargetActor *ActorRegistry_GetEntityByIndex(int id);
extern int QueryStageEventPlacement(u32 id, int arg, VecFx32 *position, u16 *direction);

void TargetKey_GetPosition(VecFx32 *out, TargetKey *key)
{
    VecFx32 position;
    TargetNode *node;

    switch (key->kind) {
    case 1:
        node = &ActorRegistry_GetEntityByIndex(key->u.source->actorId)->node;
        *out = *node->position;
        break;
    case 2:
        QueryStageEventPlacement(key->u.event.eventId, key->u.event.slot, &position, NULL);
        *out = position;
        break;
    default:
        *out = data_0205344c;
        break;
    }
}
