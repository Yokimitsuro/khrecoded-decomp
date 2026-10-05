#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Matrix33 {
    fx32 m[3][3];
} Matrix33;

typedef struct SceneNode {
    u16 flags;
    u8 pad_02[0x7e];
    Matrix33 rotation;
} SceneNode;

extern const s16 data_02053580[];
extern void MTX_Identity33_(Matrix33 *mtx);
extern void MTX_RotX33_(Matrix33 *mtx, fx32 sinValue, fx32 cosValue);
extern void MTX_RotY33_(Matrix33 *mtx, fx32 sinValue, fx32 cosValue);
extern void MTX_Concat33(const Matrix33 *a, const Matrix33 *b, Matrix33 *ab);

void SetNodeRotationXY(SceneNode *node, u32 axes, int angleY, int angleX)
{
    Matrix33 rotateX;
    Matrix33 rotateY;

    MTX_Identity33_(&rotateX);
    MTX_Identity33_(&rotateY);
    if (axes & 1) {
        MTX_RotX33_(&rotateX, data_02053580[angleX >> 4], data_02053580[(0x400 - (angleX >> 4)) & 0xfff]);
    }
    if (axes & 2) {
        MTX_RotY33_(&rotateY, data_02053580[angleY >> 4], data_02053580[(0x400 - (angleY >> 4)) & 0xfff]);
    }
    MTX_Concat33(&rotateX, &rotateY, &node->rotation);
    node->flags &= 0xffdf;
}
