#include "nitro/types.h"

typedef struct Actor Actor;

typedef struct AnimBlendSet {
    u8 selector[0xd8];
    u8 blendTable[0x104 - 0xd8];
} AnimBlendSet;

typedef struct AnimBank {
    AnimBlendSet sets[3];
} AnimBank;

typedef int (*ActorGetMode)(Actor *actor);

struct Actor {
    u8 pad_0000[0x1dc];
    int mode;
    u8 pad_1e0[0x22c - 0x1e0];
    ActorGetMode getMode;
    u8 pad_230[0x16f0 - 0x230];
    u8 animReset[0x1700 - 0x16f0];
    AnimBank *animBank;
};

extern void func_ov059_020c8b9c(void *state);
extern void selectJointAnimationBlend(void *selector, u16 trackIndex, void *blendTable, s16 blendIndex);

void Actor_SetJointBlendMode(Actor *actor, int mode) {
    void *animReset = actor->animReset;
    int i;
    int current;

    if (actor->getMode != NULL) {
        current = actor->getMode(actor);
    } else {
        current = actor->mode;
    }
    if (mode != current) {
        func_ov059_020c8b9c(animReset);
        switch (mode) {
        case 1:
            for (i = 0; i < 5; i++) {
                selectJointAnimationBlend(actor->animBank->sets[0].selector, i, (u8 *)&actor->animBank->sets[0] + 0xd8, 0);
            }
            break;
        case 2:
            for (i = 0; i < 5; i++) {
                selectJointAnimationBlend(actor->animBank->sets[1].selector, i, (u8 *)&actor->animBank->sets[1] + 0xd8, 0);
            }
            break;
        case 3:
            for (i = 0; i < 5; i++) {
                selectJointAnimationBlend(actor->animBank->sets[2].selector, i, (u8 *)&actor->animBank->sets[2] + 0xd8, 0);
            }
            break;
        }
        actor->mode = mode;
    }
}
