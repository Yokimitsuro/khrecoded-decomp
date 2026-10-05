#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorInfo {
    u8 pad_00[0x7d];
    u8 category;
} ActorInfo;

typedef struct TargetActor {
    u8 pad_00[4];
    struct TargetActor *next;
    ActorInfo *info;
} TargetActor;

typedef struct TargetCandidate {
    s32 kind;
    void *object;
    u8 pad_08[0xc];
} TargetCandidate;

typedef struct TargetScore {
    s32 distance;
    s32 priority;
    s32 valid;
} TargetScore;

extern TargetActor *func_ov001_0207f0b4(void);
extern BOOL IsActorTargetable(void *origin, TargetActor *actor, s32 range);
extern VecFx32 *func_ov001_0207f898(TargetActor *actor);
extern void ClassifyTargetRange(void *origin, VecFx32 *position, TargetScore *score, s32 kind);
extern BOOL func_ov001_0206bb48(TargetScore *best, TargetScore *score);
extern TargetCandidate *func_ov001_0206b938(TargetCandidate *candidate, TargetActor *actor);

void ScanActorsForNearestTarget(TargetCandidate *candidate, TargetScore *best, void *origin, s32 range)
{
    TargetActor *actor;
    TargetScore score;

    for (actor = func_ov001_0207f0b4(); actor != NULL; actor = actor->next) {
        if (IsActorTargetable(origin, actor, range)) {
            ClassifyTargetRange(origin, func_ov001_0207f898(actor), &score, 2);
            if (actor->info->category == 4) {
                score.priority = 10;
            }
            if (func_ov001_0206bb48(best, &score)) {
                func_ov001_0206b938(candidate, actor);
                *best = score;
            }
        }
    }
}
