#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorStateFunc)(Actor *actor, int state);

typedef struct QuadTreeRef {
    int *root;
} QuadTreeRef;

typedef struct FieldSystem {
    u8 pad_00[4];
    QuadTreeRef *tree;
} FieldSystem;

struct Actor {
    u8 pad_0000[0x6ac];
    VecFx32 shadowOffset;
    u8 pad_06b8[0x928 - 0x6b8];
    u64 statusFlags;
    u8 pad_0930[0x94c - 0x930];
    VecFx32 knockback;
    u8 pad_0958[0x970 - 0x958];
    VecFx32 moveVelocity;
    VecFx32 rootMotion;
    u8 pad_0988[0xe9c - 0x988];
    int hitCounter;
    u8 pad_0ea0[0x171c - 0xea0];
    u32 pad_bits : 14;
    s32 commandActive : 1;
    u32 rest_bits : 17;
    u8 pad_1720[0x1774 - 0x1720];
    u8 quadNode[4];
    u8 pad_1778[0x1808 - 0x1778];
    ActorStateFunc setState;
};

extern FieldSystem *GetActorRegistry(void);
extern void QuadTree_RemoveObject(int *root, void *node);
extern void StopSeqArcOrDefault(int seqArcNo, int player, int fadeFrames);

void Actor_ClearMotionState(Actor *actor, int mode, BOOL flag) {
    switch (mode) {
    case 0:
        if (flag) {
            actor->statusFlags |= 0x20;
        } else {
            actor->statusFlags &= ~(u64)0x20;
        }
        actor->statusFlags &= ~(u64)0x1a;
        actor->hitCounter = 0;
        actor->moveVelocity.z = 0;
        actor->moveVelocity.y = 0;
        actor->moveVelocity.x = 0;
        actor->rootMotion.z = 0;
        actor->rootMotion.y = 0;
        actor->rootMotion.x = 0;
        actor->knockback.z = 0;
        actor->knockback.y = 0;
        actor->knockback.x = 0;
        break;
    case 1:
        actor->shadowOffset.z = 0;
        actor->shadowOffset.y = 0;
        actor->shadowOffset.x = 0;
        break;
    case 2:
        actor->moveVelocity.z = 0;
        actor->moveVelocity.y = 0;
        actor->moveVelocity.x = 0;
        actor->rootMotion.z = 0;
        actor->rootMotion.y = 0;
        actor->rootMotion.x = 0;
        actor->knockback.z = 0;
        actor->knockback.y = 0;
        actor->knockback.x = 0;
        if (flag) {
            actor->setState(actor, 1);
        } else {
            actor->commandActive = 0;
            QuadTree_RemoveObject(GetActorRegistry()->tree->root, actor->quadNode);
            StopSeqArcOrDefault(0xcd, 0, 5);
        }
        break;
    }
}
