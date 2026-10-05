#include "nitro/types.h"

typedef struct ScriptCommand {
    u8 pad_00[0xc];
    u8 type;
    u8 pad_0d[3];
    s16 groupId;
    u16 targetId;
} ScriptCommand;

typedef struct ScriptRunner {
    u16 targetKind;
    u16 targetId;
} ScriptRunner;

typedef struct GroupMember {
    u8 pad_000[0x1d0];
    ScriptRunner runner;
    u8 pad_1d4[0x28a - 0x1d4];
    u16 unk_28A_0 : 9;
    u16 scriptRunning : 1;
    u16 unk_28A_10 : 6;
} GroupMember;

extern GroupMember *GetStageActor(s16 groupId);
extern void *GetStageObjectHandle(u32 id);
extern int SelectSequenceTrack(ScriptRunner *runner, int slot);

int RunLeaderScriptSlotCommand(ScriptCommand *command)
{
    GroupMember *leader = GetStageActor(command->groupId);

    GetStageObjectHandle(command->targetId);
    leader->scriptRunning = 1;
    if (SelectSequenceTrack(&leader->runner, 5) != 4) {
        return 0;
    }
    if (command->type == 8) {
        leader->scriptRunning = 0;
        return 0;
    }
    leader->scriptRunning = 0;
    return 3;
}
