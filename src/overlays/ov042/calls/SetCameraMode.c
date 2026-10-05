#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 _0[0x70];
    VecFx32 goalEye;
    u8 _7c[0x24];
    VecFx32 savedEye;
    VecFx32 savedGoalEye;
    int savedIndex;
    u8 _bc[0x84];
    u32 mode;
} CameraState;

typedef struct {
    u8 _0[4];
    int **tree;
} CollisionWorld;

extern CameraState *data_ov042_020be5e0;
extern CollisionWorld *GetActorRegistry(void);
extern void QuadTree_RemoveObject(int *tree, int object);

void SetCameraMode(u32 mode) {
    CollisionWorld *world = GetActorRegistry();
    data_ov042_020be5e0->mode = mode;
    if (data_ov042_020be5e0->mode & 1) {
        QuadTree_RemoveObject(*world->tree, (int)data_ov042_020be5e0 + 0x40c);
        QuadTree_RemoveObject(*world->tree, (int)data_ov042_020be5e0 + 0x494);
        QuadTree_RemoveObject(*world->tree, (int)data_ov042_020be5e0 + 0x51c);
    }
    if (data_ov042_020be5e0->mode & 4) {
        data_ov042_020be5e0->savedEye = data_ov042_020be5e0->goalEye;
        data_ov042_020be5e0->savedGoalEye = data_ov042_020be5e0->goalEye;
        data_ov042_020be5e0->savedIndex = -1;
    }
}
