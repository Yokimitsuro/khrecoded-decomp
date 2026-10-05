#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct Basis {
    VecFx32 row[3];
} Basis;

typedef struct CameraMatrix {
    Basis basis;
    VecFx32 position;
} CameraMatrix;

typedef struct EventCameraWork {
    u8 pad000[0x38];
    fx32 positionBlend;
    fx32 rotationBlend;
    u8 pad040[0xe8];
    CameraMatrix matrix;
} EventCameraWork;

extern void Camera_BuildSideView(CameraMatrix *out);
extern void RotateTowardVector(const VecFx32 *from, const VecFx32 *to, fx32 ratio, VecFx32 *out);
extern void BuildBasisFromForward(const VecFx32 *forward, const VecFx32 *up, Basis *basis);
extern void NegateVecFx32(VecFx32 *vec);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void BlendEventCameraMatrix(EventCameraWork *work)
{
    CameraMatrix target;
    Basis built;
    Basis rebuilt;
    Basis *basis;
    CameraMatrix *source;
    VecFx32 *focus;

    if (work->positionBlend == FX32_ONE && work->rotationBlend == FX32_ONE) {
        Camera_BuildSideView(&work->matrix);
        return;
    }
    source = &target;
    Camera_BuildSideView(source);
    if (work->rotationBlend == FX32_ONE) {
        work->matrix.basis = target.basis;
    } else {
        basis = &work->matrix.basis;
        RotateTowardVector(&basis->row[2], &source->basis.row[2], work->rotationBlend, &basis->row[2]);
        RotateTowardVector(&basis->row[1], &source->basis.row[1], work->rotationBlend, &basis->row[1]);
        BuildBasisFromForward(&basis->row[2], &basis->row[1], &built);
        rebuilt = built;
        *(MtxFx33 *)basis = *(MtxFx33 *)&rebuilt;
        NegateVecFx32(&basis->row[0]);
    }
    if (work->positionBlend == FX32_ONE) {
        work->matrix.position = target.position;
        return;
    }
    focus = &target.position;
    VEC_Subtract(&work->matrix.position, focus, &work->matrix.position);
    ScaleVecFx32InPlace(&work->matrix.position, FX32_ONE - work->positionBlend);
    VEC_Add(&work->matrix.position, focus, &work->matrix.position);
}
