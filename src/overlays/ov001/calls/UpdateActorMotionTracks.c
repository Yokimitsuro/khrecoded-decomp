#include "nitro/types.h"

typedef struct MotionEntity {
    s32 flags;
    u16 animFlags;
} MotionEntity;

typedef struct MotionTrack {
    s32 endFrame;
    s16 frame;
    u8 pad_06[2];
    s32 blend;
    char name[0x20];
} MotionTrack;

typedef struct MotionActor {
    u8 pad_000[0xd0];
    MotionTrack tracks[5];
    u8 pad_1ac[0xd18 - 0x1ac];
    MotionEntity **entitySlot;
    u8 pad_d1c[0xef4 - 0xd1c];
    u32 flags;
    u8 pad_ef8[0x8];
    s32 entityId;
} MotionActor;

extern int ActorSlot_GetField1C4ByIndex(u16 entityId);
extern int BuildSlotMask(void *anim, int speed);
extern int Anim_GetFrame(void *anim, u16 track);
extern int func_0202f4cc(void *anim, u16 track);
extern void func_01ffb2f8(void *anim, u16 track, int frame);
extern void ApplyPendingSeqRequests(MotionActor *actor);
extern void ActorSlot_UnlinkByIndex(u16 entityId);
extern void func_ov001_02088b80(MotionActor *actor);
extern void AdvanceAnimationRequestQueue(MotionActor *actor, int track);
extern void ClearActorTimerFields(MotionActor *actor);
extern void func_ov001_0208a480(MotionActor *actor);
extern void ClearActorFlagBit40(MotionActor *actor);

void UpdateActorMotionTracks(MotionActor *actor)
{
    MotionEntity *entity = *actor->entitySlot;
    BOOL any = FALSE;
    BOOL fire = FALSE;
    int mask = BuildSlotMask(&entity->animFlags, ActorSlot_GetField1C4ByIndex((u16)actor->entityId));
    int i;
    int j;
    MotionTrack *track;

    for (i = 0; i < 5; i++) {
        track = &actor->tracks[i];
        if (track->frame == -1 && track->name[0] == 0) {
            continue;
        }
        if (mask & (1 << i)) {
            if (!(entity->animFlags & 4)) {
                fire = TRUE;
            }
        } else if (i == 0) {
            if (Anim_GetFrame(&entity->animFlags, (u16)i) >= track->endFrame) {
                fire = TRUE;
            }
        }
        if (fire) {
            ApplyPendingSeqRequests(actor);
            if (track->frame == -2) {
                if (*actor->entitySlot != NULL) {
                    for (j = 0; j < 5; j++) {
                        func_01ffb2f8(&entity->animFlags, (u16)j, 0);
                    }
                }
                ActorSlot_UnlinkByIndex((u16)actor->entityId);
                func_ov001_02088b80(actor);
                actor->flags = 0x2000;
                return;
            }
            AdvanceAnimationRequestQueue(actor, i);
            if (i == 0) {
                func_01ffb2f8(&entity->animFlags, 0, 0);
                actor->tracks[i].endFrame = func_0202f4cc(&entity->animFlags, (u16)i) - 0x1000;
                if (actor->flags & 0x80) {
                    ClearActorTimerFields(actor);
                }
            }
        }
        if (!(track->frame == -1 && track->name[0] == 0)) {
            any = TRUE;
        }
    }
    if (any) {
        return;
    }
    actor->flags &= ~0x200;
    if (actor->flags & 0x40) {
        func_ov001_0208a480(actor);
        ClearActorFlagBit40(actor);
    }
}
