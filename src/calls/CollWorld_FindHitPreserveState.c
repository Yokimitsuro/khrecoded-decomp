#include "nitro/types.h"

typedef struct CollHitRecord {
    u32 words[0x2e];
} CollHitRecord;

typedef struct CollTraversalFrame CollTraversalFrame;
typedef struct CollWorld CollWorld;

extern void MIi_CpuCopyFast(const void *src, void *dest, u32 size);
extern CollHitRecord *CollWorld_FindHit(CollWorld *world, const void *params);
extern CollHitRecord data_027e0134;
extern CollHitRecord data_02060784;
extern u8 data_027e00b4[0x80];
extern CollTraversalFrame *data_027e00b0;

CollHitRecord *CollWorld_FindHitPreserveState(CollWorld *world, const void *params)
{
    u8 savedFrames[0x80];
    CollHitRecord result;
    CollTraversalFrame *savedTop;
    CollHitRecord *hit;

    data_02060784 = data_027e0134;
    MIi_CpuCopyFast(data_027e00b4, savedFrames, sizeof(savedFrames));
    savedTop = data_027e00b0;
    hit = CollWorld_FindHit(world, params);
    if (hit != NULL) {
        result = *hit;
    }
    data_027e0134 = data_02060784;
    MIi_CpuCopyFast(savedFrames, data_027e00b4, sizeof(savedFrames));
    data_027e00b0 = savedTop;
    if (hit != NULL) {
        data_02060784 = result;
        return &data_02060784;
    }
    return NULL;
}
