#include "nitro/types.h"

typedef struct GroupCommand {
    s32 state;
    u16 resetPending : 1;
    u16 unk_04_1 : 15;
    u8 pad_06[0x10 - 0x06];
    u16 groupId;
} GroupCommand;

extern void *data_ov001_0209e48c[];
extern void *GetStageActor(s16 groupId);
extern void func_ov001_02095904(GroupCommand *command, int mode);
extern void func_ov001_02090f28(void *leader);
extern void func_ov001_020925e4(GroupCommand *command, s32 state);

void ResetGroupCommandState(GroupCommand *command)
{
    void *leader;

    if (command->resetPending && command->groupId != 0) {
        leader = GetStageActor((s16)command->groupId);
        if (command->state >= 12 || data_ov001_0209e48c[command->state] != NULL) {
            func_ov001_02095904(command, 0);
            func_ov001_02090f28(leader);
            func_ov001_020925e4(command, 6);
            command->resetPending = 0;
        }
    }
}
