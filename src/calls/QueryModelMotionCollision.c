#include "nitro/types.h"

typedef struct MotionState {
    u8 pad_00[0xe4];
    s32 maxRange;
    u8 pad_e8[0x2c];
} MotionState;

typedef struct CollModelRef {
    void *model;
} CollModelRef;

typedef struct CollisionScene {
    u32 unk_00;
    CollModelRef *modelRef;
} CollisionScene;

typedef struct CollisionResult {
    u8 pad_00[0x2c];
    s32 hitRange;
} CollisionResult;

extern void InitMotionState(MotionState *state, void *info);
extern BOOL TestMoverAgainstModelWalls(MotionState *state, void *model);
extern CollisionResult data_027e0134;

CollisionResult *QueryModelMotionCollision(CollisionScene *scene, void *info)
{
    MotionState state;

    InitMotionState(&state, info);
    if (TestMoverAgainstModelWalls(&state, scene->modelRef->model)) {
        data_027e0134.hitRange = state.maxRange;
        return &data_027e0134;
    }
    return NULL;
}
