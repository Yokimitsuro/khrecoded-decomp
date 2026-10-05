#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TargetCandidate {
    s32 kind;
    void *actor;
} TargetCandidate;

typedef struct TargetScore {
    fx32 distance;
    s32 priority;
    s32 valid;
} TargetScore;

typedef struct Actor {
    u8 pad_00[0xbc];
    VecFx32 position;
} Actor;

extern int func_ov001_0206dc38(void);
extern Actor *GetBoundedEntryField(int index);
extern BOOL IsActorNearLeader(Actor *actor, fx32 range);
extern void ClassifyTargetRange(int playerIndex, VecFx32 *position, TargetScore *score, int mode);
extern BOOL func_ov001_0206bb48(TargetScore *best, TargetScore *score);
extern void func_ov001_0206b954(TargetCandidate *candidate, Actor *actor);

void PickBestPartyTarget(TargetCandidate *candidate, TargetScore *best, int playerIndex, fx32 range)
{
    int count = func_ov001_0206dc38();
    int index;
    Actor *actor;
    TargetScore score;
    VecFx32 position;

    if (count > 1 && playerIndex == 0) {
        for (index = 1; index < count; index++) {
            actor = GetBoundedEntryField(index);
            if (IsActorNearLeader(actor, range)) {
                position = actor->position;
                ClassifyTargetRange(playerIndex, &position, &score, 4);
                if (func_ov001_0206bb48(best, &score)) {
                    func_ov001_0206b954(candidate, actor);
                    *best = score;
                }
            }
        }
    }
}
