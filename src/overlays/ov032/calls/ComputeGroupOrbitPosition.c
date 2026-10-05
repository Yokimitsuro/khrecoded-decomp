#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
} GroupMemberWork;

typedef struct ObjectGroup {
    u8 pad_00[0x2c];
    fx32 orbitRadius;
    s32 orbitAngle;
    s32 orbitPhase;
} ObjectGroup;

extern const fx16 data_02053580[];

extern GroupMemberWork *func_ov032_020bbc98(void *object);
extern ObjectGroup *func_ov032_020bbc80(void *object);
extern VecFx32 *func_ov001_0206dc4c(int index);

void ComputeGroupOrbitPosition(void *object, VecFx32 *out)
{
    GroupMemberWork *work = func_ov032_020bbc98(object);
    ObjectGroup *group = func_ov032_020bbc80(object);

    *out = *func_ov001_0206dc4c(0);
    if (work->leaderLink == -1) {
        switch (group->orbitPhase) {
        case 0:
            group->orbitRadius += 0x266;
            if (group->orbitRadius > 0x1800) {
                group->orbitRadius = 0x1800;
                group->orbitPhase = 1;
            }
            break;
        case 1:
            group->orbitAngle += 0x38e;
            if (group->orbitAngle >= 0x10000) {
                group->orbitAngle = 0;
                group->orbitPhase = 2;
            }
            break;
        case 2:
            group->orbitRadius -= 0x266;
            if (group->orbitRadius < 0) {
                group->orbitRadius = 0;
                group->orbitPhase = 0;
            }
            break;
        }
    }
    out->x += (fx32)(((s64)group->orbitRadius * data_02053580[group->orbitAngle >> 4] + 0x800) >> 12);
    out->z += (fx32)(((s64)group->orbitRadius * data_02053580[(0x400 - (group->orbitAngle >> 4)) & 0xfff] + 0x800) >> 12);
}
