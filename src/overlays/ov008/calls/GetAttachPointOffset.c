#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct AttachPoint {
    void *owner;
    u8 pad_04[0x8];
    VecFx32 offset;
} AttachPoint;

typedef struct AttachObject {
    u8 pad_00[0x68];
    AttachPoint points[24];
} AttachObject;

typedef struct AttachRequest {
    u8 pad_00[3];
    u8 pointIndex;
} AttachRequest;

extern const VecFx32 data_0205344c;
extern fx32 VEC_Mag(const VecFx32 *v);

BOOL GetAttachPointOffset(AttachObject *object, VecFx32 *outOffset, AttachRequest *request)
{
    if (request != NULL && request->pointIndex != 0xff) {
        *outOffset = object->points[request->pointIndex].offset;
    } else {
        *outOffset = data_0205344c;
    }
    if (VEC_Mag(outOffset) != 0) {
        return TRUE;
    }
    return FALSE;
}
