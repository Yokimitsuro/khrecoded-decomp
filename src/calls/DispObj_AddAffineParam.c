#include "nitro/types.h"

typedef struct OamSlot {
    u16 attr[3];
    s16 affineValue;
} OamSlot;

typedef struct AffineGroup {
    OamSlot slots[4];
} AffineGroup;

typedef struct DispObjOamBuffer {
    u8 pad[0x6028];
    int oamCapacity;
    int pad602c;
    int affineCount;
    AffineGroup groups[1];
} DispObjOamBuffer;

/* Store fx32 matrix as fx16 in OAM affine slots */
int DispObj_AddAffineParam(DispObjOamBuffer *buffer, const int *matrix)
{
    int index = buffer->affineCount;
    int result = -1;
    if (index < buffer->oamCapacity / 4) {
        AffineGroup *group = &buffer->groups[index];
        group->slots[0].affineValue = matrix[0] >> 4;
        group->slots[1].affineValue = matrix[1] >> 4;
        group->slots[2].affineValue = matrix[2] >> 4;
        group->slots[3].affineValue = matrix[3] >> 4;
        buffer->affineCount++;
        result = index;
    }
    return result;
}
