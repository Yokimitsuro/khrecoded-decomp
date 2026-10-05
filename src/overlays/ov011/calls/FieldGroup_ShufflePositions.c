#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x40];
    VecFx32 position;
} FieldObject;

typedef struct FieldGroup {
    u8 pad_00[0x46];
    u16 objectCount;
} FieldGroup;

extern void MI_CpuFill8(void *dst, int value, u32 size);
extern FieldObject *func_ov001_0207f4dc(FieldGroup *group, int index);
extern u32 random_next_scaled(u32 upperBound);
extern VecFx32 *ClaimNthFreeSpawnPoint(int target, int count, VecFx32 *points, u8 *used);
extern void FieldObject_SetPositionAndSync(FieldObject *object, const VecFx32 *position);

void FieldGroup_ShufflePositions(FieldGroup *group)
{
    u8 used[0x1a];
    VecFx32 positions[0x1a];
    int i = 0;
    int count = group->objectCount;

    MI_CpuFill8(used, 0, sizeof(used));
    for (; i < count; i++) {
        positions[i] = func_ov001_0207f4dc(group, i)->position;
    }
    for (i = 0; i < count; i++) {
        FieldObject *object = func_ov001_0207f4dc(group, i);
        FieldObject_SetPositionAndSync(object, ClaimNthFreeSpawnPoint(random_next_scaled(count - i), count, positions, used));
    }
}
