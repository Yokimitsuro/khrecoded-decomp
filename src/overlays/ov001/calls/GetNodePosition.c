#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AttachedMatrix {
    fx32 rotation[9];
    VecFx32 translation;
    u16 nodeId;
} AttachedMatrix;

typedef struct ModelOwner {
    u8 pad_000[0x2c0];
    VecFx32 position;
} ModelOwner;

extern const VecFx32 data_0205344c;

extern AttachedMatrix *GetAttachedObject(ModelOwner *owner);
extern AttachedMatrix *GetObjectAttachment(AttachedMatrix *object);

void GetNodePosition(ModelOwner *owner, u32 nodeId, VecFx32 *out)
{
    AttachedMatrix *attached;

    *out = data_0205344c;
    if (nodeId == 0xFFFF) {
        *out = owner->position;
        return;
    }
    for (attached = GetAttachedObject(owner); attached != NULL; attached = GetObjectAttachment(attached)) {
        if (attached->nodeId == nodeId) {
            *out = attached->translation;
            return;
        }
    }
}
