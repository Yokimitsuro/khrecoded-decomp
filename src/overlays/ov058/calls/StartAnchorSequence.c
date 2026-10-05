#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    u8 data[0x28];
} SegmentStorage;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct {
    u32 words[0x12];
    QueryCallback filter;
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef struct {
    u8 active;
    u8 pad_01[3];
    s32 unk04;
    VecFx32 anchor;
    VecFx32 prevAnchor;
    s16 heading;
    u8 pad_22[2];
    s32 arrived;
    s32 unk28;
    u8 pad_2c[0x3c - 0x2c];
    u8 model[0x778 - 0x3c];
    s16 slotGroups[3][4];
    s16 slots[4];
    u8 cameraPath[4];
} OverlayState;

extern OverlayState data_ov058_020d8a44;
extern const VecFx32 data_ov058_020d89c8;

extern void RotateOffsetAroundY(VecFx32 *out, const VecFx32 *origin, u16 angle, const VecFx32 *offset);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern CollisionShape func_0203ade0(SegmentStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern void CollisionQuery_Init(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision(CollisionQuery *query);
extern void func_ov021_020a9288(void);
extern void func_ov058_020d7074(fx32 step);
extern void SelectAnimationById(void *model, int id);
extern void CameraPath_Start(void *path);
extern void UpdateSceneCameraTransform(int mode);

void StartAnchorSequence(const VecFx32 *pos, s16 angle)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    CollisionQuery query;
    VecFx32 offset;
    VecFx32 anchor;
    SegmentStorage segment;
    CollisionShape shape;
    VecFx32 top;
    VecFx32 end;
    VecFx32 dir;
    CollisionShape shapeResult;
    VecFx32 diff;
    VecFx32 axis;
    u32 filterArg;
    QueryCallback callback;
    OverlayState *state = &data_ov058_020d8a44;
    int heading;
    int i;
    int j;

    state->unk04 = 0;
    state->active = 1;
    state->arrived = 0;
    state->unk28 = 0;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 4; j++) {
            state->slotGroups[i][j] = -1;
        }
    }
    for (i = 0; i < 4; i++) {
        state->slots[i] = -1;
    }
    heading = (u16)(angle + 0x8000);
    offset = data_ov058_020d89c8;
    RotateOffsetAroundY(&anchor, pos, heading, &offset);
    top = *pos;
    top.y += 0x400;
    end = anchor;
    end.y = top.y;
    VEC_Subtract(&end, &top, &diff);
    axis = diff;
    shapeResult = func_0203ade0(&segment, &top, &end, &axis, func_01ffaff4(&axis, &axis));
    shape = shapeResult;
    CollisionQuery_Init(&query, 7, NULL, 0xa, 1, 0, &shape, &workspace, NULL);
    sweep = query;
    filterArg = 0;
    callback.func = func_ov021_020a9288;
    callback.arg = &filterArg;
    sweep.callback = callback;
    if (SweepWorldCollision(&sweep) != NULL) {
        VEC_Subtract(&shape.data[1], pos, &dir);
        VEC_Normalize(&dir, &dir);
        VEC_MultAdd(0x800, &dir, pos, &anchor);
        anchor.y = pos->y;
    }
    state->anchor = anchor;
    state->heading = heading;
    func_ov058_020d7074(0x1000);
    SelectAnimationById(state->model, -1);
    CameraPath_Start(state->cameraPath);
    UpdateSceneCameraTransform(1);
}
