#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Matrix33 {
    fx32 m[3][3];
} Matrix33;

typedef struct SceneNode {
    u16 flags;
    u8 pad_02[0x7a];
    u16 angleY;
    u16 angleZ;
    Matrix33 rotation;
} SceneNode;

extern const s16 data_02053580[];
extern void MTX_RotY33_(Matrix33 *mtx, fx32 sinValue, fx32 cosValue);

void UpdateNodeRotationYZ(SceneNode *node)
{
    if (node->flags & 0x20) {
        MTX_RotY33_(&node->rotation, data_02053580[node->angleY >> 4], data_02053580[(0x400 - (node->angleY >> 4)) & 0xfff]);
        if (node->angleZ != 0) {
            int index = node->angleZ >> 4;
            fx32 cosValue = data_02053580[(0x400 - index) & 0xfff];
            fx32 sinValue = data_02053580[index];
            fx32 value;
            fx64 negSin;

            node->rotation.m[1][1] = cosValue;
            node->rotation.m[0][1] = sinValue;
            sinValue = -sinValue;
            value = node->rotation.m[0][0];
            negSin = sinValue;
            node->rotation.m[1][0] = (fx32)((negSin * value) >> 12);
            node->rotation.m[0][0] = (fx32)(((fx64)cosValue * value) >> 12);
            value = node->rotation.m[0][2];
            node->rotation.m[1][2] = (fx32)((negSin * value) >> 12);
            node->rotation.m[0][2] = (fx32)(((fx64)cosValue * value) >> 12);
        }
        node->flags &= 0xffdf;
    }
}
