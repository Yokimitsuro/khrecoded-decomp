#include "nitro/types.h"

typedef struct Enemy Enemy;
typedef int (*EnemyGetter)(Enemy *enemy);

typedef struct {
    u8 animState[0xd8];
    u8 blendTable[0x2c];
} AnimSet;

typedef struct {
    s32 frame;
    s32 timer;
    u8 active;
    u8 pad_09[3];
    s32 count;
} PoseState;

struct Enemy {
    u8 pad_0000[0x1dc];
    s32 pose;
    u8 pad_01e0[0x22c - 0x1e0];
    EnemyGetter getPose;
    u8 pad_0230[0x105c - 0x230];
    PoseState poseState;
    AnimSet *poseAnims;
};

extern void selectJointAnimationBlend(void *animState, u16 trackIndex, void *blendTable, s16 blendIndex);

void SetEnemyPose(Enemy *enemy, int pose)
{
    PoseState *state = &enemy->poseState;
    int current;
    BOOL valid;
    int i;

    if (enemy->getPose != NULL) {
        current = enemy->getPose(enemy);
    } else {
        current = enemy->pose;
    }
    valid = FALSE;
    if (pose == current) {
        return;
    }
    switch (pose) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        valid = TRUE;
        break;
    }
    if (!valid) {
        return;
    }
    state->frame = 0;
    state->timer = 0;
    state->active = 0;
    state->count = 0;
    switch (pose) {
    case 0:
        break;
    case 1:
        for (i = 0; i < 5; i++) {
            selectJointAnimationBlend(enemy->poseAnims[0].animState, i, enemy->poseAnims[0].blendTable, 0);
        }
        break;
    case 2:
        for (i = 0; i < 5; i++) {
            selectJointAnimationBlend(enemy->poseAnims[1].animState, i, enemy->poseAnims[1].blendTable, 0);
        }
        break;
    case 3:
        for (i = 0; i < 5; i++) {
            selectJointAnimationBlend(enemy->poseAnims[2].animState, i, enemy->poseAnims[2].blendTable, 0);
        }
        break;
    case 4:
        for (i = 0; i < 5; i++) {
            selectJointAnimationBlend(enemy->poseAnims[3].animState, i, enemy->poseAnims[3].blendTable, 0);
        }
        break;
    }
    enemy->pose = pose;
}
