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

extern void InitMoverCast(MotionState *state, void *info);
extern BOOL TestMoverAgainstModelTree(MotionState *state, void *model);
extern CollisionResult data_027e0134;

CollisionResult *QueryModelCollision(CollisionScene *scene, void *info)
{
    MotionState state;

    InitMoverCast(&state, info);
    if (TestMoverAgainstModelTree(&state, scene->modelRef->model)) {
        data_027e0134.hitRange = state.maxRange;
        return &data_027e0134;
    }
    return NULL;
}
