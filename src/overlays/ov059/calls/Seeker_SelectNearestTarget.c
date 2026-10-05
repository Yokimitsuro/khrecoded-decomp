#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ObjectInfo {
    u8 pad_00[0x5a];
    u8 category;
} ObjectInfo;

typedef struct FieldObject {
    struct FieldObject *next;
    ObjectInfo *info;
    u8 pad_08[0x32 - 0x8];
    u8 actorId;
} FieldObject;

typedef struct TargetRef {
    union {
        FieldObject *object;
        struct {
            u16 eventId;
            u16 subId;
        } event;
    } u;
    int type;
} TargetRef;

typedef struct ActorBody {
    u8 pad_00[0x18];
    VecFx32 position;
} ActorBody;

typedef struct ActorNode {
    u8 pad_000[0x10c];
    ActorBody body;
} ActorNode;

typedef struct LockOn {
    u8 pad_00[0x10];
    TargetRef target;
} LockOn;

typedef struct Seeker {
    u8 pad_000[0xd4];
    VecFx32 position;
    u8 pad_0e0[0x150 - 0xe0];
    LockOn *lock;
} Seeker;

extern FieldObject *func_ov001_02087264(void);
extern BOOL IsTargetInVerticalRange(TargetRef *ref);
extern ActorNode *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern u16 func_ov001_02087950(void);
extern u16 func_ov001_0208796c(u16 startIndex);
extern int func_ov001_02087c14(u32 id, int arg, VecFx32 *position, u16 *next);

void Seeker_SelectNearestTarget(Seeker *seeker) {
    VecFx32 eventPos;
    VecFx32 diff;
    VecFx32 offset;
    VecFx32 eventDiff;
    VecFx32 eventOffset;
    TargetRef ref;
    TargetRef eventRef;
    TargetRef candidate;
    TargetRef eventCandidate;
    u16 next;
    VecFx32 *origin;
    fx64 best;
    LockOn *lock = seeker->lock;
    FieldObject *object;
    u16 event;
    u16 sub;

    origin = &seeker->position;
    best = 0x7fffffffffffffffLL;
    lock->target.type = 0;
    for (object = func_ov001_02087264(); object != NULL; object = object->next) {
        if (object->info->category == 6) {
            candidate.u.object = object;
            candidate.type = 1;
            ref = candidate;
            if (IsTargetInVerticalRange(&ref)) {
                fx64 dist;
                ActorBody *body = &ActorRegistry_GetEntityByIndex(object->actorId)->body;
                func_01ff9e3c(&body->position, origin, &diff);
                offset = diff;
                dist = VEC_DotProduct(&offset, &offset);
                if (dist < best) {
                    best = dist;
                    lock->target = candidate;
                }
            }
        }
    }
    for (event = func_ov001_02087950(); event != 0; event = func_ov001_0208796c(event)) {
        BOOL found;
        sub = 0;
        found = func_ov001_02087c14(event, 0, &eventPos, &next);
        while (found) {
            eventCandidate.u.event.eventId = event;
            eventCandidate.u.event.subId = sub;
            eventCandidate.type = 2;
            eventRef = eventCandidate;
            if (IsTargetInVerticalRange(&eventRef)) {
                fx64 dist;
                func_01ff9e3c(&eventPos, origin, &eventDiff);
                eventOffset = eventDiff;
                dist = VEC_DotProduct(&eventOffset, &eventOffset);
                if (dist < best) {
                    best = dist;
                    lock->target = eventCandidate;
                }
            }
            if (sub >= next) {
                break;
            }
            sub = next;
            found = func_ov001_02087c14(event, sub, &eventPos, &next);
        }
    }
}
