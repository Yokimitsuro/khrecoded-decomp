#include "nitro/types.h"

typedef struct ScriptRunner {
    u16 targetKind;
    u16 targetId;
} ScriptRunner;

typedef struct GroupMember {
    u8 pad_000[0x1d0];
    ScriptRunner runner;
} GroupMember;

extern int func_ov021_020b4bfc(ScriptRunner *runner, int slot);
extern GroupMember *GetLinkedStageActor(GroupMember *member);

u16 RunGroupScriptSlot(GroupMember *leader, int slot)
{
    GroupMember *member = leader;
    u16 leaderResult = 0;

    while (member != NULL) {
        u16 result = func_ov021_020b4bfc(&member->runner, slot);
        if (member == leader) {
            leaderResult = result;
        }
        member = GetLinkedStageActor(member);
    }
    return leaderResult;
}
