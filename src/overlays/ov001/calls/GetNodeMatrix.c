#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Matrix43 {
    fx32 m[12];
} Matrix43;

typedef struct AttachedMatrix {
    Matrix43 mtx;
    u16 nodeId;
} AttachedMatrix;

typedef struct ModelPart {
    u8 pad_00[4];
    u8 node[0x80];
    Matrix43 rootMtx;
} ModelPart;

typedef struct ModelOwner {
    u8 pad_00[0x10];
    ModelPart part;
} ModelOwner;

extern AttachedMatrix *GetAttachedObject(ModelOwner *owner);
extern AttachedMatrix *GetObjectAttachment(AttachedMatrix *object);
extern BOOL RestoreNodeMatrixWithRotationCorrection(u8 *node, Matrix43 *posMtx, u32 nodeId, BOOL applyCorrection);

void GetNodeMatrix(ModelOwner *owner, u32 nodeId, Matrix43 *out)
{
    ModelPart *part = &owner->part;
    AttachedMatrix *attached;

    if (nodeId == 0xFFFF) {
        *out = part->rootMtx;
        return;
    }
    for (attached = GetAttachedObject(owner); attached != NULL; attached = GetObjectAttachment(attached)) {
        if (attached->nodeId == nodeId) {
            *out = attached->mtx;
            return;
        }
    }
    RestoreNodeMatrixWithRotationCorrection(part->node, out, nodeId, TRUE);
}
