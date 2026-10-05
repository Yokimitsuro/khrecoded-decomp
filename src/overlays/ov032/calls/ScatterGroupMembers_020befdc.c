#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GroupMemberWork {
    s16 state;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x4];
    void *world;
} GroupObject;

typedef struct ObjectGroup {
    u32 firstMember : 9;
    u32 leaderIndex : 9;
    u32 unk_00_18 : 14;
    u32 unk_04;
    u32 flags;
    u16 memberCount : 8;
    u16 unk_0c_8 : 8;
    u8 pad_0e[0x2a];
    s16 unk_38;
} ObjectGroup;

extern ObjectGroup *func_ov032_020bbc80(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern GroupObject *func_ov001_02086384(void *world, int index);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern u32 random_next_scaled(u32 upperBound);
extern BOOL func_ov032_020beed8(int index, VecFx32 *out);
extern void func_ov016_020a6ce4(GroupObject *object, const VecFx32 *position);

void ScatterGroupMembers_020befdc(GroupObject *object)
{
    ObjectGroup *group = func_ov032_020bbc80(object);
    VecFx32 *spots = NNSi_FndAllocFromDefaultHeap(0xc00);
    u16 freeSpots[256];
    int count;
    int i;
    int j;

    i = 0;
    count = 0;
    for (; i < 0x100; i++) {
        if (func_ov032_020beed8(i, &spots[i])) {
            freeSpots[count++] = i;
        }
    }
    for (i = 0; i < group->memberCount; i++) {
        GroupObject *member = func_ov001_02086384(object->world, group->firstMember + i);
        GroupMemberWork *work = func_ov032_020bbc98(member);
        u16 spot;
        j = random_next_scaled(count);
        spot = freeSpots[j];
        for (; j < count - 1; j++) {
            freeSpots[j] = freeSpots[j + 1];
        }
        work->state = 0;
        group->unk_38 = 0;
        count--;
        func_ov016_020a6ce4(member, &spots[spot]);
    }
    NNSi_FndFreeFromDefaultHeap(spots);
    group->flags = (group->flags | 4) & ~1;
}
