#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PushContext {
    u32 flags;
} PushContext;

typedef struct PushEvent {
    u8 pad_00[0x10];
    u16 actorId;
} PushEvent;

typedef struct PushEntry {
    u8 pad_000[0xbc];
    VecFx32 target;
    u8 pad_0c8[0x9c8 - 0xc8];
    VecFx32 velocity;
} PushEntry;

typedef struct LinkedActor {
    u8 pad_00[0xc];
    u8 flags;
    u8 pad_0d[0xa2 - 0xd];
    u16 nextId;
} LinkedActor;

typedef struct PushActor {
    u8 pad_000[0x26c];
    u32 flags : 31;
    u32 unk_26c_31 : 1;
    u8 pad_270[0x284 - 0x270];
    u16 linkId;
    u8 pad_286[2];
    u16 unk_288_0 : 7;
    u16 pushed : 1;
    u16 unk_288_8 : 8;
    u8 pad_28a[0x2b4 - 0x28a];
    fx32 height;
    u8 pad_2b8[0x2c0 - 0x2b8];
    VecFx32 basePosition;
    u8 pad_2cc[0x31c - 0x2cc];
    fx32 scale;
    u8 pad_320[0x374 - 0x320];
    VecFx32 pushOffset;
} PushActor;

extern const VecFx32 data_0205344c;

extern PushContext *func_ov001_0209c3e8(void);
extern PushActor *GetStageActor(int id);
extern PushEntry *CacheStageEntryValue(u16 id);
extern fx32 GetStageEntryParam(u16 id);
extern LinkedActor *GetStageLinkedActor(u16 id);
extern BOOL ComputeActorPushOut(PushEvent *event, PushActor *actor, LinkedActor *other, VecFx32 *position,
                                         const VecFx32 *target, fx32 margin, VecFx32 *outSelf, VecFx32 *outOther);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern fx32 VEC_Mag(const VecFx32 *v);

#define FX_MUL(a, b) ((fx32)(((fx64)(a) * (b) + 0x800) >> 12))
#define ABS(x) ((x) < 0 ? -(x) : (x))

void ResolveStageEntryPushOut(PushEvent *event)
{
    PushContext *context = func_ov001_0209c3e8();
    VecFx32 zero = data_0205344c;
    VecFx32 total = data_0205344c;
    PushActor *actor;
    LinkedActor *linked;
    const VecFx32 *target;
    PushEntry *entry;
    int i;

    if (context->flags & 1) {
        return;
    }
    if (event->actorId == 0) {
        return;
    }
    actor = GetStageActor((s16)event->actorId);
    actor->pushed = 0;
    for (i = 0;; i++) {
        int id = i + 1;
        VecFx32 position;

        entry = CacheStageEntryValue(id);
        position = actor->basePosition;

        position.y += FX_MUL(actor->height, actor->scale);
        if (entry == NULL) {
            return;
        }
        target = &entry->target;
        if (target == NULL) {
            continue;
        }
        if (!(actor->flags & 0x800)) {
            VecFx32 selfPush = zero;
            VecFx32 otherPush = zero;
            fx32 margin = GetStageEntryParam(id);

            actor->pushed = ComputeActorPushOut(event, actor, NULL, &position, target, margin, &selfPush, &otherPush) != 0;
            VEC_Add(&selfPush, &actor->pushOffset, &actor->pushOffset);
            VEC_Add(&otherPush, &total, &total);
            if (actor->linkId != 0) {
                LinkedActor *first = GetStageLinkedActor(actor->linkId);

                linked = first;

                if (first != NULL) {
                    do {
                        if (first != linked && !(linked->flags & 2)) {
                            selfPush = zero;
                            otherPush = zero;
                            actor->pushed = ComputeActorPushOut(event, actor, linked, NULL, target, margin, &selfPush, &otherPush) != 0;
                            VEC_Add(&selfPush, &actor->pushOffset, &actor->pushOffset);
                            VEC_Add(&otherPush, &total, &total);
                        }
                        if (linked->nextId == 0) {
                            linked = NULL;
                        } else {
                            linked = GetStageLinkedActor(linked->nextId);
                        }
                    } while (linked != NULL);
                }
            }
        }
        if (entry != NULL && VEC_Mag(&total) != 0) {
            fx32 current = entry->velocity.y;

            total.y = (fx32)(((fx64)total.y * 0xcd + 0x800) >> 12);
            if (current * total.y > 0) {
                if (ABS(current) < ABS(total.y)) {
                    entry->velocity.y = total.y;
                }
            } else {
                entry->velocity.y += total.y;
            }
            entry->velocity.x += total.x;
            entry->velocity.z += total.z;
        }
    }
}
