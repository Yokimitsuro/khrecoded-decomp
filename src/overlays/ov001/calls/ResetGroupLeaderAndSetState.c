#include "nitro/types.h"

typedef struct GroupActor {
    u8 pad_000[0x10];
    s16 groupId;
    u8 pad_012[0x1b4 - 0x12];
    u8 groupFlagA;
    u8 groupFlagB;
} GroupActor;

typedef struct AnimController {
    u8 pad_00[0x10];
    void *defaults;
} AnimController;

typedef struct GroupMember {
    u8 pad_000[0x1d0];
    AnimController animController;
} GroupMember;

extern GroupMember *GetStageActor(s16 groupId);
extern void ClearActorMotionState(GroupMember *member);
extern void CopySourceWords(AnimController *controller);
extern void ClearWalkerStepState(GroupMember *member);
extern void func_ov001_02091ae8(GroupMember *member, u32 slotKey, u32 slotSubKey, int reserved);
extern u32 func_ov001_020925e4(GroupActor *actor, u32 state);

void ResetGroupLeaderAndSetState(GroupActor *actor)
{
    GroupMember *leader = GetStageActor(actor->groupId);

    if (leader != NULL) {
        actor->groupFlagA = 0;
        actor->groupFlagB = 0;
        ClearActorMotionState(leader);
        CopySourceWords(&leader->animController);
        ClearWalkerStepState(leader);
        func_ov001_02091ae8(leader, 0xffff, 0xffff, 0);
        func_ov001_020925e4(actor, 11);
    }
}
