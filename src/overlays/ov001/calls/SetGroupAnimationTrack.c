#include "nitro/types.h"

typedef struct GroupActor {
    u8 pad_000[0x10];
    s16 groupId;
} GroupActor;

typedef struct GroupMember {
    u8 pad_000[0x288];
    u16 unk_288_0 : 9;
    u16 followsLeaderAnimation : 1;
    u16 unk_288_10 : 6;
} GroupMember;

extern GroupMember *GetStageActor(s16 groupId);
extern GroupMember *GetLinkedStageActor(GroupMember *member);
extern void PlayActorAnimationSlot(GroupMember *member, u32 track, u8 animId, u32 blendFrames, BOOL enable);

void SetGroupAnimationTrack(GroupActor *actor, u32 track, u8 animId, u32 blendFrames, BOOL enable)
{
    GroupMember *member = GetStageActor(actor->groupId);
    GroupMember *leader = member;

    for (; member != NULL; member = GetLinkedStageActor(member)) {
        if (member == leader || member->followsLeaderAnimation) {
            PlayActorAnimationSlot(member, track, animId, blendFrames, enable);
        }
    }
}
