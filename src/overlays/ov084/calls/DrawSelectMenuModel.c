#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraParams {
    fx32 fovySin;
    fx32 fovyCos;
    fx32 aspect;
    fx32 nearClip;
    fx32 farClip;
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;
} CameraParams;

typedef struct CameraPreset {
    fx32 height;
    fx32 targetX;
    fx32 targetY;
    fx32 depth;
} CameraPreset;

typedef struct SelectMenu {
    u8 pad_00[0xd0];
    u8 model[1];
} SelectMenu;

extern CameraPreset data_ov084_020bfc70[2];

extern u32 func_ov039_020bc818(void);
extern void LoadDefaultProjectionValues(CameraParams *params);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void camera_commit_projection(CameraParams *params);
extern void G3X_SetHOffset(int value);
extern u16 AdvanceAnimationTracks(void *state, fx32 delta);
extern void func_01ffb12c(void *node);

void DrawSelectMenuModel(SelectMenu *menu)
{
    CameraParams camera;
    VecFx32 offset;
    CameraPreset *preset;
    int index;

    if (func_ov039_020bc818() & 0x8000) {
        index = 0;
    } else {
        index = 1;
    }
    preset = &data_ov084_020bfc70[index];
    LoadDefaultProjectionValues(&camera);
    camera.position.y = preset->height;
    {
        VecFx32 depth;
        depth.x = 0;
        depth.y = 0;
        depth.z = preset->depth;
        offset = depth;
    }
    camera.position.x = 0;
    camera.position.z = 0;
    VEC_Add(&camera.position, &offset, &camera.target);
    camera.target.x += preset->targetX;
    camera.target.y += preset->targetY;
    camera_commit_projection(&camera);
    G3X_SetHOffset(-0x39);
    AdvanceAnimationTracks(menu->model, 0x1000);
    func_01ffb12c(menu->model);
}
