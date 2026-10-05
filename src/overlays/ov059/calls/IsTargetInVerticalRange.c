#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackedObject {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x50 - 0x33];
    u16 flags;
    s8 hidden;
    u8 pad_53[0xa0 - 0x53];
    int state;
} TrackedObject;

typedef struct TargetRef {
    union {
        TrackedObject *object;
        struct {
            u16 eventId;
            u16 subId;
        } event;
    } u;
    int type;
} TargetRef;

typedef struct ActorBody {
    u8 pad_00[0x24];
    VecFx32 *position;
} ActorBody;

typedef struct ActorNode {
    u8 pad_000[0x10c];
    ActorBody body;
} ActorNode;

extern ActorNode *ActorRegistry_GetEntityByIndex(u32 actorId);
extern fx32 func_ov031_020bc720(void);
extern int func_ov001_02087ca0(u32 id);
extern int func_ov001_02087c14(u32 id, int arg, VecFx32 *position, u16 *direction);

BOOL IsTargetInVerticalRange(TargetRef *ref) {
    switch (ref->type) {
    case 1: {
        TrackedObject *object = ref->u.object;
        if (object->hidden == 0 && !(object->flags & 8) && object->state != 2) {
            ActorBody *body = &ActorRegistry_GetEntityByIndex(object->actorId)->body;
            VecFx32 *pos = body->position;
            if (pos->z <= 0x3000 && pos->z > -func_ov031_020bc720() - 0xc00) {
                return TRUE;
            }
        }
        break;
    }
    case 2:
        if (func_ov001_02087ca0(ref->u.event.eventId)) {
            VecFx32 pos;
            func_ov001_02087c14(ref->u.event.eventId, ref->u.event.subId, &pos, NULL);
            if (pos.z <= 0x3000 && pos.z > -func_ov031_020bc720() - 0xc00) {
                return TRUE;
            }
        }
        break;
    }
    return FALSE;
}
