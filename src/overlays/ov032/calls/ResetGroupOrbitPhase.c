#include "nitro/types.h"

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 unk_03;
    s16 leaderLink;
} GroupMemberWork;

typedef struct ObjectGroup {
    u8 pad_00[0x2C];
    s32 orbitRadius;
    s32 orbitAngle;
    s32 orbitPhase;
} ObjectGroup;

extern GroupMemberWork *func_ov032_020bbc98(void *object);
extern ObjectGroup *func_ov032_020bbc80(void *object);

void ResetGroupOrbitPhase(void *object)
{
    GroupMemberWork *work = func_ov032_020bbc98(object);
    ObjectGroup *group = func_ov032_020bbc80(object);

    if (work->leaderLink == -1) {
        group->orbitPhase = 0;
    }
}
