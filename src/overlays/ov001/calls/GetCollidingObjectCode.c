#include "nitro/types.h"

typedef struct FieldObject {
    u8 pad_000[0x1d8];
    u8 unk_1D8;
} FieldObject;

extern u8 *data_ov001_020a0528;
extern FieldObject *FindNextOverlappingEntry(const void *bounds, void *hitInfo);

u16 GetCollidingObjectCode(const void *bounds, void *hitInfo)
{
    FieldObject *object;

    if (data_ov001_020a0528 == NULL) {
        return 0;
    }
    object = FindNextOverlappingEntry(bounds, hitInfo);
    if (object == NULL) {
        return 0;
    }
    return object->unk_1D8 + 1;
}
