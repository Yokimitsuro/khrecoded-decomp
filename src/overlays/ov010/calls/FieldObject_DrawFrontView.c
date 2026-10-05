#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ViewSource {
    u8 pad_00[0xc];
    fx32 nearClip;
    fx32 farClip;
} ViewSource;

typedef struct ViewCamera {
    u8 pad_00[0xc];
    fx32 nearClip;
    fx32 farClip;
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;
} ViewCamera;

typedef struct ObjectModel {
    u8 pad_00[0x14];
    u8 node[1];
} ObjectModel;

typedef struct FieldObject {
    u8 pad_00[0xc];
    ObjectModel *model;
} FieldObject;

extern const VecFx32 data_0205344c;
extern ViewSource *func_ov021_020af614(void);
extern void DrawNodeWithExplicitProjection(void *node, void *camera, int top, int bottom, int left, int right);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

void FieldObject_DrawFrontView(FieldObject *object)
{
    ViewSource *source = func_ov021_020af614();
    ViewCamera camera;

    camera.nearClip = source->nearClip;
    camera.farClip = source->farClip;
    camera.position = data_0205344c;
    camera.target = MakeVec(0, 0, -0x1000);
    camera.up = MakeVec(0, 0x1000, 0);
    DrawNodeWithExplicitProjection(object->model->node, &camera, 0x1800, -0x1800, 0x2000, -0x2000);
}
